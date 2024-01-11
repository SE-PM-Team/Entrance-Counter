#include "who_camera.h"
#include "who_human_face_detection.hpp"
#include "who_lcd.h"
#include "app_wifi.h"
#include "app_httpd.hpp"
#include "app_mdns.h"


#include "esp_log.h"
#include "mqtt_client.h"


#include <iostream>
#include <ctime>
#include <string>
#include <chrono>

static const char *TAG = "MQTT_EXAMPLE";

static QueueHandle_t xQueueAIFrame = NULL;
static QueueHandle_t xQueueLCDFrame = NULL;

#define AWS_IOT_ENDPOINT "a3k42p0h1rrxj7-ats.iot.eu-central-1.amazonaws.com"
using namespace std; 

static const char *aws_root_ca = "-----BEGIN CERTIFICATE-----\nMIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\nADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\nb24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\nMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\nb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\nca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\nIFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\nVOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\njgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\nAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\nA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\nU5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\nN+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\no/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\nrqXRfboQnoZsG4q5WTP468SQvvG5\n-----END CERTIFICATE-----";
static const char *aws_cert_pem = "-----BEGIN CERTIFICATE-----\nMIIDWTCCAkGgAwIBAgIUZawnlLEDLiQucGuZoomv34a92yIwDQYJKoZIhvcNAQEL\nBQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\nSW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIzMTEyOTE4NDEw\nM1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\nZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKTBvh0+StlovTlw06R/\neM5fOg7QLlK3C/fNz8cjf8lD7iZdD06M/HZDvUXoQHT8m9feVDYkfPy06ez+48aX\nmXO1sa3Wr1zhzgQqwG99ql4U6MCBHb2iSglTTly2ogVe1V7ZgrmQAcxVwzNvXcmp\nmip5yfgkni27fXhs5NosT9UtlE3mJzNRMgo+r2CONApV7hp6jA1q/VtH1MuEfHI3\npsBkmj2WnPVl4KlQbrbt4Sg1MrDTtroa61M4nLGTsfk5cm9FFM25SZqphW3/vL9I\nPSiti0YwC1ysLiqU5mpfHeLKTLTzKG/1c5uWOv5D14WU/k4O+xK7WqQjIYB3hDn4\nJzsCAwEAAaNgMF4wHwYDVR0jBBgwFoAUF60aZHr3BM7qupWT1//K6DSzFaAwHQYD\nVR0OBBYEFHTI0a7tFVw544Pt5Rnlyg0uo5cQMAwGA1UdEwEB/wQCMAAwDgYDVR0P\nAQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBbE1LHYf7fwvMmYsOEtcZIO3yC\nPXcv7pKjrDaHN6BzNKEq8vrh03UCzUFRYiAcMrCvV5pAhxCZxZX8SFkiV60GBwr+\n4LsHR2pGAgBa4r/BJZuzekLiFnvQ2YmOIXPr+BCnXU03DcVwsbwaJOerrjJdHBDC\nELjW+MEHLtSF1wOMkg1+LcnscXQGX6QaErhWqa8i3b0mKVLXOp2TUsQTEaQsasFi\nJ/c2tV5S9Xc7BHJagvS3BNUZRAPPTIkZLcUwgLd7W/7FFj1r/vmBhT3IS1lEK1uQ\n9eRpMnipVt7CLxjMTNFPORCThn6PIuC+I8FTfuWuiAe1BxmSVSPzjNZhpceQ\n-----END CERTIFICATE-----";
static const char *aws_private_key = "-----BEGIN RSA PRIVATE KEY-----\nMIIEowIBAAKCAQEApMG+HT5K2Wi9OXDTpH94zl86DtAuUrcL983PxyN/yUPuJl0P\nToz8dkO9RehAdPyb195UNiR8/LTp7P7jxpeZc7WxrdavXOHOBCrAb32qXhTowIEd\nvaJKCVNOXLaiBV7VXtmCuZABzFXDM29dyamaKnnJ+CSeLbt9eGzk2ixP1S2UTeYn\nM1EyCj6vYI40ClXuGnqMDWr9W0fUy4R8cjemwGSaPZac9WXgqVButu3hKDUysNO2\nuhrrUzicsZOx+Tlyb0UUzblJmqmFbf+8v0g9KK2LRjALXKwuKpTmal8d4spMtPMo\nb/Vzm5Y6/kPXhZT+Tg77ErtapCMhgHeEOfgnOwIDAQABAoIBAALbvaGiQAgvkgDa\nHUHgWEc0TbyODg+vT0zYTD+HNSNXw1z1Blv1hDfFCxaYZe3hqA6Bs/JQhb6YoOpU\nrbz3SllAkLmUXOx+mmVmHHqSso75S+RzGQH+O8yXnmdrX7o6H/eKTINNpUpXPpC4\n4Oarw5nzDPb6I6hldVLOiNXkKOpo3eUVZse2hcEYA3DwKyDTZm7gQTK5xM4eihYz\nq42Y9pRnEKq3VXQqGzhMJTtorijkY4WcWSd+Ee94aPJWJ4tORZVpaQsS5PkaIUaR\nOAobO0V5bmS9d5illM4Gleq+vCXkvZGQhWtIk51r0v21WLa2F1HMdF6VjbgmzIqs\nML+leAECgYEA1bcGXc1LQBzS953nq8QRYxmxyAGpTPxirPwLDiFk4V0TEh2eNcIl\nKBug+rrqb6fSLwEBvTkemAPnY8v8ac/OXEeDuvjel+1K9VY+pbJ+hTLX0Zj+2J8x\nKvTLA1/YYg1R2kNDptO7/nJvGh076KncywFFj8GCqBpQVFFA013GLAECgYEAxVrq\nn/HGklLK1mRmH5RG9h05U3kwWFxXQxzBwrAsHgQoicAN+sn61i7QNNEHXjwKqSzP\nU2BJrpnD9PUaks8sSyNA6SU/jW2grE4hUb3sTqeMWtkg6VB3TvNHwsUIOKcdJ9l2\nGIHh5UmziBrRzRJ502jBueMjdvBgfgyZqerIAzsCgYEAvkZmz6sRHXLMThPziNVX\nGaFtzIHWJynp/NOmUB1hQNjqOs3N51UEWfJHYBR8145WLu05jCxH1dZb9FlQUTDo\nLParDRO4sxFdFJOF0WbbCGJdDkqmU11gnDs4aLez4pCzWJ1cpTKMhR2DV3/BsANU\nBhYKxdPnLR3IeVmiWs15vAECgYB4AvJ8cv0qy9f3CbSkbXm9fkX3AdIpWXXjJOCa\n8KDTW/n+0mBt6ldz2aHZDGeroV1mRQ6KiBomZ/Emy8nuDrfDtVtqq7D64vh670QJ\nvjGuHusV78W4u6rhwsUXptN6B/2N1wqempTw5qGbGZwNVbfpnGF6FariUAiNfkIP\ndutMMwKBgCISxFbBi6Aiooyt5B341VTnIi22hzTIx7RbuetFgEJOmIpO37oCnN5S\nsuf6Kq0ynir1XsHw0fyndpwZ9FS5KLtekuvwMvtYb/Z5vRHQFoh9xFa1vBsjsMaF\n5kdBsA2GvGd7YxeGzJE+HtXlc3EOCo9XtpuvCxQVUNRvmsYqUzxH\n-----END RSA PRIVATE KEY-----";


