## Lab 5

Go to www.pjrc.com/teensy to download audrino v 1.6.11 then go to terminal.

tar xf ~/Downloads/arduino-1.6.11-linuxarm.tar.xz -C ~/

cd arduino-1.6.11/

sudo ./install.sh

cd cse2100

cd teensy

sudo sh install_teensyduino.sh

sudo apt-get install libusb-0.1-4

Then Run Arduino from Menu and open teensy_blink code.
Then check in Tools that Teensy 3.2/3.1 is selected.
Then Compile and Upload.

# Task
Modify the provided Teensy LED blink example to flash the famous distress signal SOS in Morse code repeatedly (3 short flashes, 3 long flashes, 3 short flashes), with a 2 second delay between messages. The LED should be on for 250 milliseconds for short flashes, and 500 milliseconds for long flashes. Use a delay of 250 milliseconds between all flashes.
