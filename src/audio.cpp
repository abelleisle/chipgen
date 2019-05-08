/*
 * Copyright (C) 2019  Belle-Isle, Andrew <drumsetmonkey@gmail.com>
 * Author: Belle-Isle, Andrew <drumsetmonkey@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <audio.hpp>

#include <iostream>
#include <cstddef>
#include <cstring>

namespace ChipGen 
{
    Device::Device()
    {}

    Device::~Device()
    {
        alcCloseDevice(device);
    }

    int Device::init()
    {
        // Open a new device
        device = alcOpenDevice(NULL);
        if (!device) {
            // SOMETHING HERE PLEASE
            std::cerr << "Could not initalize blank device" << std::endl;
            return 0;
        }

        // Test possible extensions
        ALboolean enumeration = alcIsExtensionPresent(NULL, 
                                                     "ALC_ENUMERATION_EXT");
        if (enumeration == AL_FALSE) {
            // handle error
            std::cerr << "Enumeration not supported" << std::endl;
            return 0;
        }

        list_devices((alcGetString(NULL, ALC_DEVICE_SPECIFIER)));

        return 1;
    }

    void Device::list_devices(const ALCchar* devices)
    {
        const ALCchar *device_item = devices, *next = devices + 1;
        size_t len = 0;

        std::cout << "Devices list:\n";
        std::cout << "-------------\n";
        while (device_item && *device_item != '\0' && next && *next != '\0') {
            std::cout << device_item << "\n";
            len = strlen(device_item);
            device_item += (len + 1);
            next += (len + 2);
        }
        std::cout << "-------------\n";
    }
}
