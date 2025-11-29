#include <zephyr/kernel.h>

/* Do not use this file at your production code!!! */

#if (CONFIG_LOG && CONFIG_USE_SEGGER_RTT)
#include <SEGGER_RTT.h>
#define LOG_FLUSH()                                                                                \
	while (((CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) == 1) &&                        \
	       (SEGGER_RTT_HasDataUp(0) > 0)) {                                                    \
	}
#else
#define LOG_FLUSH() (void)0
#endif

#define RTT_THREAD_STACKSIZE 256
#define RTT_THREAD_PRIORITY  10

void rtt_thread_handler(void)
{
	while (1) {
		LOG_FLUSH(); // Wait for RTT buffer to clear
		k_msleep(1000);
	}
}
K_THREAD_DEFINE(rtt_thread_id, RTT_THREAD_STACKSIZE, rtt_thread_handler, NULL, NULL, NULL,
		RTT_THREAD_PRIORITY, 0, 0);
