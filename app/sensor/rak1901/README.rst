Overview
********

This sample application periodically (0.5 Hz) measures the ambient
temperature and humidity. The result is written to the console.

References
**********

 - `RAK1901 sensor <https://store.rakwireless.com/products/rak1901-shtc3-temperature-humidity-sensor?srsltid=AfmBOor7X4-RTG4Dm4S73nG4nOUBOrKoDRkf_7FxUK6xMWYAksMGRyh1/>`_
 - `RAK5010 board internal sensor <https://docs.rakwireless.com/product-categories/wistrio/rak5010-m/datasheet/#system-on-a-chip-socs-and-sensors>`

Building and Running
********************

This project outputs RAK1901 sensor (SHTC3) data to the console.
It requires a RAK1901 sensor to connected to RAK19007 base board.

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/sensor/rak1901
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/sensor/rak1901
   :board: rak4631, rak5010
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/sensor/rak1901
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

Sample Output
=============

.. code-block:: console

   RAK1901(SHTC3): 19.64 Cel ; 41.96 %RH
   RAK1901(SHTC3): 19.74 Cel ; 42.06 %RH
   RAK1901(SHTC3): 19.75 Cel ; 42.08 %RH
