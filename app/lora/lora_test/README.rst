Overview
********

This sample demonstrates how to use the LoRa radio driver to configure
the encoding settings and send/receive data over the radio.

Building and Running
********************

Build and flash lora_test example as follow for your board:

Building for rak3112
--------------------

:zephyr:board:`rak3112` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lora_test
   :board: rak3112/esp32s3/procpu
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lora_test
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lora_test
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11160
---------------------

:zephyr:board:`rak11160` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lora_test
   :board: rak11160
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lora_test
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

After flashing, the GREEN LED starts with on and off and then, the LoRa
tranmission will be started.
