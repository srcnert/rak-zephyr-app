Overview
********

This example shows how to use the RAK1904 and a Neuton AI model. The default model determins the orientation
			of the board with the following classes (Note: RAK1904 is installed on the bottom side of the board (Slot D)):
					Class 0 - board is sitting flat on the table
					Class 1 - USB connector is facing up
					Class 2 - board is upside down (bottom if facing up)
					Class 3 - bottom edge of PCB is facing up (side with headers on the base board)

NOTES:
 - The model which is provided will only run on the RAK4631 (Cortex-M4)
 - This code has only been tested with the RAK4631 and likely won't work on other cores

References
**********

 - `RAK1904 sensor <https://store.rakwireless.com/products/rak1904-lis3dh-3-axis-acceleration-sensor/>`_

Building and Running
********************

This project outputs either:
  - The RAK1904 sensor (LIS3DH) data to the console (MODELBUILD mode)
  - The output of the Neuton model (RUTIME mode)

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/ai/neuton
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/ai/neuton
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

Sample Output
=============

.. code-block:: console

   0.15,-0.31,-9.50
