#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>

#include "ble_peripheral.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(ble_peripheral, LOG_LEVEL_INF);

#define DEVICE_NAME			CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN		(sizeof(DEVICE_NAME) - 1)

#define BT_GAP_ADV_FAST_INT_MIN 1600  /* 1000 ms   */
#define BT_GAP_ADV_FAST_INT_MAX 1600  /* 1000 ms   */
/** Connectable advertising with @ref BT_LE_ADV_OPT_CONN */
#define BT_LE_ADV_CUSTOM BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONN, \
									BT_GAP_ADV_FAST_INT_MIN, \
									BT_GAP_ADV_FAST_INT_MAX, \
									NULL)

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

static void adv_start_work_handler(struct k_work *work) {
	bt_le_adv_stop();

	int err = bt_le_adv_start(BT_LE_ADV_CUSTOM, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)", err);
		return;
	}

	LOG_INF("Advertising successfully started");
}
K_WORK_DEFINE(adv_start_work, adv_start_work_handler);

static void mtu_updated(struct bt_conn *conn, uint16_t tx, uint16_t rx)
{
	printk("Updated MTU: TX: %d RX: %d bytes\n", tx, rx);
}

static struct bt_gatt_cb gatt_callbacks = {
	.att_mtu_updated = mtu_updated
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed, err 0x%02x %s\n", err, bt_hci_err_to_str(err));
	} else {
		printk("Connected\n");
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected, reason 0x%02x %s\n", reason, bt_hci_err_to_str(reason));
	k_work_submit(&adv_start_work);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};

static void bt_ready_handler(int err) {
	if (err) {
		LOG_ERR("Ble peripheral init failed (err %d)", err);
		return;
	}

	bt_gatt_cb_register(&gatt_callbacks);
	k_work_submit(&adv_start_work);
}

int ble_peripheral_init(void) {
	int err = bt_enable(bt_ready_handler);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return err;
	}

	return err;
}
