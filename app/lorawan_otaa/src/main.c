/*
 * LoRaWAN OTAA sample application
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/pm/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/settings/settings.h>

#include "rak_adc.h"
#include "rak_ble_peripheral.h"
#include "rak_lorawan.h"
#include "rak_lp_console.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_shtcx)
#error "No sensirion,shtcx compatible node found in the device tree"
#endif

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(green_led), gpios);

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
	int ret = -1;

#if defined(CONFIG_BOARD_RAK3172)
	rak_lp_console_init();
#endif

#if defined(CONFIG_BOARD_RAK4631)
	configure_uicr();
#endif

	if (!gpio_is_ready_dt(&led)) {
		LOG_ERR("LED is not ready!");
		return 0;
	}

#if defined(CONFIG_BT_PERIPHERAL)
	ret = rak_ble_peripheral_init();
	if (ret) {
		LOG_ERR("Failed to init ble peripheral: %d", ret);
	}
#endif

	gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	gpio_pin_set_dt(&led, 1); // ON
	k_msleep(1000);

	if (IS_ENABLED(CONFIG_SETTINGS)) {
		settings_load();
	}

	ret = rak_adc_init();
	if(ret != 0) {
		LOG_ERR("Failed to init adc: %d", ret);
		return 0;
	}

	ret = rak_lorawan_init();
	if(ret != 0) {
		LOG_ERR("Failed to start lorawan: %d", ret);
		return 0;
	}

	gpio_pin_set_dt(&led, 0); // OFF

	rak_lorawan_thread_start();

	LOG_INF("LoRaWAN OTAA example started @%s", CONFIG_BOARD);
	printk("LoRaWAN OTAA example started @%s\n", CONFIG_BOARD);

	return 0;
}
