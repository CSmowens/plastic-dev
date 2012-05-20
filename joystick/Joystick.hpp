////////////////////////////////////////////////////////////
// Copyright (c) 2011 - 2012 Hiairrassary Victor
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

#ifndef PLASTIC_JOYSTICK_HPP
#define PLASTIC_JOYSTICK_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <linux/joystick.h>
#include <fcntl.h>

namespace plt
{
    namespace Joy
    {
        enum Axis
        {
            AxisX,   ///< The X axis
            AxisY,   ///< The Y axis
            AxisZ,   ///< The Z axis
            AxisR,   ///< The R axis
            AxisU,   ///< The U axis
            AxisV,   ///< The V axis
            AxisPOV, ///< The Point-Of-View axis (hat)

            AxisCount // Keep last -- total number of joystick axis
        };

        enum
        {
            Count       = 8, ///< Total number of supported joysticks
            ButtonCount = 32 ///< Total number of supported joystick buttons
        };

    }


    class Joystick
    {
        public :
            Joystick();
            void initialize(unsigned int index);
            void updateState();
            bool hasAxis(Joy::Axis Axis) const;
            unsigned int getButtonsCount() const;

        public:
            float Axis[Joy::AxisCount];      ///< Position on each axis in range [-100, 100] (except POV which is [0, 360])
            bool  Buttons[Joy::ButtonCount]; ///< Status of each button (true = pressed)

        private :
            int           myDescriptor;               ///< Linux descriptor of the joystick
            unsigned int  myNbButtons;                ///< Number of buttons supported by the joystick
            bool          myAxes[Joy::AxisCount];     ///< Supported axes
            int           myPovX;                     ///< Last X position of the POV
            int           myPovY;                     ///< Last Y position of the POV
            char          myAxesMapping[ABS_MAX + 1]; ///< Axes mapping (index --> axis id)

    };


} //namespace plt

#endif // PLASTIC_JOYSTICK_HPP

