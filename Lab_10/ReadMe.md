## Lab 10

Go to your LED_controller code (Lab 9)
sudo apt-get
install doxygen
mkdir doc
cd doc
doxygen -g
gedit doxyfile &

Then in doxyfile change following fields:
INPUT = ../src ../include
EXTRACT_ALL = YES
GENERATE_LATEX = NO
PROJECT_NAME = LEDController
Then run:
doxygen

Then open /src/main.cpp code add comments and compile it again
