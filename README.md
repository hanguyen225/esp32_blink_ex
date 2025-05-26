This example was taken from PlatformIO, modified for education purpose only 
we are group 5 of class 157326
1. Blinking video link: https://drive.google.com/file/d/1eX0xyw9mcOsW2jNArJ9LdJR_aJpEOMbG/view?usp=drive_link
  Initial ESP32 in the video was pre-wiped ie no code is in the flash memory
  Any modified code is in ./src folder, other files are only external modules PlatformIO added in order to compile into final .bin file to flash into the ESP32

  
3. Sử dụng các chế độ GPIO khác nhau để nhấp nháy LED. Kết quả: vẽ mạch phần cứng liên quan, viết ra đoạn code liên quan, đo đạc nhận xét bằng thực hành hoặc lý thuyết.

The initial ./src/Blink.cpp is original from PlatformIO and uses software vTaskDelay() which is software-based delay of FreeRTOS (Real-Time-Operating-System) which in this case allow CPU to use its cycle for other tasks as opposed to more simpler software-based delay like delay() commonly used in arduino where CPU will instead run for a set amount of cycles corresponding to its clock speed to get the final result of time needed (analogy: FreeRTOS is you wait while doing other work if there are, but in arduino you wait by wait, you cannot do anything else during you wait)

We tested the code and it have been working properly, as attached video at 1. did, visually there is no difference, but down at the OS, if we were to implement other function along with blinking there would be difference, the arduino's delay() would not allow the other function to run at all, while FreeRTOS vTaskDelay() during so will allocate its queue to other task, allowing it to run, and hardware based interrupt rely on clock cycle to time its own delay, but does not use other resources allowing the OS to run other tasks more efficiently, but implementing this is inflexible than vTaskDelay() as it rely on clock cycle and could only be coded to delay a set amount of time, if we were try to implement a blinking sequence with this method would be impractical as we have to code every interruptions and delays.

3. Ongoing











PlatformIO's README.md starts here

How to build PlatformIO based project
=====================================

1. [Install PlatformIO Core](https://docs.platformio.org/page/core.html)
2. Download [development platform with examples](https://github.com/platformio/platform-espressif32/archive/develop.zip)
3. Extract ZIP archive
4. Run these commands:

```shell
# Change directory to example
$ cd platform-espressif32/examples/espidf-arduino-blink

# Build project
$ pio run

# Upload firmware
$ pio run --target upload

# Build specific environment
$ pio run -e esp32dev

# Upload firmware for the specific environment
$ pio run -e esp32dev --target upload

# Clean build files
$ pio run --target clean
```
