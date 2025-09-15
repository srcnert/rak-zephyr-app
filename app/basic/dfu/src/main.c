#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/pm/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/lora.h>

#include "rak_ble_peripheral.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
#if defined(CONFIG_BT_PERIPHERAL)
	int ret = rak_ble_peripheral_init();
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
