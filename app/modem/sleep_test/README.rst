Overview
********

The project shows how to reach lowest idle current for RAKwireless RAK5010 board
on Zephyr OS.

Building and Running
********************

This application can be built and executed as follows:

Building for rak5010
--------------------

:zephyr:board:`rak5010` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/modem/sleep_test
   :board: rak5010
   :goals: build flash
   :west-args: --no-sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_sleep_rak5010.conf"
