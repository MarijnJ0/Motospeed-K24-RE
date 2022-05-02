/******************************************************************************************\
*                                                                                          *
*   Detect Motospeed Controllers                                                             *
*                                                                                          *
*       Tests the USB address to see if a Motospeed controller exists there.               *
*                                                                                          *
\******************************************************************************************/

#include "Detector.h"
#include "MotospeedController.h"
#include "RGBController.h"

#include "RGBController_MotospeedK24.h"
#include <hidapi/hidapi.h>
#include <unordered_set>


#define Motospeed_VID            0x0416

#define Motospeed_K24_PID        0xC345

void DetectMotospeedControllers(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        MotospeedController*     controller        = new MotospeedController(dev, info->path);
        RGBController_MotospeedK24* rgb_controller = new RGBController_MotospeedK24(controller);
        rgb_controller->name = name;
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}   /* DetectDuckyKeyboardControllers() */

REGISTER_HID_DETECTOR_I("Motospeed K24",           DetectMotospeedControllers, Motospeed_VID, Motospeed_K24_PID,     1);
