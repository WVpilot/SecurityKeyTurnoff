// SecurityKeyTurnoff.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.
// Made by Jack Redden, credit to Microsoft Documentation
// The purpose of this program is to disable or logoff the adminastrator 
// user after a USB security key has been removed

#include <iostream>
#include <Windows.h>
#include <setupapi.h>

int main()
{
    //Initialize variables
    HDEVINFO devInfoSet;
    SP_DEVINFO_DATA devInfoData;
    bool keyIn;
    int devIndex;

    //Check for key and make device list
    devInfoSet = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    ZeroMemory(&devInfoData, sizeof(SP_DEVINFO_DATA));
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    //Start of functionality
    //Start checking automatically if key is still inserted
    if (keyIn)
    {
        while (keyIn)
        {
            devIndex = 0;

            while (SetupDiEnumDeviceInfo(
                devInfoSet,
                devIndex,
                &devInfoData))/*THAT STUPID POINTER*/
            {
                devIndex++;

            }
        }

        //Release the device list
        if (devInfoSet)
        {
            SetupDiDestroyDeviceInfoList(devInfoSet);
        }

        //Return the value of ExitWindows after informing to logoff, with security reason (possibly going to change reason or revert back to 0xffffffff)
        return ExitWindowsEx(EWX_LOGOFF, SHTDN_REASON_MINOR_SECURITY);
    }

    //Log Windows of automatically if key is not detected automatically
    else
    {
        //Release the device list
        if (devInfoSet)
        {
            SetupDiDestroyDeviceInfoList(devInfoSet);
        }
        
        //Return the value of ExitWindows after informing to logoff, with security reason (possibly going to change reason or revert back to 0xffffffff)
        return ExitWindowsEx(EWX_LOGOFF, SHTDN_REASON_MINOR_SECURITY);
    }
}