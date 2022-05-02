/*-----------------------------------------*\
|  MotospeedController.h                  |
|                                           |
|  Definitions and types for Das Keyboard   |
|  RGB keyboard lighting controller         |
|                                           |
|  Frank Niessen (denk_mal) 12/16/2020      |
\*-----------------------------------------*/

#include "RGBController.h"

#include <string>
#include <hidapi/hidapi.h>

#pragma once

class MotospeedController
{
public:
    MotospeedController(hid_device *dev_handle, const char *path);

    ~MotospeedController();

    std::string GetDeviceLocation();

    std::string GetSerialString();

    void SendColors(unsigned char key_id, unsigned char mode,
                    unsigned char red, unsigned char green, unsigned char blue);

    void SendApply();

private:
    hid_device  *dev;
    std::string location;
    std::string version;
    bool        useTraditionalSendData;

    void SendInitialize();

    void SendData(const unsigned char *data, unsigned int length);

    void SendDataTraditional(const unsigned char *data, unsigned int length);

    void SendDataModern(const unsigned char *data, unsigned int length);

    int ReceiveData(unsigned char *data, unsigned int max_length);
};
