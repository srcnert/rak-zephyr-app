Overview
********

The blinky example blinks an LED forever using the :ref:`GPIO API <gpio_api>`.

The source code shows how to use blue and green leds on RAK19007 base board.

Building and Running
********************

Build and flash Blinky example as follows for your board:

Building for rak3112
--------------------

:zephyr:board:`rak3112` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/blinky
   :board: rak3112/esp32s3/procpu
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/blinky
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/blinky
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak5010
--------------------

:zephyr:board:`rak5010` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/blinky
   :board: rak5010
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11160
---------------------

:zephyr:board:`rak11160` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/blinky
   :board: rak11160
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/blinky
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

After flashing, the LED starts to blink and messages with the current LED state
are printed on the console.
