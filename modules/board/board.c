#include <zephyr/kernel.h>
#include <zephyr/init.h>

static int configure_uicr(void) {
	if ((NRF_UICR->REGOUT0 & UICR_REGOUT0_VOUT_Msk) !=
		(UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos)) {
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
		while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

		NRF_UICR->REGOUT0 = (NRF_UICR->REGOUT0 & ~((uint32_t)UICR_REGOUT0_VOUT_Msk)) |
							(UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos);

		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
		while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

		// System reset is needed to update UICR registers.
		NVIC_SystemReset();
	}

	return 0;
}

SYS_INIT(configure_uicr, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
