#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_shtcx)
#error "No sensirion,shtcx compatible node found in the device tree"
#endif

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(sensirion_shtcx);
	int ret;

	if (!device_is_ready(dev)) {
		printf("Device %s is not ready\n", dev->name);
		return 0;
	}

	while (1) {
		struct sensor_value temp, hum;

		ret = sensor_sample_fetch(dev);
		if (ret == 0) {
			ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP,
						&temp);
		}
		if (ret == 0) {
			ret = sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY,
						&hum);
		}
		if (ret != 0) {
			printf("RAK1901(SHTC3): failed: %d\n", ret);
			break;
		}

		printf("RAK1901(SHTC3): %.2f Cel ; %0.2f %%RH\n",
				sensor_value_to_double(&temp),
				sensor_value_to_double(&hum));

		k_sleep(K_MSEC(2000));
	}

	return 0;
}
