#ifndef _USBINTERFACE_H_
#define _USBINTERFACE_H_

#define INDEX_ALL -1

enum DeviceClass{
	DeviceClass_NONE = -1,
	DeviceClass_MOUSE,
	DeviceClass_SYSTEM,
	DeviceClass_USB,
	DeviceClass_NET,
	DeviceClass_KEYBOARD
};

enum Property{
	Property_NONE          = -1,
	Property_DESCRIPTION   = 0x00000000,
	Property_HARDWAREID    = 0x00000001,
	Property_COMPATIBLEIDS = 0x00000002
};

/*
* Function:      getDeviceProperty
* Description:   obtain appointed device's property and save it in the buffer
* Para:          deviceClass    - specific device class
*                deviceProperty - specific device property intended to retrieve
*                index          - device index in the deviceInfoSet
*                buffer         - buffer saved the retieved device property
* Return:        success return 0, or other error code
* Author:        fengqiangguo
* Date:          2020-2-16
*/
int getDeviceProperty(
	DeviceClass deviceClass,
	Property    deviceProperty,
	int         index,
	char*       buffer);



#endif //_USBINTERFACE_H_