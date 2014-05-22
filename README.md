## My Custum CrazyFlie Firmware

This is where I play with the crazyflie firmware. The latest version of this should be used in conjunction with the latest version of my [crazyflieROS](https://github.com/omwdunkley/crazyflieROS) client application.

For now the changes are minimal, most of the important ones have been merged into the bitCraze repo already.

Thanks to Phil Hoch for providing the base code for the idle task measurement.

Idealy the changes here do not break compatibility with the default client application by BitCraze.

Below is the original readme for reference

----

This project contains the source code for the Crazyflie firmware. More information can be found on the 
[Bitcraze wiki](http://wiki.bitcraze.se/projects:crazyflie:index)

```
Folder description:
./              | Root, contains the Makefile
 + init         | Contains the main.c
 + config       | Configuration files
 + drivers      | Hardware driver layer
 |  + src       | Drivers source code
 |  + interface | Drivers header files. Interface to the HAL layer
 + hal          | Hardware abstaction layer
 |  + src       | HAL source code
 |  + interface | HAL header files. Interface with the other parts of the program
 + modules      | Firmware operating code and headers
 |  + src       | Firmware tasks source code and main.c
 |  + interface | Operating headers. Configure the firmware environement
 + utils        | Utils code. Implement utility block like the console.
 |  + src       | Utils source code
 |  + interface | Utils header files. Interface with the other parts of the program
 + scripts      | Misc. scripts for LD, OpenOCD, make, version control, ...
 |              | *** The two following folders contains the unmodified files ***
 + lib          | Libraries
 |  + FreeRTOS  | Source FreeRTOS folder. Cleaned up from the useless files
 |  + STM32F... | Library folder of the St STM32 peripheral lib
 |  + CMSIS     | Core abstraction layer

Make targets:

all        : Shortcut for build
compile    : Compile cflie.hex. WARNING: Do NOT update version.c
build      : Update version.c and compile cflie.elf/hex
clean_o    : Clean only the Objects files, keep the executables (ie .elf, .hex)
clean      : Clean every compiled files
mrproper   : Clean every compiled files and the classical editors backup files

cload      : If the crazyflie-clients-python is placed on the same directory level and the Crazyradio is inserted
             it will try to flash the firmware using the wireless bootloader.
flash      : Flash cflie.elf using OpenOCD
halt       : Halt the target using OpenOCD
reset      : Reset the target using OpenOCD
openocd    : Launch OpenOCD
```
