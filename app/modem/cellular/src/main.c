#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>

#include "rak_ble_peripheral.h"
#include "rak_modem.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);


int main(void) {
	int ret = -1;

#if defined(CONFIG_BT_PERIPHERAL)
	ret = rak_ble_peripheral_init();
	if (ret) {
		LOG_ERR("Failed to init ble peripheral: %d", ret);
	}
#endif

	ret = rak_modem_disable_gps_power();
	if (ret) {
		LOG_ERR("Failed to disable gps: %d", ret);
	}

	ret = rak_modem_init();
	if (ret) {
		LOG_ERR("Failed to init modem: %d", ret);
	}

	rak_modem_resume();

	ret = rak_modem_if_up();
	if (ret) {
		LOG_ERR("Failed to bring up network interface: %d", ret);
	}

	ret = rak_modem_connect(120);
	if (ret) {
		LOG_ERR("Failed to connect: %d", ret);
	} else {
		rak_modem_info modem_info;
		ret = rak_modem_get_cellular_info(&modem_info);
		if (ret) {
			LOG_ERR("Failed to get cellular info: %d", ret);
		} else {
			rak_modem_print_info(modem_info);
		}
	}

	ret = rak_modem_if_down();
	if (ret) {
		LOG_ERR("Failed to bring down network interface: %d", ret);
	}

	rak_modem_suspend();

	LOG_INF("Cellular Test %s", CONFIG_BOARD);

	while (1) {
		k_sleep(K_FOREVER);
	}

	return 0;
}
