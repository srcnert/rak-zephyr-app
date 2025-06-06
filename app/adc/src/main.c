#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#if defined(CONFIG_BOARD_RAK3172)
double correction_ratio = 1.1;
#endif

#if defined(CONFIG_BOARD_RAK4631)
double correction_ratio = 1.1;
#endif

#if defined(CONFIG_BOARD_RAK11720)
// Apollo3's adc range is 2V!
double correction_ratio = (2.13) * (1.3);
#endif

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

/* Data of ADC io-channels specified in devicetree. */
static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels, DT_SPEC_AND_COMMA)
};

uint16_t buf;
struct adc_sequence sequence = {
	.buffer = &buf,
	/* buffer size in bytes, not number of samples */
	.buffer_size = sizeof(buf),
};

#if defined(CONFIG_BOARD_RAK4631)
static void configure_uicr(void) {
	if ((NRF_UICR->REGOUT0 & UICR_REGOUT0_VOUT_Msk) !=
		(UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos)) {
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
		while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

		NRF_UICR->REGOUT0 = (NRF_UICR->REGOUT0 & ~((uint32_t)UICR_REGOUT0_VOUT_Msk)) |
							(UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos);

		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
		while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

		LOG_INF("REGOUT0 is updated!");

		// System reset is needed to update UICR registers.
		NVIC_SystemReset();
	}
}
#endif

int main(void)
{
	int err;

#if defined(CONFIG_BOARD_RAK4631)
	configure_uicr();
#endif

	/* Configure channels individually prior to sampling. */
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
		if (!adc_is_ready_dt(&adc_channels[i])) {
			LOG_ERR("ADC controller device %s not ready", adc_channels[i].dev->name);
			return 0;
		}

		err = adc_channel_setup_dt(&adc_channels[i]);
		if (err < 0) {
			LOG_ERR("Could not setup channel #%d (%d)", i, err);
			return 0;
		}
	}

	int32_t vref_mv = (int32_t)adc_ref_internal(adc_channels[0].dev);
	enum adc_gain gain = adc_channels[0].channel_cfg.gain;
	adc_gain_invert(gain, &vref_mv);
	double vref = (double) (vref_mv/1000.0);
	uint8_t resolution = adc_channels[0].resolution;

	LOG_INF("Vref: %d", vref_mv);
	LOG_INF("Resolution: %d", resolution);

	while (1) {
		/* ADC reading */
		for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
			int32_t val;

#if defined(CONFIG_BOARD_RAK3172)
			LOG_INF("Calibrate ADC");
			sequence.calibrate=true;
#endif

			(void)adc_sequence_init_dt(&adc_channels[i], &sequence);

			err = adc_read_dt(&adc_channels[i], &sequence);
			if (err < 0) {
				LOG_ERR("Could not read (%d)", err);
				continue;
			}

			val = (int32_t)buf;
			LOG_INF("ADC: %"PRId32, val);

			/*
			If rak19007 board is used as a base board,
			- no battery, USB connected
				* meaningless value, you read the Vout of the TP4054 in none-charging mode
			- battery, USB connected
				* meaningless value, you read the charging voltage of the TP4054
			- battery, USB not connected
				* battery voltage reading

			Due to this, RTT logging is used, please do not connect your usb line
			to get correct ADC data!

			Please connect a lipo battery to your RAK19007 board!
			*/

			double bat_lvl = correction_ratio * ((vref * (((double)val) / ((double) pow(2, resolution))) * (5.0)) / (3.0));
			LOG_INF("V_BAT = %"PRId32" mV", (int32_t) (bat_lvl*1000.0));
		}

		k_sleep(K_MSEC(1000));
	}

	return 0;
}
