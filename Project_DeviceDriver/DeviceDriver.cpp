#include "DeviceDriver.h"

#include <exception>
#include <windows.h>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int FirstReadval = (int)(m_hardware->read(address));
    Sleep(200); //200ms
    for(int trycnt = 2; trycnt <= 5; trycnt++)
    {
        int curReadval = (int)(m_hardware->read(address));
        Sleep(200); //200ms
        if (FirstReadval != curReadval)
            throw std::exception("Exception!!");
    }
    return FirstReadval;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}