#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/pm/device.h>

#include "rak_ble_peripheral.h"

#include <esp_sleep.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

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

/*
 * Get LoRa device
 */
// static const struct device *lora_dev = DEVICE_DT_GET(DT_ALIAS(lora0));

/*
 * Get UART device
 */
static const struct device *const uart_dev = DEVICE_DT_GET(DT_ALIAS(test_uart));

/*
 * Print a null-terminated string character by character to the UART interface
 */
void print_uart(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(uart_dev, buf[i]);
	}
}

int main(void)
{
#if defined(CONFIG_BOARD_RAK4631)
	configure_uicr();
#endif

	// if (!device_is_ready(lora_dev)) {
	// 	LOG_ERR("LoRa device not found!");
	// 	return -1;
	// }

	if (!device_is_ready(uart_dev)) {
		LOG_ERR("UART device not found!");
		return -1;
	}

#if defined(CONFIG_BT_PERIPHERAL)
	int ret = rak_ble_peripheral_init();
	if (ret) {
		LOG_ERR("Failed to init ble peripheral: %d", ret);
		return -1;
	}
#endif

	while (1) {
		// pm_device_action_run(uart_dev, PM_DEVICE_ACTION_RESUME);
		print_uart("Hello! Uart Sleep Test.\r\n");
		// pm_device_action_run(uart_dev, PM_DEVICE_ACTION_SUSPEND);

		k_sleep(K_USEC(DT_PROP(DT_NODELABEL(light_sleep), min_residency_us) + 50UL));
		// k_msleep(10000);

	}

	return 0;
}
