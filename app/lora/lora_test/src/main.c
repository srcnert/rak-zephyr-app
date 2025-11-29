#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/lora.h>
#include <zephyr/drivers/regulator.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#if defined(CONFIG_BOARD_RAK11160)
/*
 * Get ESP8684 enable regulator
 */
static const struct device *esp = DEVICE_DT_GET(DT_NODELABEL(esp8684_enable));
#endif

/*
 * Get LED GPIO
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(green_led), gpios);

/*
 * Get LoRa device
 */
static const struct device *lora_dev = DEVICE_DT_GET(DT_ALIAS(lora0));

static struct lora_modem_config modem_config = {
	.frequency = 868000000,
	.bandwidth = BW_125_KHZ,
	.datarate = SF_10,
	.coding_rate = CR_4_5,
	.preamble_len = 8,
	.iq_inverted = false,
	.public_network = false,
	.tx_power = 22,
	.tx = true,
};

#define MAX_DATA_LEN 12
char data[MAX_DATA_LEN] = {'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', ' ', '0'};

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
	int ret;

#if defined(CONFIG_BOARD_RAK11160)
	// Suspend ESP MCU
	ret = regulator_disable(esp);
	if (ret) {
		LOG_ERR("Failed to suspend esp: %d", ret);
	}
#endif

	ret = lora_config(lora_dev, &modem_config);
	if (ret < 0) {
		LOG_ERR("LoRa config failed");
		return ret;
	}

	led_init();
	LOG_INF("LoRa Output Power Test: %s", CONFIG_BOARD);

	while (1) {
		/* Send TX Message */
		modem_config.tx = true;

		ret = lora_send(lora_dev, data, MAX_DATA_LEN);
		if (ret < 0) {
			LOG_ERR("LoRa send failed: %i", ret);
		}

		k_msleep(5000);

		/* Wait for Receiving Message */
		char buf[0xff];
		int16_t rssi;
		int8_t snr;

		modem_config.tx = false;

		/* Block until data arrives */
		ret = lora_recv(lora_dev, buf, sizeof(buf), K_MSEC(2000), &rssi, &snr);
		if (ret < 0) {
			LOG_ERR("LoRa recv failed: %i", ret);

		} else {
			LOG_INF("RSSI: %" PRIi16 " dBm, SNR:%" PRIi8 " dBm", rssi, snr);
		}

		k_msleep(5000);
	}

	return 0;
}
