# Esp32 Micro Controller setup
In the context of our Software Management course, the exploration of the ESP-IDF framework for face detection and counting involved several crucial steps. The initial setup started with the setup of necessary frameworks, including esp-idf, esp-who, and Espressif. The first step was to run the provided examples in esp-who, setting the foundation for further customization.\
In the provided code in the folder micro_controller lives the main code, everything else namely esp-idf, and espressif should be downloaded for it to run correctly. The folder structure should look like this:\
repository\
 └	micro_controller\
 └	esp-idf\
 └	Espressif

The main file to run for the face detection and counting functionality lives in the file `micro_controller/examples/human_face_detection/lcd/main/app_main.cpp`. This main code serves as the entry point for the application and contains the logic for counting faces detected by the device.

## Wi-Fi Configuration
To ensure the proper functioning of the controller, initial setup involved configuring the Wi-Fi settings. This configuration could be achieved through the `menuconfig` tool or by directly adding it into the code. In our case, both methods were employed for flexibility.\
For configuration with direct code, adjustments need to be made in the file `micro_controller /components/modules/web/app_wifi.c`. Within this file, the parameters `EXAMPLE_ESP_WIFI_SSID` and `EXAMPLE_ESP_WIFI_PASS` were modified to reflect the desired Wi-Fi network name and password.  With these configurations in place, the device is ready for operation.

## Counting Logic Modifications
The counting logic, fundamental to the face detection system, was primarily located in `esp-who/components/modules/ai/human_face_detection.cpp`. To tailor the counting functionality to our specific requirements, customizations and adjustments were implemented in the original code.\
One notable modification involved the introduction of the client as an object passed onto from the app_main.cpp file on line 143. The counting logic initiates from line 51 in the `human_face_detection.cpp` file. In essence, when a face is detected, the system triggers a count increment, sending a signal to increment +1 or decrement by sending the string "esp32-1-0" message to the designated topic `entrance_counter/data` to AWS. Esp32 is the device id, 1 is entered number and 0 is exited number.\
To summarize, the comprehensive documentation and customization of the ESP-IDF framework for face detection and counting involved configuring Wi-Fi settings, adapting the main code in `app_main.cpp`, and refining the counting logic in `human_face_detection.cpp`.
