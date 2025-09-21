Overview
********

The UART sleep example shows how to use Zephyr PM api with RAK Wisduo modules.

The source code shows how to send UART messages with low power requirments.

(RAK3112 module is not supported for this example!)

Building and Running
********************

Build and flash Blinky as follows for your board:

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/uart_sleep
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/uart_sleep
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/uart_sleep
   :board: rak11720
   :goals: build flash
   :gen-args: -DEXTRA_CONF_FILE=overlay_ble.conf
   :west-args: --no-sysbuild

After flashing, UART messages will be sended over selected UART port at every
10 seconds and then UART peripheral is suspended.
