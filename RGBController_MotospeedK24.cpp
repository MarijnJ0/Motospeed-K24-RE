/*-----------------------------------------*\
|  RGBController_MotospeedK24.cpp            |
|                                           |
|  Generic RGB Interface for Das Keyboard   |
|  RGB keyboard devices                     |
|                                           |
|  Frank Niessen (denk_mal) 12/16/2020      |
\*-----------------------------------------*/

#include "RGBControllerKeyNames.h"
#include "RGBController_MotospeedK24.h"

using namespace std::chrono_literals;

//0xFFFFFFFF indicates an unused entry in matrix
#define NA  0xFFFFFFFF

// Motospeed K24 key layout 

static unsigned int matrix_map_keys[6][4] =
    {
		{ 0,  1,  2,  3,},	
		{ 4,  5,  6,  7,},
		{ 8,  9, 10, 11,},
		{12, 13, 14, NA,},
		{15, 16, 17, 18,},
		{19, NA, 20, NA,}
    };

// Motospeed K24 underglow layout 

// static unsigned int matrix_map_underglow[10][6] =
//    {
//		{NA,  1,  2,  3,  4, NA,},
//		{23, NA, NA, NA, NA,  5,},
//		{22, NA, NA, NA, NA,  6,},
//		{21, NA, NA, NA, NA,  7,},
//		{20, NA, NA, NA, NA,  8,},
//		{19, NA, NA, NA, NA,  9,},
//		{NA, NA, NA, NA, NA, 10,},
//		{18, NA, NA, NA, NA, 11,},
//		{17, NA, NA, NA, NA, 12,},
//		{16, NA, 15, NA, 14, 13,}
//    };

static const char *zone_names[] =
    {
        "K24"
//        "Underglow"
    };

static zone_type zone_types[] =
    {
        ZONE_TYPE_MATRIX,
//        ZONE_TYPE_MATRIX,
    };

static const unsigned int zone_sizes[] =
    {
        21
//        23
    };

// Layout
static const char *led_names[] =
{   
    KEY_EN_NUMPAD_0,
    KEY_EN_NUMPAD_1,
    KEY_EN_NUMPAD_4,
    KEY_EN_NUMPAD_7,
    KEY_EN_NUMPAD_LOCK,
    KEY_EN_ESCAPE,

    KEY_EN_UNUSED,
    KEY_EN_NUMPAD_2,
    KEY_EN_NUMPAD_5,
    KEY_EN_NUMPAD_8,
    KEY_EN_NUMPAD_DIVIDE,
    KEY_EN_TAB,

    KEY_EN_NUMPAD_PERIOD,
    KEY_EN_NUMPAD_3,
    KEY_EN_NUMPAD_6,
    KEY_EN_NUMPAD_9,
    KEY_EN_NUMPAD_TIMES,
    KEY_EN_BACKSPACE,

    KEY_EN_UNUSED,
    KEY_EN_NUMPAD_ENTER,
    KEY_EN_UNUSED,
    KEY_EN_NUMPAD_PLUS,
    KEY_EN_NUMPAD_MINUS,
    KEY_EN_LEFT_FUNCTION,
};

