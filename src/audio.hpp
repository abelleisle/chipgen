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

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <string>


namespace ChipGen 
{
    /************
    *  DEVICE  *
    ************/
    
    class Device
    {
        private:
            ALCdevice *device;
            ALCcontext *context;
        public:
            Device();
           ~Device();

            int init();
            static void list_devices(const ALCchar* devices);
    };

    /***********
    *  TRACK  *
    ***********/

    class Track
    {
        private:
            ALuint buffer, source;
            ALint source_state;
        public:
            Track(std::string);
            ~Track();

            void play();
            void loop();
            bool playing();
            
            void setPitch(float);
            void setGain(float);
            void setPosition(float, float, float);
            void setVelocity(float, float, float);
    };

    /**************
    *  LISTENER  *
    **************/
    class Listener
    {
        private:
        public:
            void setPitch(float);
            void setGain(float);
            void setPosition(float, float, float);
            void setVelocity(float, float, float);
            void setOrientation(float[]);
    };
    

}

#endif //AUDIO_HPP
