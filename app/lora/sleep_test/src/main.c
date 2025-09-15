#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/lora.h>

#include "rak_ble_peripheral.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(green_led), gpios);

static void led_init() {
	if (!gpio_is_ready_dt(&led)) {
		LOG_ERR("LED is not ready!");
		return;
	}

	int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		LOG_ERR("Failed to configure LED!");
	}

	ret = gpio_pin_set_dt(&led, 1); // ON
	if (ret) {
		LOG_ERR("Failed to control LED!");
	}
	k_msleep(1000);
	ret = gpio_pin_set_dt(&led, 0); // OFF
	if (ret) {
		LOG_ERR("Failed to control LED!");
	}

	ret = gpio_pin_configure_dt(&led, GPIO_DISCONNECTED);
	if (ret) {
		LOG_ERR("Failed to disconnect LED!");
	}
}

/*
 * Get LoRa device
 */
static const struct device *lora_dev = DEVICE_DT_GET(DT_ALIAS(lora0));

int main(void) {
#if defined(CONFIG_BT_PERIPHERAL)
	int ret = rak_ble_peripheral_init();
	if (ret) {
		LOG_ERR("Failed to init ble peripheral: %d", ret);
		return -1;
	}
#endif

	if (!device_is_ready(lora_dev)) {
		LOG_ERR("%s: device not ready.", lora_dev->name);
		return -1;
	}

	led_init();

	LOG_INF("Sleep Test! %s", CONFIG_BOARD);
	printk("Sleep Test! %s\n", CONFIG_BOARD);

	while (1) {
		k_sleep(K_FOREVER);
	}

	return 0;
}
