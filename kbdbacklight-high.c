//
// kbdbacklight-high - A simple command-line program to set the brightness
//                     of the keyboard backlight to 100%
//
// Heavily based on the work of Amit Singh:
// http://www.osxbook.com/book/bonus/chapter10/light/
//
// (c)2008 Sean M. Graham (http://www.sean-graham.com/)
//         Amit Singh (http://www.osxbook.com/)
//

#include <mach/mach.h> 
#include <IOKit/IOKitLib.h> 
#include <CoreFoundation/CoreFoundation.h> 
#include "lmucommon.h" 

static double updateInterval = 0.1; 
static io_connect_t dataPort = 0; 

int 
main(void) 
{  
    kern_return_t kr;  
    io_service_t serviceObject;  

    // Look up a registered IOService object whose class is AppleLMUController  
    serviceObject = IOServiceGetMatchingService(kIOMasterPortDefault,  
                        IOServiceMatching("AppleLMUController"));  

    if (!serviceObject) {  
        fprintf(stderr, "failed to find ambient light sensor\n");  
        exit(1);  
    }  

    // Create a connection to the IOService object  
    kr = IOServiceOpen(serviceObject, mach_task_self(), 0, &dataPort);  
    IOObjectRelease(serviceObject);  

    if (kr != KERN_SUCCESS) {  
        mach_error("IOServiceOpen:", kr);  
        exit(kr);  
    }  

    IOItemCount scalarInputCount = 2;  
    IOItemCount scalarOutputCount = 1; 
    SInt32 in_unknown = 0, in_brightness, out_brightness; 

    in_brightness = 0xfff; // some particular value 

    kr = IOConnectMethodScalarIScalarO(dataPort, kSetLEDBrightnessID,  
        scalarInputCount, scalarOutputCount, in_unknown, in_brightness,  
        &out_brightness);

    exit(0); 
}
