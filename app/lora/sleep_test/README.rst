Overview
********

The project shows how to reach lowest idle current for RAKwireless LoRa modules
and Zephyr OS.

RAK3112 module do not support PM. This example shows how to set deep sleep for
RAK3112 module.

Building and Running
********************

This application can be built and executed as follows:

Building for rak3112
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/sleep_test
   :board: rak3112/esp32s3/procpu
   :goals: build flash
   :west-args: --sysbuild

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/sleep_test
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_sleep_rak3172.conf"

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/sleep_test
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_sleep_rak4631.conf"

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/sleep_test
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_sleep_rak11720.conf"
