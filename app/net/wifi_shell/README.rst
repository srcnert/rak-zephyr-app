.. zephyr:code-sample:: wifi-shell
   :name: Wi-Fi shell
   :relevant-api: net_stats

   Test Wi-Fi functionality using the Wi-Fi shell module.

Overview
********

This sample allows testing Wi-Fi drivers for various boards by
enabling the Wi-Fi shell module that provides a set of commands:
scan, connect, and disconnect.  It also enables the net_shell module
to verify net_if settings.

Building and Running
********************

Verify the board and chip you are targeting provide Wi-Fi support.


Building for rak3112
--------------------

:zephyr:board:`rak3112` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/net/wife_shell
   :board: rak3112/esp32s3/procpu
   :goals: build flash
   :west-args: --no-sysbuild

Building for rak11160
---------------------

:zephyr:board:`rak11160` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/net/wife_shell
   :board: rak11160
   :goals: build flash
   :west-args: --no-sysbuild

After the board has automatically reset and booted, you should see the following
message in the monitor:

Sample console interaction
==========================

.. code-block:: console

   shell> wifi scan
   Scan requested
   shell>
   Num  | SSID                             (len) | Chan | RSSI | Sec
   1    | kapoueh!                         8     | 1    | -93  | WPA/WPA2
   2    | mooooooh                         8     | 6    | -89  | WPA/WPA2
   3    | Ap-foo blob..                    13    | 11   | -73  | WPA/WPA2
   4    | gksu                             4     | 1    | -26  | WPA/WPA2
   ----------
   Scan request done

   shell> wifi connect "gksu" 4 SecretStuff
   Connection requested
   shell>
   Connected
   shell>
