#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/shell/shell.h>
#include <zephyr/sys/printk.h>

static int cmd_test_example(const struct shell *shell, size_t argc, char *argv[])
{
	shell_print(shell, "Board: %s", CONFIG_BOARD);
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(test_cmds,

			       SHELL_CMD_ARG(test, NULL, "trigger a test command", cmd_test_example,
					     0 /* mandatory param */, 0 /* optional param */),

			       SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(rak, &test_cmds, "RAKwireless", NULL);
