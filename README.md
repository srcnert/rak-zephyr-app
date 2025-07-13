RAKwireless Zephyr Applications
===

This project is prepared to use RAKwireless LoRa modules with Zephyr project. This repo is prepared to use RAK3172, RAK4631 and RAK11720 stamp modules. All sample projects are tested on RAK19007 Wisblock base board.

The main idea of the repo is inspired by https://github.com/zephyrproject-rtos/example-application.

### Initialization
Before starting initialization, please install VsCODE, GIT, J-LINK and NRFUTIL programs for your operating system.

After that, you must install toolchain via:

```shell
# Install tools for managing and using toolchains:
nrfutil install device
nrfutil install toolchain-manager
# Install a specific version toolchain:
nrfutil toolchain-manager install --ncs-version v3.0.2
# List your currently installed toolchain and learn its path:
nrfutil toolchain-manager list
# Launch toolchain commands in the environment directly:
nrfutil toolchain-manager launch --terminal
# Go to setup path:
cd <go to destination you wanna setup rak-zephyr-workspace>
# Initialize rak-zephyr-workspace:
west init -m https://github.com/srcnert/rak-zephyr-app rak-zephyr-workspace
# Update zephyr modules:
cd rak-zephyr-workspace
west update
```

This is the easier way to set up a toolchain for Zephyr RTOS or nRF Connect SDK for RAK4631(nRF52840 + SX1262) or any other boards.

Second way is to follow up Zephyr RTOS guide:
https://docs.zephyrproject.org/latest/develop/getting_started/index.html

### Patch
To patch addressed issues, run the following command:
```shell
cd rak-zephyr-app
west -v patch apply
```

To revert applied patches:
```shell
west -v patch clean
```

To list patch files:
```shell
west patch list
```

### Building and running
To build an application, open '../rak-zephyr-workspace/rak-zephyr-app' directory on your Visual Studio Code app. After that, please open '../.vscode/settings.json' file and set following parameters:

```shell
"ZEPHYR_WORKSPACE": "/your/path/to/rak-zephyr-workspace",

"TOOLCHAIN_BASE":   "/your/path/to/toolchains/0123456789",
"JLINK_PATH":       "/your/path/to/JLink_V123",
"MCUMGR_PATH":      "/your/path/to/go/bin"
```

*** McuMgr is necessary to use mcumgr commands. Please check dfu application for details.

Please run 'west patch apply' command to fix following problems:
- Rak3172 i2c is not working correctly with PM. https://github.com/zephyrproject-rtos/zephyr/issues/37414
- Adding RTT support for Rak11720.
- Fixing Apollo3's adc problem.
- Fixing build problem if PM and GPIO is used together for apollo3.
- Sx1262 idle current problem.
- Fixing wrongly defined clock settings and RF controller pins. https://github.com/zephyrproject-rtos/zephyr/pull/86037

You can build your project via 'VsCode --> Terminal --> Run Build Task' option.
For example, if you wanna build 'app/adc' example for rak3172, please select following options:
- Select the board: rak3172
- Select the build type: --no-sysbuild
- Select the ble overlay: no_overlay.conf
- Select the mcuboot overlay: no_overlay.conf
- Select the sleep overlay: no_overlay.conf
- Select the project: app/adc

For example, if you wanna build 'app/lorawan_otaa' example for rak11720, please select following options:
- Select the board: rak11720
- Select the build type: --sysbuild
- Select the ble overlay: overlay_ble.conf
- Select the mcuboot overlay: overlay_mcuboot.conf
- Select the sleep overlay: overlay_sleep_rak11720.conf
- Select the project: app/lorawan_otaa

The overlay files can be selected according to your request. Whole sample examples are tested on Rak19007 base board. J-Link is used to program stamp modules.

To program your board, please use 'VsCode --> Terminal --> Run Task --> flash' option.
