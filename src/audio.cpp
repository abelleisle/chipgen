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

#define TEST_ERROR(_msg)		    \
	auto error = alGetError();		\
	if (error != AL_NO_ERROR) {	    \
		std::cerr << _msg << "\n";	\
    }

namespace ChipGen 
{
    /************
    *  DEVICE  *
    ************/
    
    Device::Device()
    {
        alutInit(0, NULL);

        alGetError();
    }

    Device::~Device()
    {
        alutExit();
        //alcDestroyContext(context);
        //alcCloseDevice(device);
    }

    int Device::init()
    {
        //const ALCchar *defaultDevice;

        //// Open a new device
        //device = alcOpenDevice(NULL);
        //if (!device) {
        //    // SOMETHING HERE PLEASE
        //    std::cerr << "Could not initalize blank device" << std::endl;
        //    return 0;
        //}

        //// Test possible extensions
        //ALboolean enumeration = alcIsExtensionPresent(NULL, 
        //                                             "ALC_ENUMERATION_EXT");
        //if (enumeration == AL_FALSE) {
        //    // handle error
        //    std::cerr << "Enumeration not supported" << std::endl;
        //    return 0;
        //}

        //list_devices((alcGetString(NULL, ALC_DEVICE_SPECIFIER)));

        //defaultDevice = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

        //device = alcOpenDevice(defaultDevice);
        //if (!device) {
        //    std::cerr << "Could not open default device!" << std::endl;
        //    return 0;
        //}

        //std::cout << "Device bound to: " << 
        //    alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;

        //context = alcCreateContext(device, NULL);
        //if (!alcMakeContextCurrent(context)) {
        //    std::cerr << "Failed to create default context" << std::endl;
        //    return 0;
        //}

        
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

    /***********
    *  TRACK  *
    ***********/
    Track::Track(std::string file)
    {
        buffer = alutCreateBufferFromFile(file.c_str());

        if (buffer == AL_NONE) {
            std::cerr << "File load error: "
                << alutGetErrorString(alutGetError())
                << std::endl;
        }

        alGenSources((ALuint)1, &source);
        //alGenBuffers(1, &buffer);

        //alutLoadWAVFile(file, &format, &data, &size, &freq, &loop);
        //alBufferData(buffer, format, data, size, freq);
    }

    Track::~Track()
    {
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
    }

    void Track::play()
    {
        alSourcei(source, AL_LOOPING, AL_FALSE);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcePlay(source);
    }

    void Track::loop()
    {
        alSourcei(source, AL_LOOPING, AL_TRUE);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcePlay(source);
    }

    bool Track::playing()
    {
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        return source_state == AL_PLAYING;
    }

    void Track::setPitch(float pitch)
    {
        alSourcef(source, AL_PITCH, pitch);
    }

    void Track::setGain(float gain)
    {
        alSourcef(source, AL_GAIN, gain);
    }

    void Track::setPosition(float x, float y, float z)
    {
        alSource3f(source, AL_POSITION, x, y, z);
    }

    void Track::setVelocity(float x, float y, float z)
    {
        alSource3f(source, AL_VELOCITY, x, y, z);
    }

    /**************
    *  LISTENER  *
    **************/
    
    void Listener::setPosition(float x, float y, float z)
    {
        alListener3f(AL_POSITION, x, y, z);
    }

    void Listener::setVelocity(float x, float y, float z)
    {
        alListener3f(AL_VELOCITY, x, y, z);
    }

    void Listener::setOrientation(float orientation[])
    {
        alListenerfv(AL_ORIENTATION, orientation);
    }
    
}
