#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/*
 * Get LED GPIO
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(green_led), gpios);

static void led_init()
{
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

int main(void)
{
	led_init();

	LOG_INF("LoRa Shell! %s", CONFIG_BOARD);

	return 0;
}
