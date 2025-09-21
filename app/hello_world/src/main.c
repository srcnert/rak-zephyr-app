#include <zephyr/kernel.h>

int main(void)
{
	while (1) {
		printk("Hello World! %s\n", CONFIG_BOARD);
		k_sleep(K_MSEC(1000));
	}

	return 0;
}
