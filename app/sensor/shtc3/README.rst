Overview
********

This sample application periodically (2 Hz) measures the ambient
temperature and humidity. The result is written to the console.

References
**********

 - `RAK1901 sensor <https://store.rakwireless.com/products/rak1901-shtc3-temperature-humidity-sensor?srsltid=AfmBOor7X4-RTG4Dm4S73nG4nOUBOrKoDRkf_7FxUK6xMWYAksMGRyh1/>`_

Building and Running
********************

This project outputs SHTC3 sensor (RAK1901) data to the console.
It requires a RAK1901 sensor to connected to RAK19007 base board.

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/shtc3
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/shtc3
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/shtc3
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

Sample Output
=============

.. code-block:: console

   SHTC3(RAK1901): 19.64 Cel ; 41.96 %RH
   SHTC3(RAK1901): 19.74 Cel ; 42.06 %RH
   SHTC3(RAK1901): 19.75 Cel ; 42.08 %RH
