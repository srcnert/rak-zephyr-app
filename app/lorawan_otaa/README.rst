Overview
********

An application to demonstrate how to combine all sample examples and 
how to use the :ref:`LoRaWAN subsystem <lorawan_api>` of Zephyr.

The sample joins a LoRaWAN network and send RAK19007 LiPo battery voltage,
RAK1901(SHTC3) sensor's the ambient temperature and humidity values 
at every three minutes periodically with following json format: 

{temp:2134,hum:5648,batt:4123}

It is also possible to use mcuboot bootloader with using ``--sysbuild`` arguments.
rak4631 is able to update over USB/Bluetooth and rak11720 is able to update over
Bluetooth. It is not possible to update rak3172 module due to its low ROM area!

The sample also must reach lowest idle current which are x.xuA for rak3172 + rak19007,
x.xuA for rak4631 + rak19007 and x.xuA for rak11720 + rak19007.

Building and Running
********************

Before building the sample, make sure to select the correct region in the
``prj.conf`` file.

The following commands build and flash the sample.

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lorawan_otaa
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_sleep_rak3172.conf"

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lorawan_otaa
   :board: rak4631
   :goals: build flash
   :west-args: --sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_mcuboot.conf:overlay_sleep_rak4631.conf"

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lorawan_otaa
   :board: rak11720
   :goals: build flash
   :west-args: --sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_mcuboot.conf:overlay_sleep_rak11720.conf"
