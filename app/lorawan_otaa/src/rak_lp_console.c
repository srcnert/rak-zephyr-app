#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/pm/device.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(rak_lp_console, LOG_LEVEL_DBG);

int rak_lp_console_init()
{
	const struct device *const dev =
		DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

	if (!device_is_ready(dev)) {
		LOG_ERR("Console device not ready");
		return -1;
	}

#if CONFIG_PM_DEVICE
	/* In PM_DEVICE modes, enable device as a wakeup source will prevent
	 * system to switch it off (clock off, set pins to sleep configuration, ...)
	 * It is not requested in CONFIG_PM mode only as in this case, device is not
	 * suspended before stop mode entry.
	 */

	bool ret;

	ret = pm_device_wakeup_is_capable(dev);
	if (!ret) {
		LOG_ERR("Device is not wakeup capable");
		return -1;
	} else {
		LOG_INF("Device is wakeup capable");

		ret = pm_device_wakeup_enable(dev, true);
		if (!ret) {
			LOG_ERR("Could not enable wakeup source");
			return -1;
		} else {
			LOG_INF("Wakeup source enable ok");
		}

		ret = pm_device_wakeup_is_enabled(dev);
		if (!ret) {
			LOG_ERR("Wakeup source not enabled");
			return -1;
		} else {
			LOG_INF("Wakeup source enabled");
		}
	}
#endif

	return 0;
}
