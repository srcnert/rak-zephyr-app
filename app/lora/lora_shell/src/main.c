#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(green_led), gpios);

int main(void)
{

	if (!gpio_is_ready_dt(&led)) {
		LOG_ERR("LED is not ready!");
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

	LOG_INF("Shell! %s", CONFIG_BOARD);

	return 0;
}
