//----------------------------------------------------------------------------
// OS-Railway - Remote Control
// Copyright (C) 2023 Peter Siegmund (https://mars3142.dev)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//----------------------------------------------------------------------------
#include "esp_now_service.h"

#include <esp32-hal-log.h>
#include <WiFi.h>

namespace ESPNow
{
    enum MessageType
    {
        PAIRING,
        META,
        FEATURES,
        COMMAND,
    };
    MessageType messageType;

    typedef struct struct_pairing
    {
        uint8_t msgType;
        uint8_t id;
        uint8_t macAddr[6];
        uint8_t channel;
    } struct_pairing;

    typedef struct struct_meta
    {
        uint8_t msgType;
        uint8_t id;
        /// data?
    } struct_meta;

    typedef struct struct_features
    {
        uint8_t msgType;
        uint8_t id;
        /// data?
    } struct_features;

    typedef struct struct_command
    {
        uint8_t msgType;
        uint8_t id;
        /// data?
    } struct_command;

    void init()
    {
        WiFi.mode(WIFI_STA);

        if (esp_now_init() != ESP_OK)
        {
            Serial.println("Error initializing ESP-NOW");
            ESP.restart();
        }
        esp_now_register_send_cb(onDataSent);
        esp_now_register_recv_cb(onDataRecv);
    }

    void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
    {
        char macStr[18];
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
                 mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        ESP_LOGD("espnow", "Last Packet Sent to: %s", macStr);
        ESP_LOGD("espnow", "Last Packet Send Status: %s", status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    }

    void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
    {
        char macStr[18];
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
                 mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        ESP_LOGD("espnow", "Last Packet Recv from: %s", macStr);
        ESP_LOGD("espnow", "Last Packet Recv Data: %s", *data);
    }
}