/*
    KEY_EN_NUMPAD_0,
    KEY_EN_NUMPAD_1,
    KEY_EN_NUMPAD_4,
    KEY_EN_NUMPAD_7,
    KEY_EN_NUMPAD_LOCK,
    KEY_EN_ESCAPE,

    KEY_EN_UNUSED,
    KEY_EN_NUMPAD_2,
    KEY_EN_NUMPAD_5,
    KEY_EN_NUMPAD_8,
    KEY_EN_NUMPAD_DIVIDE,
    KEY_EN_TAB,

    KEY_EN_NUMPAD_PERIOD,
    KEY_EN_NUMPAD_3,
    KEY_EN_NUMPAD_6,
    KEY_EN_NUMPAD_9,
    KEY_EN_NUMPAD_TIMES,
    KEY_EN_BACKSPACE,

    KEY_EN_UNUSED,
    KEY_EN_NUMPAD_ENTER,
    KEY_EN_UNUSED,
    KEY_EN_NUMPAD_PLUS,
    KEY_EN_NUMPAD_MINUS,
    KEY_EN_LEFT_FUNCTION,
};


       Key Label                Index
    { KEY_EN_ESCAPE,            0       },
    { KEY_EN_TAB,               1       },
    { KEY_EN_BACKSPACE,         2       },
    { KEY_EN_FUNCTION,          3       },
    { KEY_EN_NUMPAD_LOCK,       4       },
    { KEY_EN_NUMPAD_DIVIDE,     5       },
    { KEY_EN_NUMPAD_TIMES,      6       },
    { KEY_EN_NUMPAD_MINUS,      7       },
    { KEY_EN_NUMPAD_7,          8       },
    { KEY_EN_NUMPAD_8,          9       },
    { KEY_EN_NUMPAD_9,          10      },
    { KEY_EN_NUMPAD_PLUS,       11      },
    { KEY_EN_NUMPAD_4,          12      },
    { KEY_EN_NUMPAD_5,          13      },
    { KEY_EN_NUMPAD_6,          14      },
    { KEY_EN_NUMPAD_1,          15      },
    { KEY_EN_NUMPAD_2,          16      },
    { KEY_EN_NUMPAD_3,          17      },
    { KEY_EN_NUMPAD_ENTER,      18      },
    { KEY_EN_NUMPAD_0,          19      },
    { KEY_EN_NUMPAD_PERIOD,     20      },
};

\*
        
/**------------------------------------------------------------------*\
    @name Das Keyboard
    @type USB
    @save :x:
    @direct :white_check_mark:
    @effects :white_check_mark:
    @detectors DetectDasKeyboardControllers
    @comment

    { KEY_EN_NUMPAD_0,            
    {    KEY_EN_NUMPAD_1,
    {    KEY_EN_NUMPAD_4,
    {    KEY_EN_NUMPAD_7,
        KEY_EN_NUMPAD_LOCK,
        KEY_EN_ESCAPE,

        KEY_EN_UNUSED,
        KEY_EN_NUMPAD_2,
        KEY_EN_NUMPAD_5,
        KEY_EN_NUMPAD_8,
        KEY_EN_NUMPAD_DIVIDE,
        KEY_EN_TAB,

        KEY_EN_NUMPAD_PERIOD,
        KEY_EN_NUMPAD_3,
        KEY_EN_NUMPAD_6,
        KEY_EN_NUMPAD_9,
        KEY_EN_NUMPAD_TIMES,
        KEY_EN_BACKSPACE,

        KEY_EN_UNUSED,
        KEY_EN_NUMPAD_ENTER,
        KEY_EN_UNUSED,
        KEY_EN_NUMPAD_PLUS,
        KEY_EN_NUMPAD_MINUS,
        KEY_EN_FUNCTION,    
\*-------------------------------------------------------------------*/

RGBController_MotospeedK24::RGBController_MotospeedK24(MotospeedController* controller_ptr)
{
    controller  = controller_ptr;

    for(unsigned int ii = 0; ii < zone_sizes[0]; ii++)
    {
        double_buffer.push_back(-1);
    }

    updateDevice = true;

    name        = "Motospeed K24";
    vendor      = "Motospeed";
    type        = DEVICE_TYPE_KEYBOARD;
    description = "Motospeed K24 RGB Numpad Device";
    location    = controller->GetDeviceLocation();
    serial      = controller->GetSerialString();

    modes.resize(4);
    modes[0].name       = "Direct";
    modes[0].value      = MOTOSPEED_K24_MODE_DIRECT;
    modes[0].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[0].color_mode = MODE_COLORS_PER_LED;

    modes[1].name       = "Static";
    modes[1].value      = MOTOSPEED_K24_MODE_STATIC;
    modes[1].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[1].color_mode = MODE_COLORS_PER_LED;

    modes[2].name       = "Breathing";
    modes[2].value      = MOTOSPEED_K24_MODE_BREATHING;
    modes[2].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[2].color_mode = MODE_COLORS_PER_LED;

    modes[3].name       = "Color Wave";
    modes[3].value      = MOTOSPEED_K24_MODE_COLOR_WAVE;
    modes[3].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[3].color_mode = MODE_COLORS_PER_LED;

    modes[4].name       = "Neon";
    modes[4].value      = MOTOSPEED_K24_MODE_NEON;
    modes[4].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[4].color_mode = MODE_COLORS_PER_LED;

    modes[5].name       = "Radar";
    modes[5].value      = MOTOSPEED_K24_MODE_RADAR;
    modes[5].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[5].color_mode = MODE_COLORS_PER_LED;

    modes[6].name       = "Twinkle";
    modes[6].value      = MOTOSPEED_K24_MODE_TWINKLE;
    modes[6].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[6].color_mode = MODE_COLORS_PER_LED;
    
    modes[7].name       = "Ripple";
    modes[7].value      = MOTOSPEED_K24_MODE_RIPPLE;
    modes[7].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[7].color_mode = MODE_COLORS_PER_LED;
    
    modes[8].name       = "Snake";
    modes[8].value      = MOTOSPEED_K24_MODE_SNAKE;
    modes[8].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[8].color_mode = MODE_COLORS_PER_LED;
    
    modes[9].name       = "Reactive";
    modes[9].value      = MOTOSPEED_K24_MODE_REACTIVE;
    modes[9].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[9].color_mode = MODE_COLORS_PER_LED;
        
    modes[10].name       = "Reactive Aurora";
    modes[10].value      = MOTOSPEED_K24_MODE_REACTIVE_AURORA;
    modes[10].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[10].color_mode = MODE_COLORS_PER_LED;
        
    modes[11].name       = "Reactive Ripple";
    modes[11].value      = MOTOSPEED_K24_MODE_REACTIVE_RIPPLE;
    modes[11].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[11].color_mode = MODE_COLORS_PER_LED;
        
    modes[12].name       = "Reactive Cross";
    modes[12].value      = MOTOSPEED_K24_MODE_REACTIVE_CROSS;
    modes[12].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[12].color_mode = MODE_COLORS_PER_LED;
        
    modes[13].name       = "Reactive Fireworks";
    modes[13].value      = MOTOSPEED_K24_MODE_REACTIVE_FIREWORKS;
    modes[13].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[13].color_mode = MODE_COLORS_PER_LED;
       
    modes[14].name       = "Custom";
    modes[14].value      = MOTOSPEED_K24_MODE_CUSTOM;
    modes[14].flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    modes[14].color_mode = MODE_COLORS_PER_LED;

}

