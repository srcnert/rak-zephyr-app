Overview
********

The lora shell example helps to test LoRa modules with following commands:

'lora config': Configure the LoRa radio
               Usage: config [freq <Hz>] [tx-power <dBm>] [bw <kHz>] [sf <int>]
               [cr <int>] [pre-len <int>]

'lora send': Send LoRa packet
             Usage: send <data>

'lora recv': Receive LoRa packet
             Usage: recv [timeout (ms)]

'lora test_cw': Send a continuous wave
            Usage: test_cw <freq (Hz)> <power (dBm)> <duration (s)>

Building and Running
********************

Build and flash lora_shell example as follow for your board:

Building for rak3112
--------------------

:zephyr:board:`rak3112` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lora_shell
   :board: rak3112/esp32s3/procpu
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lora_shell
   :board: rak3172
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lora_shell
   :board: rak4631
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/lora/lora_shell
   :board: rak11720
   :goals: build flash
   :west-args: --no-sysbuild

After flashing, the GREEN LED starts with on and off and then, the cli commands
can be used.
