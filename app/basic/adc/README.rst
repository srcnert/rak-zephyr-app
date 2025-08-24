Overview
********

This sample demonstrates how to use the :ref:`ADC driver API <adc_api>`.

The project reads ADC samples from one channel and prints
the readings on the RTT console.

The pins of the ADC channels are board-specific. Please check the boards
overlay file for further details.

Please also aware that, if rak19007 board is used as a base board,
- no battery, USB connected
	* meaningless value, you read the Vout of the TP4054 in none-charging mode
- battery, USB connected
	* meaningless value, you read the charging voltage of the TP4054
- battery, USB not connected
	* battery voltage reading

Due to this, RTT logging is used, please do not connect your usb line
to get correct ADC results!

Building and Running
********************

Configuration of channels (settings like gain, reference, or acquisition time)
also needs to be specified in devicetree, in ADC controller child nodes. Also
the ADC resolution and oversampling setting (if used) need to be specified
there. See :zephyr_file:`boards/3172.overlay`, :zephyr_file:`boards/rak4631.overlay`,
:zephyr_file:`boards/rak5010.overlay` or :zephyr_file:`boards/11720.overlay` for an example of such setup.

The sample can be built and executed as follows:

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/adc
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/adc
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak5010
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/basic/adc
   :board: rak5010
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/adc
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

Sample output
=============

You should get a similar output on RTT console as below, repeated every second:

.. code-block:: console

   V_BAT: 4123 mV
