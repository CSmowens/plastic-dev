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
#include "RenderTexture.hpp"

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

#include <stdexcept>

namespace plt
{
    RenderImage::RenderImage
    (

    ) :
    RenderTarget()
    {
        // Mettre à jour le viewport
        try
        {
            initialize();
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during RenderImage initialisation");
        }  
    }


    RenderImage::~RenderImage
    (
    )
    {
        cleanUp();
    }


    unsigned int RenderImage::getWidth
    (
    ) const
    {
        return 0;
    }


    unsigned int RenderImage::getHeight
    (
    ) const
    {
        return 0;
    }


    void RenderImage::bind
    (
    )
    {
        GLCheck( glBindFramebuffer(GL_FRAMEBUFFER, m_fbo) );
    }


    GLuint RenderImage::getGLHandle
    (
    )
    {
        return m_fbo;
    }


    void RenderImage::initialize
    (
    )
    {
        GLCheck( glGenFramebuffers(1, &m_fbo) );
        GLCheck( glBindFramebuffer(GL_FRAMEBUFFER, m_fbo) );

        checkFramebufferObject();
    }


    void RenderImage::cleanUp
    (
    )
    {
        if( glIsFramebuffer(m_fbo) )
            GLCheck( glDeleteFramebuffers(1, &m_fbo) );
    }


    void RenderImage::checkFramebufferObject
    (
    )
    {
        GLenum errorCode;

        GLCheck( errorCode = glCheckFramebufferStatus(GL_FRAMEBUFFER) );

        if (errorCode != GL_FRAMEBUFFER_COMPLETE)
        {
            std::string error = "unknown error";
            std::string description  = "no description";

            // Decode the error code
            switch (errorCode)
            {
                case GL_FRAMEBUFFER_UNDEFINED:
                {
                    error = "GL_FRAMEBUFFER_UNDEFINED";
                    description = "the default framebuffer does not exist";
                    break;
                }

                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                {
                    error = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
                    description = "any of the framebuffer attachment points are framebuffer incomplete";
                    break;
                }

                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                {
                    error = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
                    description = "the framebuffer does not have at least one image attached to it";
                    break;
                }

                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                {
                    error = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
                    description = "the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAWBUFFERi";
                    break;
                }

                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                {
                    error = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
                    description = "GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER";
                    break;
                }

                case GL_FRAMEBUFFER_UNSUPPORTED:
                {
                    error = "GL_FRAMEBUFFER_UNSUPPORTED";
                    description = "the combination of internal formats of the attached images violates an implementation-dependent set of restrictions";
                    break;
                }

                case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                {
                    error = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
                    description = "the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES OR the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures";
                    break;
                }


                case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                {
                    error = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
                    description = "any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target";
                    break;
                }

                throw std::runtime_error("Framebuffer is not complete : " + error + " : " + description);

            }
        }
    }

} // namespace plt

