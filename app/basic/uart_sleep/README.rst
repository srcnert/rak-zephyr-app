Overview
********

The UART sleep example shows how to use Zephyr PM api with RAK Wisduo modules.

The source code shows how to send UART messages with low power requirments.

Building and Running
********************

Build and flash Blinky as follows for your board:

Building for rak3112
--------------------

:zephyr:board:`rak3112` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/blinky
   :board: rak3172
   :goals: build flash
   :west-args: --sysbuild

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/blinky
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/blinky
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/blinky
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

After flashing, UART messages will be sended over selected UART port at every
10 seconds.
