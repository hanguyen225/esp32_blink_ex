This example was taken from PlatformIO, modified for education purpose only 
we are group 5 of class 157326
1. Blinking video link: https://drive.google.com/file/d/1eX0xyw9mcOsW2jNArJ9LdJR_aJpEOMbG/view?usp=drive_link
   
    Initial ESP32 in the video was pre-wiped ie no code is in the flash memory
    Any modified code is in ./src folder, other files are only external modules PlatformIO added in order to compile into final .bin file to flash into the ESP32

  
2. Sử dụng các chế độ GPIO khác nhau để nhấp nháy LED. Kết quả: vẽ mạch phần cứng liên quan, viết ra đoạn code liên quan, đo đạc nhận xét bằng thực hành hoặc lý thuyết.

    The initial ./src/Blink.cpp is original from PlatformIO and uses software vTaskDelay() which is software-based delay of FreeRTOS (Real-Time-Operating-System) which in this case allow CPU to use its cycle for other tasks as opposed to more simpler software-based delay like delay() commonly used in arduino where CPU will instead run for a set amount of cycles corresponding to its clock speed to get the final result of time needed (analogy: FreeRTOS is you wait while doing other work if there are, but in arduino you wait by wait, you cannot do anything else during you wait)

   mạch phần cứng: 
   ![Blinking LED](assets/2025-05-26_20-04-42.gif)


    We tested the code and it have been working properly, as attached video at 1. did, visually there is no difference, but down at the OS, if we were to implement other function along with blinking there would be difference, the arduino's delay() would not allow the other function to run at all, while FreeRTOS vTaskDelay() during so will allocate its queue to other task, allowing it to run, and hardware based interrupt rely on clock cycle to time its own delay, but does not use other resources allowing the OS to run other tasks more efficiently, but implementing this is inflexible than vTaskDelay() as it rely on clock cycle and could only be coded to delay a set amount of time, if we were try to implement a blinking sequence with this method would be impractical as we have to code every interruptions and delays.

4. Ongoing

      First we should define how should led flash in 1hz feq, means it complete flashing on and off within 1hz -> 0.5s on and 0.5s off

      Lưu đồ thuật toán:
      ![Diagram](./assets/Untitled_Diagram.svg)

      Code sử dụng nằm ở ./src/hardware_based_interrupt_delay_blink.cpp, trích đoạn:

        timer = timerBegin(0, 80, true);                // 80MHz / 80 = 1MHz (chia clock ABP cho 8 ta được 1MHz clock -> 1micro giây)
        timerAttachInterrupt(timer, &onTimer, true);    // Initialize interrupt
        timerAlarmWrite(timer, 500000, true);           // 500000micro giây = nửa chu kỳ (0.5s) -> toggle tắt mở mỗi 0.5s
        timerAlarmEnable(timer);                        // Interrupt

      
      Một số thông tin của ESP32 được sử dụng để code timer:
         ESP32 ABP clock = 80MHz

      

Hướng dẫn chạy code trên ESP32
   Tải PlatformIO trên VScode, sau khi xong initializing thì tải repository này về và import
   Khi import xong cần build bằng cách sử dụng tổ hợp ctrl+shift+p và chọn PlatformIO và chọn phần tương ứng
   
   ![Diagram](https://github.com/hanguyen225/esp32_blink_ex/blob/main/assets/Screenshot%202025-05-26%20125002.png?raw=true)

   
      Thứ tự các bước build->chọn COM->flash

  
