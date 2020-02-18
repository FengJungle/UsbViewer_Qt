#include "UsbInterface.h"
#include "log.h"

#include <Windows.h>
#include <SetupAPI.h>
#include <devguid.h>
#include <stdio.h>
#include <wchar.h>

#pragma comment(lib, "setupapi.lib")

static int wideCharToASCII(wchar_t* wchar_buffer, char** char_buffer)
{
	// Get the required number of bytes the transform needs
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wchar_buffer, -1, NULL, 0, NULL, FALSE);    
	*char_buffer = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wchar_buffer, -1, *char_buffer, dwNum, NULL, FALSE);
	return 0;
}

int retrieveDeviceProperty(
	int         index,
	DeviceClass deviceClass,
	char*       buffer)
{
	ENTER();

	int res = 0;
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData = { sizeof(DeviceInfoData) };
	GUID guid;

	switch (deviceClass){
	case DeviceClass_SYSTEM:
		guid = GUID_DEVCLASS_SYSTEM;
		break;
	case DeviceClass_USB:
		guid = GUID_DEVCLASS_USB;
		break;
	case DeviceClass_MOUSE:
		guid = GUID_DEVCLASS_MOUSE;
		break;
	case DeviceClass_NET:
		guid = GUID_DEVCLASS_NET;
		break;
	case DeviceClass_KEYBOARD:
		guid = GUID_DEVCLASS_KEYBOARD;
		break;
	default:
		break;
	}

	// Get device class information set handle that contains requested device information elements for a local computer
	hDevInfo = SetupDiGetClassDevs(
		&guid,          
		0,              
		0,              
		DIGCF_PRESENT   
		);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		res = GetLastError();
		return res;
	}

	// enumerute device information
	DWORD required_size = 0;

	// SetupDiEnumDeviceInfo: returns a SP_DEVINFO_DATA structure that specifies a device information element in a device information set
	if (index == INDEX_ALL)
	{
		for (int i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
		{
			DWORD DataT;
			wchar_t wcBuffer[2046] = { 0 };
			DWORD buffersize = 2046;
			DWORD req_bufsize = 0;
			char* asciiBuffer = NULL;

			// retrieves a specified Plug and Play device property
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_DEVICEDESC,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(buffer, asciiBuffer);
		}
	}
	else
	{
		SetupDiEnumDeviceInfo(hDevInfo, index, &DeviceInfoData);
		
		DWORD DataT;
		wchar_t wcBuffer[2046] = { 0 };
		DWORD buffersize = 2046;
		DWORD req_bufsize = 0;
		char* asciiBuffer = NULL;

		{
			// retrieve DESCRIPTION
			LOG_DEBUG("retrieve DESCRIPTION");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_DEVICEDESC,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Device Description:\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve HARDWAREID
			LOG_DEBUG("retrieve HARDWAREID");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_HARDWAREID,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Hardware ID:\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve COMPATIBLEIDS
			LOG_DEBUG("retrieve COMPATIBLEIDS");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_COMPATIBLEIDS,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Compatible ID:\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve SERVICE
			LOG_DEBUG("retrieve SERVICE");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_SERVICE,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Service:\t\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve CLASS
			LOG_DEBUG("retrieve CLASS");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_CLASS,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Class:\t\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve CLASSGUID
			LOG_DEBUG("retrieve CLASSGUID");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_CLASSGUID,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Class GUID:\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve DRIVER
			LOG_DEBUG("retrieve DRIVER");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_DRIVER,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Driver:\t\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve MFG
			LOG_DEBUG("retrieve MFG");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_MFG,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "MFG:\t\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve LOCATION_INFORMATION
			LOG_DEBUG("retrieve LOCATION_INFORMATION");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_LOCATION_INFORMATION,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Location Information:\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve DEVICE_POWER_DATA
			LOG_DEBUG("retrieve DEVICE_POWER_DATA");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_DEVICE_POWER_DATA,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Device Power Data:\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve FRIENDLYNAME
			LOG_DEBUG("retrieve FRIENDLYNAME");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_FRIENDLYNAME,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Friendly name:\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}

		{
			// retrieve LOCATION_PATHS
			LOG_DEBUG("retrieve LOCATION_PATHS");
			if (!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&DeviceInfoData,
				SPDRP_LOCATION_PATHS,
				&DataT,
				(LPBYTE)wcBuffer,
				buffersize,
				&req_bufsize
				))
			{
				res = GetLastError();
				//continue;
			}

			char prefixBuffer[256] = "Location path:\t";
			wideCharToASCII(wcBuffer, &asciiBuffer);
			strcat(asciiBuffer, "\n");
			strcat(prefixBuffer, asciiBuffer);
			strcat(buffer, prefixBuffer);
		}
	}

	SetupDiDestroyDeviceInfoList(&hDevInfo);

	EXIT();
	return res;
}

int getDeviceProperty(
	DeviceClass deviceClass,
	Property    deviceProperty,
	int         index,
	char*       buffer)
{
	ENTER();

	int res = 0;

	if (deviceClass == DeviceClass_NONE || deviceProperty == Property_NONE){
		res = -1;
		goto exit;
	}

	if (nullptr == buffer){
		res = -2;
		goto exit;
	}

	res = retrieveDeviceProperty(index, deviceClass, buffer);

exit:
	EXIT();
	return res;
}