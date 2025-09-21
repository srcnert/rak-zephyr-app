Overview
********

An application to demonstrate how to combine all sample examples and
how to use the :ref:`LoRaWAN subsystem <lorawan_api>` of Zephyr.

The sample joins a LoRaWAN network and send RAK19007 LiPo battery voltage,
RAK1901(SHTC3) sensor's the ambient temperature and humidity values
at every three minutes periodically with following json format:

{temp:2134,hum:5648,batt:4123}

It is also possible to use mcuboot bootloader with using ``--sysbuild`` arg.
RAK3112 and RAK4631 are able to update over USB/Bluetooth and RAK11720 is able
to update over just Bluetooth. The RAK3172 is able to update over just UART.

The sample also must reach lowest idle current.

(RAK3112 does not have low power support. Please do not use PM!)

Building and Running
********************

Before building the sample, make sure to select the correct region in the
``prj.conf`` file.

The following commands build and flash the sample.

Building for rak3112
--------------------

:zephyr:board:`3112` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lorawan_otaa
   :board: rak3112/esp32s3/procpu
   :goals: build flash
   :west-args: --sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_mcuboot.conf"

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lorawan_otaa
   :board: rak3172
   :goals: build flash
   :west-args: --sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_mcuboot.conf;overlay_sleep_rak3172.conf"

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lorawan_otaa
   :board: rak4631
   :goals: build flash
   :west-args: --sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_mcuboot.conf;overlay_sleep_rak4631.conf"

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lorawan_otaa
   :board: rak11720
   :goals: build flash
   :west-args: --sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_mcuboot.conf;overlay_sleep_rak11720.conf"
