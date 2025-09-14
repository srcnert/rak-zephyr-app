#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#if !DT_HAS_COMPAT_STATUS_OKAY(st_lis3dh)
#error "No st,lis3dh compatible node found in the device tree"
#endif

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

		// System reset is needed to update UICR registers.
		NVIC_SystemReset();
	}
}
#endif

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(st_lis3dh);
	int rc;

#if defined(CONFIG_BOARD_RAK4631)
	configure_uicr();
#endif

	if (!device_is_ready(dev)) {
		printf("Device %s is not ready\n", dev->name);
		return 0;
	}

	while (1) {
		struct sensor_value accel[3];

		rc = sensor_sample_fetch(dev);
		if (rc == 0) {
			rc = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ,
						accel);
		}

		if (rc != 0) {
			printf("RAK1904(LIS3DH): failed: %d\n", rc);
			break;
		}

		printf("RAK1904(LIS3DH): %.2f m/s^2 ; %.2f m/s^2 ; %.2f m/s^2\n",
				sensor_value_to_double(&accel[0]),
				sensor_value_to_double(&accel[1]),
				sensor_value_to_double(&accel[2]));

		k_sleep(K_MSEC(2000));
	}

	return 0;
}
