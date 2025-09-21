#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/pm/device.h>
#include <zephyr/pm/device_runtime.h>
#include <zephyr/drivers/regulator.h>

#include "rak_ble_peripheral.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(green_led), gpios);

static void led_init()
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

	ret = gpio_pin_configure_dt(&led, GPIO_DISCONNECTED);
	if (ret) {
		LOG_ERR("Failed to disconnect LED!");
	}
}

// Modem Devices
static const struct device *mdm = DEVICE_DT_GET(DT_ALIAS(modem));
static const struct device *mdm_uart = DEVICE_DT_GET(DT_ALIAS(modem_uart));
static const struct device *gps = DEVICE_DT_GET(DT_NODELABEL(gps_pwr));

// Sensor Devices
static const struct device *sensor_temp = DEVICE_DT_GET(DT_ALIAS(temp_sensor));
static const struct device *sensor_light = DEVICE_DT_GET(DT_ALIAS(light_sensor));
static const struct device *sensor_accel = DEVICE_DT_GET(DT_ALIAS(accel_sensor));
static const struct device *sensor_press = DEVICE_DT_GET(DT_ALIAS(press_sensor));

int main(void)
{
	int ret = -1;

#if defined(CONFIG_BT_PERIPHERAL)
	ret = rak_ble_peripheral_init();
	if (ret) {
		LOG_ERR("Failed to init ble peripheral: %d", ret);
	}
#endif

	// Suspend all sensors and BG95 modem
	ret = pm_device_action_run(sensor_temp, PM_DEVICE_ACTION_SUSPEND);
	if (ret) {
		LOG_ERR("Failed to suspend temp sensor: %d", ret);
	}

	ret = pm_device_action_run(sensor_light, PM_DEVICE_ACTION_SUSPEND);
	if (ret) {
		LOG_ERR("Failed to suspend light sensor: %d", ret);
	}

	ret = pm_device_action_run(sensor_accel, PM_DEVICE_ACTION_SUSPEND);
	if (ret) {
		LOG_ERR("Failed to suspend accel sensor: %d", ret);
	}

	ret = pm_device_action_run(sensor_press, PM_DEVICE_ACTION_SUSPEND);
	if (ret) {
		LOG_ERR("Failed to suspend press sensor: %d", ret);
	}

	// Suspend BG95 modem
	ret = regulator_disable(gps);
	if (ret) {
		LOG_ERR("Failed to suspend gps: %d", ret);
	}

	ret = pm_device_action_run(mdm, PM_DEVICE_ACTION_SUSPEND);
	if (ret) {
		LOG_ERR("Failed to suspend modem: %d", ret);
	}

	ret = pm_device_action_run(mdm_uart, PM_DEVICE_ACTION_SUSPEND);
	if (ret) {
		LOG_ERR("Failed to suspend modem: %d", ret);
	}

	// Set up led
	led_init();

	LOG_INF("Sleep Test! %s", CONFIG_BOARD);
	printk("Sleep Test! %s\n", CONFIG_BOARD);

	while (1) {
		k_sleep(K_FOREVER);
	}

	return 0;
}