static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_subscribe(client, "/test/testing", 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_subscribe(client, "/test/testing", 1);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_unsubscribe(client, "/test/testing");
        ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        msg_id = esp_mqtt_client_publish(client, "/test/testing", "hello from esp_32", 0, 0, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_CONNECTION_REFUSED)
        {
            ESP_LOGI(TAG, "Connection refused error: 0x%x", event->error_handle->connect_return_code);
        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
    return ESP_OK;
}

static esp_mqtt_client_handle_t mqtt_app_start(void)
{
    const esp_mqtt_client_config_t mqtt_cfg = {
        .event_handle = mqtt_event_handler,
        .host = AWS_IOT_ENDPOINT,
        .cert_pem = aws_root_ca,
        .client_cert_pem = aws_cert_pem,
        .client_key_pem = aws_private_key,
        .transport = MQTT_TRANSPORT_OVER_SSL,
    };

    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

    return client;
}




extern "C" void app_main()
{

    app_wifi_main();

    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

    vTaskDelay(10000 / portTICK_PERIOD_MS);

    esp_mqtt_client_handle_t client = mqtt_app_start();
    while (true)
    {           
        // Get the current date and time
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        // Convert the time to a string
        std::string time_str = std::ctime(&now_c);
        esp_mqtt_client_publish(client, "$aws/things/esp_32/shadow", "Device started", 0,1,0);
        esp_mqtt_client_publish(client, "$aws/things/esp_32/shadow/update", time_str.c_str(), 0,1,0);
        break;
    }
    

    xQueueAIFrame = xQueueCreate(2, sizeof(camera_fb_t *));
    xQueueLCDFrame = xQueueCreate(2, sizeof(camera_fb_t *));

    register_camera(PIXFORMAT_RGB565, FRAMESIZE_240X240, 2, xQueueAIFrame);
    app_mdns_main();

    register_human_face_detection(xQueueAIFrame, NULL, NULL, xQueueLCDFrame, client, false);
    register_lcd(xQueueLCDFrame, NULL, true);


} 