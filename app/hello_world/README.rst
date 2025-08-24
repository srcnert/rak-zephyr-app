Overview
********

A simple sample that can be used with RAKwireless LoRa modules and
prints "Hello World" to the console. The example provides a way to use
RAK19007 base board's USB-C port. For this aim, rak3172 is using LP-UART,
rak4631 and rak5010 arre using USB and RAK11720 is using UART.
Please check overlay files to get detailed information.

Building and Running
********************

This application can be built and executed as follows:

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/hello_world
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/hello_world
   :board: rak4631, rak5010
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/hello_world
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

Sample Output
=============

.. code-block:: console

    Hello World! rak11720/apollo3_blue
