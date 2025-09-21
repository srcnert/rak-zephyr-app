#ifndef RAK_MODEM_H__
#define RAK_MODEM_H__

#include <zephyr/drivers/cellular.h>

#define MODEM_CELLULAR_DATA_LEN              (16)
#define MODEM_CELLULAR_DATA_IMEI_LEN         (16)
#define MODEM_CELLULAR_DATA_MODEL_ID_LEN     (65)
#define MODEM_CELLULAR_DATA_IMSI_LEN         (23)
#define MODEM_CELLULAR_DATA_ICCID_LEN        (22)
#define MODEM_CELLULAR_DATA_MANUFACTURER_LEN (65)
#define MODEM_CELLULAR_DATA_FW_VERSION_LEN   (65)

typedef struct {
	enum cellular_registration_status reg_status;
	int16_t rssi;
	uint8_t imei[MODEM_CELLULAR_DATA_IMEI_LEN];
	uint8_t model_id[MODEM_CELLULAR_DATA_MODEL_ID_LEN];
	uint8_t manufacturer[MODEM_CELLULAR_DATA_MANUFACTURER_LEN];
	uint8_t imsi[MODEM_CELLULAR_DATA_IMSI_LEN];
	uint8_t iccid[MODEM_CELLULAR_DATA_ICCID_LEN];
	uint8_t fw_version[MODEM_CELLULAR_DATA_FW_VERSION_LEN];
} rak_modem_info;

int rak_modem_init(void);
int rak_modem_connect(int timeout_sec);
int rak_modem_disable_gps_power();
void rak_modem_resume();
void rak_modem_suspend();
int rak_modem_if_up();
int rak_modem_if_down();
int rak_modem_get_cellular_info(rak_modem_info *modem_info);
void rak_modem_print_info(rak_modem_info info);

#endif
