#!/bin/bash
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
echo "Pi zero" > strings/0x409/product
echo "0123456789" > strings/0x409/serialnumber

# Create HID function
mkdir functions/hid.usb0

echo 1 > functions/hid.usb0/protocol
echo 8 > functions/hid.usb0/report_length # 8-byte reports
echo 1 > functions/hid.usb0/subclass
#echo -ne \\x05\\x01\\x09\\x06\\xA1\\x01\\x05\\x07\\x1A\\x24\\x02\\x2A\\x31\\x02\\x14\\x25\\x01\\x75\\x01\\x95\\x08\\x81\\x02\\x95\\x01\\x75\\x08\\x81\\x01\\x95\\x05\\x75\\x01\\x05\\x08\\x19\\x01\\x29\\x05\\x91\\x02\\x95\\x01\\x75\\x03\\x91\\x03\\x95\\x06\\x75\\x08\\x14\\x26\\xFF\\x00\\x05\\x07\\x18\\x2A\\x55\\x02\\x80\\xC0 > functions/hid.usb0/report_desc
cp /home/pi/report_desc functions/hid.usb0/

# Create configuration
mkdir configs/c.1
mkdir configs/c.1/strings/0x409

echo 0x80 > configs/c.1/bmAttributes
echo 200 > configs/c.1/MaxPower # 200 mA
echo "Example configuration" > configs/c.1/strings/0x409/configuration
echo "prelink"
# Link HID function to configuration
ln -s functions/hid.usb0 configs/c.1

# Enable gadget
ls /sys/class/udc > UDC
echo "done"
sleep 10

function write_report {
    echo -ne $1 > /dev/hidg0
    echo -ne "\0\0\0\0\0\0\0\0" > /dev/hidg0
}

# H (press shift and H)
write_report "\x20\0\xb\0\0\0\0\0"

# e
write_report "\0\0\x8\0\0\0\0\0"

# ll
write_report "\0\0\xf\0\0\0\0\0"
write_report "\0\0\xf\0\0\0\0\0"

# o
write_report "\0\0\x12\0\0\0\0\0"

# SPACE
write_report "\0\0\x2c\0\0\0\0\0"

# W (press shift and W)
write_report "\x20\0\x1a\0\0\0\0\0"

# o
write_report "\0\0\x12\0\0\0\0\0"

# r
write_report "\0\0\x15\0\0\0\0\0"

# l
write_report "\0\0\xf\0\0\0\0\0"

# d
write_report "\0\0\x7\0\0\0\0\0"

# ! (press shift and 1)
write_report "\x20\0\x1e\0\0\0\0\0"

# Release al keys
write_report "\0\0\0\0\0\0\0\0"
