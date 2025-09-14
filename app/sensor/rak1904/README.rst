Overview
********

This sample application periodically (0.5 Hz) measures the 3 axis accelerometer.
The result is written to the console.

References
**********

 - `RAK1904 sensor <https://store.rakwireless.com/products/rak1904-lis3dh-3-axis-acceleration-sensor/>`_

Building and Running
********************

This project outputs RAK1904 sensor (LIS3DH) data to the console.
It requires a RAK1904 sensor to connected to RAK19007 base board.

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/sensor/rak1904
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/sensor/rak1904
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/sensor/rak1904
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

Sample Output
=============

.. code-block:: console

   RAK1904(LIS3DH): 0.1 m/s^2 ; 0.1 m/s^2 ; 0.9 m/s^2
