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
#include "RenderBuffer.hpp"

#include "GLEnum.hpp"

#include <Plastic/Core/Vector2.hpp>

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

#include <stdexcept>

namespace plt
{
    RenderBuffer::RenderBuffer
    (
    )
    {

    }


    RenderBuffer::RenderBuffer
    (
        PixelFormat format,
        const uvec2 &dimensions
    )
    {
        try
        {
            initialize(format, dimensions);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during RenderBuffer initialisation");
        }  
    }


    RenderBuffer::~RenderBuffer
    (
    )
    {
        cleanUp();   
    }


    void RenderBuffer::cleanUp
    (
    )
    {
        if( glIsRenderbuffer(m_renderbuffer) )
            GLCheck( glDeleteRenderbuffers(1, &m_renderbuffer) );
    }


    void RenderBuffer::bind
    (
    ) const
    {
        GLCheck( glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer) );
    }


    void RenderBuffer::unbind
    (
    ) const
    {
        GLCheck( glBindRenderbuffer(GL_RENDERBUFFER, 0) );
    }


    GLuint RenderBuffer::getOpenGLHandle
    (
    ) const
    {
        return m_renderbuffer;
    }


    PixelFormat RenderBuffer::getPixelFormat
    (
    ) const
    {
        return m_format;
    }


    void RenderBuffer::initialize
    (
        PixelFormat format,
        const uvec2 &dimensions
    )
    {
        m_format = format;
        m_dimensions = dimensions;

        GLCheck(glGenRenderbuffers(1, &m_renderbuffer) );

        bind();
            GLCheck(glRenderbufferStorage(GL_RENDERBUFFER, GLEnum::getInternalFormat(m_format), m_dimensions.x, m_dimensions.y) );
        unbind();
    }

} // namespace plt
