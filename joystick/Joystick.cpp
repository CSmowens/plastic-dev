////////////////////////////////////////////////////////////
// Copyright (c) 2011 - Hiairrassary Victor
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of its 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Joystick.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <cstring> 
#include <cstdio> 

namespace plt
{
    Joystick::Joystick
    (
    )
    {
        // Default value for axes
        for (int i = 0; i < Joy::AxisCount; ++i)
            Axis[i] = 0.f;
        Axis[Joy::AxisPOV] = -1.f;

        // Default value for buttons
        for (int i = 0; i < Joy::ButtonCount; ++i)
            Buttons[i] = false;
    }


    void Joystick::initialize
    (
        unsigned int index
    )
    {
        // Initial state
        myNbButtons = 0;
        myPovX = 0;
        myPovY = 0;
        for (int i = 0; i < Joy::ButtonCount; ++i)
        {
            Buttons[i] = false;
        }
        for (int i = 0; i < Joy::AxisCount; ++i)
        {
            Axis[i] = 0.f;
            myAxes[i] = false;
        }

        // Open the joystick handle
        std::ostringstream oss;
        oss << "/dev/input/js" << index;
        myDescriptor = open(oss.str().c_str(), O_RDONLY);
        if (myDescriptor > 0)
        {
	        char name[128];

            if (ioctl(myDescriptor, JSIOCGNAME(sizeof(name)), name) < 0)
                strncpy(name, "Unknown", sizeof(name));
            
            printf("Name: %s\n", name);


            // Use non-blocking mode
            fcntl(myDescriptor, F_SETFL, O_NONBLOCK);

            // Get number of buttons
            char nbButtons;
            ioctl(myDescriptor, JSIOCGBUTTONS, &nbButtons);
            myNbButtons = nbButtons;
            if (myNbButtons > Joy::ButtonCount)
                myNbButtons = Joy::ButtonCount;

            // Get the supported axes
            char nbAxes;
            ioctl(myDescriptor, JSIOCGAXES, &nbAxes);
            ioctl(myDescriptor, JSIOCGAXMAP, myAxesMapping);
            for (int i = 0; i < nbAxes; ++i)
            {
                switch (myAxesMapping[i])
                {
                    case ABS_X :                      myAxes[Joy::AxisX]   = true; break;
                    case ABS_Y :                      myAxes[Joy::AxisY]   = true; break;
                    case ABS_Z :                      myAxes[Joy::AxisZ]   = true; break;
                    case ABS_RZ :                     myAxes[Joy::AxisR]   = true; break;
                    case ABS_RX :                     myAxes[Joy::AxisU]   = true; break;
                    case ABS_RY :                     myAxes[Joy::AxisV]   = true; break;
                    case ABS_HAT0X : case ABS_HAT0Y : myAxes[Joy::AxisPOV] = true; break;
                    default : break;
                }
            }

            std::cout << "Joystick n° " << index << std::endl;
            std::cout << "Nombre of buttons : " << static_cast<int>(nbButtons) << std::endl;
            std::cout << "Number of axes : " << static_cast<int>(nbAxes) << std::endl;
        }

        else
            throw std::runtime_error("The file " + oss.str() + " doesn't exist!");
    }


    void Joystick::updateState()
    {
        if (myDescriptor > 0)
        {
            js_event joyState;
            while (read(myDescriptor, &joyState, sizeof(joyState)) > 0)
            {
                switch (joyState.type & ~JS_EVENT_INIT)
                {
                    // An axis has been moved
                    case JS_EVENT_AXIS :
                    {
                        switch (myAxesMapping[joyState.number])
                        {
                            case ABS_X :                      Axis[Joy::AxisX] = static_cast<float>(joyState.value) * 100.f / 32767.f; break;
                            case ABS_Y :                      Axis[Joy::AxisY] = static_cast<float>(joyState.value) * 100.f / 32767.f; break;
                            case ABS_Z :                      Axis[Joy::AxisZ] = static_cast<float>(joyState.value) * 100.f / 32767.f; break;
                            case ABS_RZ :                     Axis[Joy::AxisR] = static_cast<float>(joyState.value) * 100.f / 32767.f; break;
                            case ABS_RX :                     Axis[Joy::AxisU] = static_cast<float>(joyState.value) * 100.f / 32767.f; break;
                            case ABS_RY :                     Axis[Joy::AxisV] = static_cast<float>(joyState.value) * 100.f / 32767.f; break;
                            case ABS_HAT0X :                  myPovX = joyState.value;                                     break;
                            case ABS_HAT0Y :                  myPovY = joyState.value;                                     break;
                            default : break;
                        }

                        // Compute the new POV angle
                        if (myPovX > 0)
                        {
                            if      (myPovY > 0) Axis[Joy::AxisPOV] = 135.f;
                            else if (myPovY < 0) Axis[Joy::AxisPOV] = 45.f;
                            else                 Axis[Joy::AxisPOV] = 90.f;
                        }
                        else if (myPovX < 0)
                        {
                            if      (myPovY > 0) Axis[Joy::AxisPOV] = 225.f;
                            else if (myPovY < 0) Axis[Joy::AxisPOV] = 315.f;
                            else                 Axis[Joy::AxisPOV] = 270.f;
                        }
                        else
                        {
                            if      (myPovY > 0) Axis[Joy::AxisPOV] = 180.f;
                            else if (myPovY < 0) Axis[Joy::AxisPOV] = 0.f;
                            else                 Axis[Joy::AxisPOV] = -1.f;
                        }

                        break;
                    }

                    // A button has been pressed
                    case JS_EVENT_BUTTON :
                    {
                        if (joyState.number < getButtonsCount())
                            Buttons[joyState.number] = (joyState.value != 0);
                        break;
                    }
                }
            }
        }
    }


    bool Joystick::hasAxis
    (
        Joy::Axis axis
    ) const
    {
        return myAxes[axis];
    }


    unsigned int Joystick::getButtonsCount
    (

    ) const
    {
        return myNbButtons;
    }

} // namespace plt

