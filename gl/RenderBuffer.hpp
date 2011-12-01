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


#ifndef PLASTIC_RENDERBUFFER_HPP
#define PLASTIC_RENDERBUFFER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Core/PixelFormat.hpp>
#include <Plastic/Core/Vector2.hpp>

#include <Plastic/OpenGL.hpp>

namespace plt
{
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class RenderBuffer
    {

    public:
        RenderBuffer();

        RenderBuffer(PixelFormat format, const uvec2 &dimensions);

        ~RenderBuffer();

        void bind() const;

        void unbind() const;

        GLenum getGLSLType() const;

        GLuint getOpenGLHandle() const;

        PixelFormat getPixelFormat() const;


    private:
        void initialize(PixelFormat format, const uvec2 &dimensions);

        void cleanUp();

		////////////////////////////////////////////////////////////
		// Member data
		//////////////////////////////////////////////////////////// 
        GLuint m_renderbuffer;
        
        PixelFormat m_format;

        uvec2 m_dimensions;
    };

} // namespace plt


#endif // PLASTIC_RENDERBUFFER_HPP




////////////////////////////////////////////////////////////
/// \class plt::RenderBuffer
///
/// \todo Etre exception safe
/// \todo Sortir le #define PLASTIC_DEBUG 1
/// \todo Utiliser les delegating constructor pour le constructeur par defaut
///
////////////////////////////////////////////////////////////
