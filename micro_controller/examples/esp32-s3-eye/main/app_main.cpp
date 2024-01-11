#include "driver/gpio.h"

#include "app_button.hpp"
#include "app_camera.hpp"
#include "app_lcd.hpp"
#include "app_led.hpp"
#include "app_motion.hpp"
#include "app_speech.hpp"
#include "app_face.hpp"

extern "C" void app_main()
{
    QueueHandle_t xQueueFrame_0 = xQueueCreate(2, sizeof(camera_fb_t *));
    QueueHandle_t xQueueFrame_1 = xQueueCreate(2, sizeof(camera_fb_t *));
    QueueHandle_t xQueueFrame_2 = xQueueCreate(2, sizeof(camera_fb_t *));

    AppButton *key = new AppButton();
    AppSpeech *speech = new AppSpeech();
    AppCamera *camera = new AppCamera(PIXFORMAT_RGB565, FRAMESIZE_240X240, 2, xQueueFrame_0);
    AppFace *face = new AppFace(key, speech, xQueueFrame_0, xQueueFrame_1);
    AppMotion *motion = new AppMotion(key, speech, xQueueFrame_1, xQueueFrame_2);
    AppLCD *lcd = new AppLCD(key, speech, xQueueFrame_2);
    AppLED *led = new AppLED(GPIO_NUM_3, key, speech);

    key->attach(face);
    key->attach(motion);
    key->attach(led);
    key->attach(lcd);

    speech->attach(face);
    speech->attach(motion);
    speech->attach(led);
    speech->attach(lcd);

    lcd->run();
    motion->run();
    face->run();
    camera->run();
    speech->run();
    key->run();
}
