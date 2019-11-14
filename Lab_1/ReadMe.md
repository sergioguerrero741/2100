## Lab 1
Go to raspberry.org to download OS (downloads/noobs) and copy all the zip files to SD Card.
Then connect HDMI and USB cables for mouse & keyboard.
Finally connect power button with will turn on the red LED.

# SET LOCALE AND TIME ZONE (Internationalization options)
raspi-config

Locale: en_US.UTF-8;
Time Zone: US Central (Space bar for select/deselect)


# UPDATE SYSTEM TIME WITH NTP
date

sudo apt-get update

sudo apt-get install ntp

sudo apt-get install ntpdate

sudo service ntp stop

sudo ntpdate pool.ntp.gov

sudo service ntp start

date

# CLONE GITHUB REPOSITORY
sudo apt-get install git cmake gedit

git clone https://github.com/ZakZadeh/cse2100.git

# BUILD HELLO WORLD EXAMPLE
cd hello_world

cmake .

make

./hello_world
