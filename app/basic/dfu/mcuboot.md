### How to use MCUMGR:

# Updating MCU over UART
Firstly, go must be installed. After that, mcumgr can be installed
via following command:
```shell
go install github.com/apache/mynewt-mcumgr-cli/mcumgr@latest
```

mcumgr path can be find via following command:
```shell
go env GOPATH
```

To test, send a string to the remote target device and have it echo it back:
```shell
mcumgr version
mcumgr --conntype serial --connstring "/dev/cu.usbserial-130,baud=115200" echo hello
```

Other commands to update mcu:
```shell
mcumgr --conntype serial --connstring <connection string> image upload ../build/dfu/zephyr/zephyr.signed.bin
mcumgr --conntype serial --connstring <connection string> image list
mcumgr --conntype serial --connstring <connection string> image confirm <hash of slot-1 image>
mcumgr --conntype serial --connstring <connection string> reset
```