RGBController_MotospeedK24::~RGBController_MotospeedK24()
{
    /*---------------------------------------------------------*\
    | Delete the matrix map                                     |
    \*---------------------------------------------------------*/
    unsigned int zone_size = zones.size();

    for(unsigned int zone_index = 0; zone_index < zone_size; zone_index++)
    {
        delete zones[zone_index].matrix_map;
    }

    delete controller;
}

void RGBController_MotospeedK24::SetupZones()
{
    /*---------------------------------------------------------*\
    | Set up zones                                              |
    \*---------------------------------------------------------*/
    unsigned int total_led_count = 0;

    for(unsigned int zone_idx = 0; zone_idx < 1; zone_idx++)
    {
        zone new_zone;
        new_zone.name               = zone_names[zone_idx];
        new_zone.type               = zone_types[zone_idx];
        new_zone.leds_min           = zone_sizes[zone_idx];
        new_zone.leds_max           = zone_sizes[zone_idx];
        new_zone.leds_count         = zone_sizes[zone_idx];
        new_zone.matrix_map         = new matrix_map_type;
        new_zone.matrix_map->height = 6;
        new_zone.matrix_map->width  = 4;
        new_zone.matrix_map->map = (unsigned int *) &matrix_map_keys;
        
        zones.push_back(new_zone);

        total_led_count += zone_sizes[zone_idx];
    }

    for(unsigned int led_idx = 0; led_idx < total_led_count; led_idx++)
    {
        led new_led;
        new_led.name                = led_names[led_idx];
        leds.push_back(new_led);
    }

    SetupColors();
}

void RGBController_MotospeedK24::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_MotospeedK24::DeviceUpdateLEDs()
{
    UpdateZoneLEDs(0);
}

void RGBController_MotospeedK24::UpdateZoneLEDs(int /*zone*/)
{
    updateDevice = false;

    for(unsigned int led_idx = 0; led_idx < leds.size(); led_idx++)
    {
        UpdateSingleLED(static_cast<int>(led_idx));
    }

    updateDevice = true;

    controller->SendApply();
}

void RGBController_MotospeedK24::UpdateSingleLED(int led)
{
    mode selected_mode = modes[active_mode];

    if(double_buffer[led] == colors[led])
    {
        return;
    }

    controller->SendColors(led, selected_mode.value,
                           RGBGetRValue(colors[led]),
                           RGBGetGValue(colors[led]),
                           RGBGetBValue(colors[led]));

    double_buffer[led] = colors[led];

    if(updateDevice)
    {
        controller->SendApply();
    }
}

void RGBController_MotospeedK24::SetCustomMode()
{
    active_mode = 0;
}

void RGBController_MotospeedK24::DeviceUpdateMode()
{
}
