Overview
********

A simple sample that can be used with RAKwireless LoRa modules and
prints "Hello World" to the console. The example provides a way to use
RAK19007 base board's USB-C port.

Please check overlay files to get detailed information for diferent boards.

Building and Running
********************

This application can be built and executed as follows:

Building for rak3112
--------------------

:zephyr:board:`rak3112` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/hello_world
   :board: rak3112/esp32s3/procpu
   :goals: build flash
   :west-args: --no-sysbuild

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

Building for rak5010
--------------------

:zephyr:board:`rak5010` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/hello_world
   :board: rak5010
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11160
---------------------

:zephyr:board:`rak11160` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/hello_world
   :board: rak11160
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
