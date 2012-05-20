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


#ifndef PLASTIC_GLCHECK_HPP
#define PLASTIC_GLCHECK_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Config.hpp>

#include <string>


namespace plt
{
    namespace priv
    {
        ////////////////////////////////////////////////////////////
        /// Let's define a macro to quickly check every OpenGL
        /// API calls
        ////////////////////////////////////////////////////////////
        #if PLASTIC_DEBUG == 1

            // In debug mode, perform a test on every OpenGL call
            #define GLCheck(call) ((call), priv::GLCheckError(__FILE__, __LINE__))

        #else

            // Else, we don't add any overhead
            #define GLCheck(call) (call)

        #endif

        ////////////////////////////////////////////////////////////
        /// \brief Check the last OpenGL error
        ///
        /// \param file Source file where the call is located
        /// \param line Line number of the source file where the call is located
        ///
        ////////////////////////////////////////////////////////////
        void GLCheckError(const std::string& file, unsigned int line);


    } // namespace priv


} // namespace plt


#endif // PLASTIC_GLCHECK_HPP
