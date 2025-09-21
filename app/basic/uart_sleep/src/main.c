#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/pm/device.h>

#include "rak_ble_peripheral.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/*
 * Get LoRa device
 */
static const struct device *lora_dev = DEVICE_DT_GET(DT_ALIAS(lora0));

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
	if (!device_is_ready(lora_dev)) {
		LOG_ERR("LoRa device not found!");
		return -1;
	}

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
		pm_device_action_run(uart_dev, PM_DEVICE_ACTION_RESUME);
		print_uart("Hello! Uart Sleep Test.\r\n");
		pm_device_action_run(uart_dev, PM_DEVICE_ACTION_SUSPEND);

		k_msleep(10000);
	}

	return 0;
}
