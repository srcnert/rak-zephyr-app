#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#if !DT_HAS_COMPAT_STATUS_OKAY(st_lis3dh)
#error "No st,lis3dh compatible node found in the device tree"
#endif

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(st_lis3dh);
	int ret;

	if (!device_is_ready(dev)) {
		printf("Device %s is not ready\n", dev->name);
		return 0;
	}

	while (1) {
		struct sensor_value accel[3];

		ret = sensor_sample_fetch(dev);
		if (ret == 0) {
			ret = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ,
						accel);
		}

		if (ret != 0) {
			printf("RAK1904(LIS3DH): failed: %d\n", ret);
			break;
		}

		printf("RAK1904(LIS3DH): %.2f m/s^2 ; %.2f m/s^2 ; %.2f m/s^2\n",
				sensor_value_to_double(&accel[0]),
				sensor_value_to_double(&accel[1]),
				sensor_value_to_double(&accel[2]));

		k_sleep(K_MSEC(2000));
	}

	return 0;
}
