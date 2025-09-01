#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>

#include "rak_ble_peripheral.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(ble_peripheral, LOG_LEVEL_INF);

#define DEVICE_NAME			CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN		(sizeof(DEVICE_NAME) - 1)

/* Advertising data */
static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
	BT_DATA_BYTES(BT_DATA_SVC_DATA16,
				0xaa, 0xfe, /* Eddystone UUID */
				0x10, /* Eddystone-URL frame type */
				0x00, /* Calibrated Tx power at 0m */
				0x01, /* URL Scheme Prefix https://www. */
				'r', 'a', 'k',
				'w', 'i', 'r', 'e', 'l', 'e', 's', 's',
				0x07 /* .com */
			)
};

/* Scan response data */
static const struct bt_data sd[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN)
};

static void adv_stop_work_handler(struct k_work *work) {
	LOG_INF("Advertising stopped");
	bt_le_adv_stop();
}
static K_WORK_DELAYABLE_DEFINE(adv_stop_work, adv_stop_work_handler);

static void adv_start_work_handler(struct k_work *work) {
	bt_le_adv_stop();

	int err = bt_le_adv_start(BT_LE_ADV_NCONN_IDENTITY, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)", err);
		return;
	}

	LOG_INF("Advertising successfully started");
	k_work_reschedule(&adv_stop_work, K_SECONDS(1));
}
K_WORK_DEFINE(adv_start_work, adv_start_work_handler);

static void bt_ready_handler(int err) {
	if (err) {
		LOG_ERR("Ble peripheral init failed (err %d)", err);
		return;
	}

	k_work_submit(&adv_start_work);
}

int rak_ble_peripheral_init(void) {
	int err = bt_enable(bt_ready_handler);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return err;
	}

	return err;
}
