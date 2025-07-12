#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/pm/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/lora.h>

#include "ble_peripheral.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

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
#if defined(CONFIG_BOARD_RAK4631)
	configure_uicr();
#endif

#if defined(CONFIG_BT_PERIPHERAL)
	int ret = ble_peripheral_init();
	if (ret) {
		LOG_ERR("Failed to init ble peripheral: %d", ret);
	}
#endif

	/* using __TIME__ ensure that a new binary will be built on every
	 * compile which is convenient when testing firmware upgrade.
	 */
	printk("build time: " __DATE__ " " __TIME__ "\n");

	while (1) {
		k_sleep(K_FOREVER);
	}

	return 0;
}
