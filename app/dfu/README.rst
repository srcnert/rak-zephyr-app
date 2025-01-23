Overview
********

This sample application implements DFU process with 
the MCUmgr management protocol.
For more information about MCUmgr and SMP, please see :ref:`device_mgmt`.

This sample application supports the following mcumgr transports:

    * UART/USB
    * Bluetooth

Caveats
*******

* The MCUboot bootloader is required for ``img_mgmt`` to function
  properly. More information about the Device Firmware Upgrade subsystem and
  MCUboot can be found in :ref:`mcuboot`.

Prerequisites
*************

Use of a tool
=============

To interact remotely with the management subsystem on a device, a tool is required to interact with
it. There are various tools available which are listed on the :ref:`mcumgr_tools_libraries` page
of the Management subsystem documentation.

For simplified commands, please check mcuboot.md file.

Building and flashing MCUboot
*****************************

The below steps describe how to build and run the MCUboot bootloader.
Detailed instructions can be found in the :ref:`mcuboot` documentation page.

The Zephyr port of MCUboot is essentially a normal Zephyr application, which means that
it can be built and flashed like normal using ``--sysbuild`` arguments.

Building the application
************************

The below steps describe how to build and run the dfu sample in Zephyr. 

Building for rak3172
--------------------

:zephyr:board:`rak3172` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/dfu
   :board: rak3172
   :goals: build flash
   :west-args: --sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_mcuboot.conf"

Building for rak4631
--------------------

:zephyr:board:`rak4631` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/dfu
   :board: rak4631
   :goals: build flash
   :west-args: --sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_mcuboot.conf"

Building for rak11720
---------------------

:zephyr:board:`rak11720` as follows:

.. zephyr-app-commands::
   :zephyr-app: app/dfu
   :board: rak11720
   :goals: build flash
   :west-args: --sysbuild
   :gen-args: -DEXTRA_CONF_FILE="overlay_ble.conf;overlay_mcuboot.conf"

Flashing the sample image
*************************

Upload the :file:`zephyr.signed.bin` file from the previous to image slot-0 of your
board.  See :ref:`flash_map_api` for details on flash partitioning.

To upload the initial image file to an empty slot-0, use ``west flash`` like normal.
``west flash`` will automatically detect slot-0 address and confirm the image.

The *signed* image file needs to be used specifically, otherwise the non-signed version
will be used and the image won't be runnable.

Device Firmware Upgrade (DFU)
*****************************

Now that the SMP server is running on your board and you are able to communicate
with it using :file:`mcumgr`, you might want to test what is commonly called
"OTA DFU", or Over-The-Air Device Firmware Upgrade.

The general sequence of a DFU process is as follows:

* Build an MCUboot enabled application, see :ref:`smp_svr_sample_build`
* Sign the application image, see :ref:`smp_svr_sample_sign`
* Upload the signed image using :file:`mcumgr`
* Listing the images on the device using :file:`mcumgr`
* Mark the uploaded image for testing using :file:`mcumgr`
* Reset the device remotely using :file:`mcumgr`
* Confirm the uploaded image using :file:`mcumgr` (optional)

Upload the signed image
=======================

To upload the signed image, refer to the documentation for your chosen tool, select the new
firmware file to upload and begin the upload.

.. note::

   At the beginning of the upload process, the target might start erasing
   the image slot, taking several dozen seconds for some targets.

List the images
===============

A list of images (slot-0 and slot-1) that are present can now be obtained on the remote target device using
the tool of your choice, which should print the status and hash values of each of the images
present.

Test the image
==============

In order to instruct MCUboot to swap the images, the image needs to be tested first, making sure it
boots, see the instructions in the tool of your choice. Upon reboot, MCUBoot will swap to the new
image.

.. note::
   There is not yet any way of getting the image hash without actually uploading the
   image and getting the hash.

Reset remotely
==============

The device can be reset remotely to observe (use the console output) how MCUboot swaps the images,
check the documentation in the tool of your choice. Upon reset MCUboot will swap slot-0 and
slot-1.

Confirm new image
=================

The new image is now loaded into slot-0, but it will be swapped back into slot-1 on the next
reset unless the image is confirmed. Confirm the image using the tool of your choice.

Note that if you try to send the very same image that is already flashed in
slot-0 then the procedure will not complete successfully since the hash values
for both slots will be identical.
