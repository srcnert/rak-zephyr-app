#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/pm/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/lora.h>

#include "ble_peripheral.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

// Even without applying patches, the lowest idle current must be seen within this project!
// If you apply patches, there is no need to enable/disable tx_enable, rx_enable or
// antenna_enable pins.

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(green_led), gpios);

/*
 * Get LoRa device
 */
static const struct device *lora_dev = DEVICE_DT_GET(DT_ALIAS(lora0));

#if defined(CONFIG_BOARD_RAK3172)
static const struct gpio_dt_spec tx_enable = GPIO_DT_SPEC_GET(DT_ALIAS(lora0), tx_enable_gpios);
static const struct gpio_dt_spec rx_enable = GPIO_DT_SPEC_GET(DT_ALIAS(lora0), rx_enable_gpios);
#endif

#if defined(CONFIG_BOARD_RAK4631)
static const struct gpio_dt_spec tx_enable = GPIO_DT_SPEC_GET(DT_ALIAS(lora0), tx_enable_gpios);
static const struct gpio_dt_spec rx_enable = GPIO_DT_SPEC_GET(DT_ALIAS(lora0), rx_enable_gpios);

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

#if defined(CONFIG_BOARD_RAK11720)
static const struct gpio_dt_spec antenna_enable = GPIO_DT_SPEC_GET(DT_ALIAS(lora0), antenna_enable_gpios);
#endif

int main(void) {
	int ret = -1;

#if defined(CONFIG_BOARD_RAK4631)
	configure_uicr();
#endif

#if defined(CONFIG_BT_PERIPHERAL)
	ret = ble_peripheral_init();
	if (ret) {
		LOG_ERR("Failed to init ble peripheral: %d", ret);
	}
#endif

	if (!device_is_ready(lora_dev)) {
		LOG_ERR("%s: device not ready.", lora_dev->name);
	}

#if defined(CONFIG_BOARD_RAK3172)
	ret = gpio_pin_configure_dt(&tx_enable, GPIO_DISCONNECTED);
	if (ret) {
		LOG_ERR("TX enabled pin is not ready!");
	}

	ret = gpio_pin_configure_dt(&rx_enable, GPIO_DISCONNECTED);
	if (ret) {
		LOG_ERR("RX enabled pin is not ready!");
	}
#endif

#if defined(CONFIG_BOARD_RAK4631)
	ret = gpio_pin_configure_dt(&tx_enable, GPIO_DISCONNECTED);
	if (ret) {
		LOG_ERR("TX enabled pin is not ready!");
	}

	ret = gpio_pin_configure_dt(&rx_enable, GPIO_DISCONNECTED);
	if (ret) {
		LOG_ERR("RX enabled pin is not ready!");
	}
#endif

#if defined(CONFIG_BOARD_RAK11720)
	ret = gpio_pin_configure_dt(&antenna_enable, GPIO_DISCONNECTED);
	if (ret) {
		LOG_ERR("Antenna enabled pin is not ready!");
	}
#endif

	if (!gpio_is_ready_dt(&led)) {
		LOG_ERR("LED is not ready!");
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
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

	LOG_INF("Sleep Test! %s", CONFIG_BOARD);
	printk("Sleep Test! %s\n", CONFIG_BOARD);

	while (1) {
		k_sleep(K_FOREVER);
	}

	return 0;
}
