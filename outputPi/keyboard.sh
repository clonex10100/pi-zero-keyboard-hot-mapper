#!/bin/bash
# Taken from https://gist.github.com/rmed/0d11b7225b3b772bb0dd89108ee93df0 and modified.
# Credit to rmed

# Script to create a keyboard gadget on the Raspberry Pi Zero
# and send some keys to the connected host.

# Create gadget
mkdir /sys/kernel/config/usb_gadget/mykeyboard
cd /sys/kernel/config/usb_gadget/mykeyboard

# Add basic information
echo 0x0100 > bcdDevice # Version 1.0.0
echo 0x0200 > bcdUSB # USB 2.0
echo 0x00 > bDeviceClass
echo 0x00 > bDeviceProtocol
echo 0x00 > bDeviceSubClass
echo 0x08 > bMaxPacketSize0
echo 0x0104 > idProduct # Multifunction Composite Gadget
echo 0x1d6b > idVendor # Linux Foundation

# Create English locale
mkdir strings/0x409

echo "Noah Evans" > strings/0x409/manufacturer
echo "Keyboard Remapper" > strings/0x409/product
echo "0123456789" > strings/0x409/serialnumber

# Create HID function
mkdir functions/hid.usb0

echo 1 > functions/hid.usb0/protocol
echo 8 > functions/hid.usb0/report_length # 8-byte reports
echo 1 > functions/hid.usb0/subclass

cp /home/pi/report_desc functions/hid.usb0/

# Create configuration
mkdir configs/c.1
mkdir configs/c.1/strings/0x409

echo 0x80 > configs/c.1/bmAttributes
echo 200 > configs/c.1/MaxPower # 200 mA
echo "Example configuration" > configs/c.1/strings/0x409/configuration

# Link HID function to configuration
ln -s functions/hid.usb0 configs/c.1

# Enable gadget
ls /sys/class/udc > UDC

sleep 10

function write_report {
    echo -ne $1 > /dev/hidg0
    echo -ne "\0\0\0\0\0\0\0\0" > /dev/hidg0
}

#Type "Ready"
write_report "\x20\0\x15\0\0\0\0\0"
write_report "\0\0\x08\0\0\0\0\0"
write_report "\0\0\x04\0\0\0\0\0"
write_report "\0\0\x07\0\0\0\0\0"
write_report "\0\0\x1c\0\0\0\0\0"
