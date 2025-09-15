#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
	while (1) {
		printk("Hello World! %s\n", CONFIG_BOARD);
		k_sleep(K_MSEC(1000));
	}

	return 0;
}
