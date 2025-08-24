Overview
********

The blinky example blinks an LED forever using the :ref:`GPIO API <gpio_api>`.

The source code shows how to use blue and green leds on RAK19007 base board.

Building and Running
********************

Build and flash Blinky as follows for your board:

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

After flashing, the LED starts to blink and messages with the current LED state
are printed on the console.
