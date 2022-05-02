/*-----------------------------------------*\
|  RGBController_MotospeedK24.h          |
|                                           |
|  Generic RGB Interface for Alienware      |
|  AW510K keyboard                          |
|                                           |
|  Mohamad Sallal - msallal      05/22/2021 |
\*-----------------------------------------*/

#pragma once

#include "RGBController.h"
#include "MotospeedController.h"

enum
{
    MOTOSPEED_K24_MODE_DIRECT                          = 0x36,
    MOTOSPEED_K24_MODE_STATIC                          = 0x00, /* "Normally on"            */
    MOTOSPEED_K24_MODE_BREATHING                       = 0x01, /* "Breathing"              */
    MOTOSPEED_K24_MODE_COLOR_WAVE                      = 0x02, /* "Wave"                   */
    MOTOSPEED_K24_MODE_NEON                            = 0x03, /* "The trial of light"     */
    MOTOSPEED_K24_MODE_RADAR                           = 0x04, /* "Circaling color"        */
    MOTOSPEED_K24_MODE_REACTIVE                        = 0x06, /* "Pass without trace"     */
    MOTOSPEED_K24_MODE_REACTIVE_AURORA                 = 0x07, /* "Reactive line horizontal"   */
    MOTOSPEED_K24_MODE_REACTIVE_RIPPLE                 = 0x08, /* "Reactive pulse"         */
    MOTOSPEED_K24_MODE_TWINKLE                         = 0x09, /* "Twinkle"                */
    MOTOSPEED_K24_MODE_REACTIVE_CROSS                  = 0x0b, /* "Cross"                  */
    MOTOSPEED_K24_MODE_REACTIVE_FIREWORKS              = 0x0B, /* "Flowers blooming"       */
    MOTOSPEED_K24_MODE_RIPPLE                          = 0x0e, /* "Color crossings"        */
    MOTOSPEED_K24_MODE_SNAKE                           = 0x0f, /* "Snake"                  */
    MOTOSPEED_K24_MODE_CUSTOM                          = 0x36  /* "Coastal"                */
};


class RGBController_MotospeedK24 : public RGBController
{
public:
    RGBController_MotospeedK24(MotospeedController* controller_ptr);
    ~RGBController_MotospeedK24();

    void        SetupZones();

    void        ResizeZone(int zone, int new_size);
    
    void        DeviceUpdateLEDs();

    void        UpdateZoneLEDs(int zone);

    void        UpdateSingleLED(int led);

    void        SetCustomMode();

    void        DeviceUpdateMode();

private:
    MotospeedController*  controller;

    std::vector<RGBColor>   double_buffer;
    bool                    updateDevice;
};

