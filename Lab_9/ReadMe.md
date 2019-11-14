## Lab 9
First build the circuit

# Part I
Go to led_and_pot_serial/led_and_pot_serial.ino. and modify it in a way that we can
read pot_value in 2 bytes.
Finally upload the code and run Teensy_Control executable

# Part II
You have to recreate Teensy_Control executable by using template in LED_Controller.
First add the UI element in glade file in /src/teensy_control.glade
(make sure that UI elements IDs are added in /include/global.h and /src/main.cpp.)
Also make sure to add signals for buttons and sliders. 
(for slider choose gtk_range->value_changed).
