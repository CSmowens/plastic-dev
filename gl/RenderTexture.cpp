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

#include "GLEnum.hpp"

#include <algorithm>
#include <stdexcept>

namespace plt
{
    RenderTexture::RenderTexture
    (
        const uvec2 &dimensions
    ) :
    RenderTarget(),
    m_dimensions(dimensions)
    {
        try
        {
            initialize();
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during RenderTexture initialisation");
        }  
    }


    RenderTexture::~RenderTexture
    (
    )
    {
        cleanUp();
    }


    unsigned int RenderTexture::getWidth
    (
    ) const
    {
        return m_dimensions.x;
    }


    unsigned int RenderTexture::getHeight
    (
    ) const
    {
        return m_dimensions.y;
    }


    void RenderTexture::bind
    (
    ) const
    {
        GLCheck( glBindFramebuffer(GL_FRAMEBUFFER, m_fbo) );

	    GLCheck(glDrawBuffers(m_drawBuffers.size(), &m_drawBuffers[0]));
    }


    void RenderTexture::unbind
    (
    ) const
    {
        GLCheck( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
    }


    void RenderTexture::clear
    (
    ) const
    {
        GLCheck( glClear(m_clearMask) );
    }



    GLuint RenderTexture::getGLHandle
    (
    )
    {
        return m_fbo;
    }


    void RenderTexture::initialize
    (
    )
    {
        m_viewport.width = m_dimensions.x;
        m_viewport.height = m_dimensions.y;

        m_clearMask = 0;

        m_maxColorAttachments = 0;
        GLCheck( glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &m_maxColorAttachments) );
        

        m_depthAttachment.first = false;


        GLCheck( glGenFramebuffers(1, &m_fbo) );
        bind();
        unbind();
    }


    void RenderTexture::cleanUp
    (
    )
    {
        if( glIsFramebuffer(m_fbo) )
            GLCheck( glDeleteFramebuffers(1, &m_fbo) );
    }


    void RenderTexture::checkDimensions
    (
        const uvec2 &dimensions
    )
    {
        if(m_colorAttachments.size() > 0 || m_depthAttachment.first)
        {
            if(dimensions != m_dimensions)
                throw std::runtime_error("All attached image must have same dimensions");
        }

        else m_dimensions = dimensions;
    }



















    void RenderTexture::attachDepthBuffer
    (
        const std::shared_ptr<Texture> &texture
    )
    {
        if(m_depthAttachment.first)
            throw std ::runtime_error("Framebuffer have got already a depht buffer");

        checkDimensions(texture->getDimensions());

        attachTexture(texture, GL_DEPTH_ATTACHMENT);

        m_depthAttachment = std::make_pair(true, AttachedImageType::Texture);
        m_clearMask |= GL_DEPTH_BUFFER_BIT;
    }


    void RenderTexture::attachDepthBuffer
    (
        const std::shared_ptr<RenderBuffer> &renderbuffer    
    )
    {
        if(m_depthAttachment.first)
            throw std ::runtime_error("Framebuffer have got already a depht buffer");

        checkDimensions(renderbuffer->getDimensions());

        GLCheck( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->getOpenGLHandle()) );

        m_depthAttachment = std::make_pair(true, AttachedImageType::RenderBuffer);
        m_clearMask |= GL_DEPTH_BUFFER_BIT;
    }
    

    void RenderTexture::detachDepthBuffer
    (
    )
    {
        if(!m_depthAttachment.first)
            throw std ::runtime_error("Framebuffer haven't got a depht buffer");


        if(m_depthAttachment.second == AttachedImageType::Texture)
            detachTexture(GL_DEPTH_ATTACHMENT);

        else
            GLCheck( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0) );

        m_depthAttachment.first = false;
        m_clearMask ^= GL_DEPTH_BUFFER_BIT;
    }













    void RenderTexture::attachColorBuffer
    (
        const std::shared_ptr<Texture> &texture, 
        unsigned int attachment
    )
    {
        auto it = m_colorAttachments.find(attachment);

        if(it != m_colorAttachments.end())
            throw std::runtime_error("Framebuffer have already a color buffer on this attachment");

        checkDimensions(texture->getDimensions());

        attachTexture(texture, GL_COLOR_ATTACHMENT0 + attachment);

        m_colorAttachments.insert(std::make_pair(attachment, AttachedImageType::Texture));
        m_clearMask |= GL_COLOR_BUFFER_BIT;
        m_drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + attachment);
    }


    void RenderTexture::attachColorBuffer
    (
        const std::shared_ptr<RenderBuffer> &renderbuffer, 
        unsigned int attachment
    )
    {
        auto it = m_colorAttachments.find(attachment);

        if(it != m_colorAttachments.end())
            throw std::runtime_error("Framebuffer have already a color buffer on this attachment");

        checkDimensions(renderbuffer->getDimensions());
        GLCheck( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_RENDERBUFFER, renderbuffer->getOpenGLHandle()) );

        m_colorAttachments.insert(std::make_pair(attachment, AttachedImageType::RenderBuffer));
        m_clearMask |= GL_COLOR_BUFFER_BIT;
        m_drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + attachment);
    }

    
    void RenderTexture::detachColorBuffer
    (
        unsigned int attachment
    )
    {
        auto it = m_colorAttachments.find(attachment);

        if(it == m_colorAttachments.end())
            throw std::runtime_error("Framebuffer haven't a color buffer on this attachment");

        if(m_depthAttachment.second == AttachedImageType::Texture)
            detachTexture(GL_COLOR_ATTACHMENT0 + attachment);

        else
            GLCheck( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_RENDERBUFFER, 0) );

        m_colorAttachments.erase(it);

        if(m_colorAttachments.size() == 0)
            m_clearMask ^= GL_COLOR_BUFFER_BIT;

        m_drawBuffers.erase( std::find(m_drawBuffers.begin(), m_drawBuffers.end(), GL_COLOR_ATTACHMENT0 + attachment) );
    }






















    void RenderTexture::attachTexture
    (
        const std::shared_ptr<Texture> &texture, 
        GLenum attachment
    )   
    {
        switch(texture->getTextureType())
        {
            case TextureType::TwoDimensions:
            case TextureType::Rectangle:
                GLCheck( glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, texture->getOpenGLTarget(), texture->getOpenGLHandle(), 0) );
                break;

            default:
                throw std::runtime_error("Impossible to attach a texture of this type");
                break;
        }
    }


    void RenderTexture::detachTexture
    (
        GLenum attachment
    )
    {
        GLCheck( glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_RECTANGLE, 0, 0) );
/*
        switch(texture->getTextureType())
        {
            case TextureType::TwoDimensions:
                GLCheck( glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, 0, 0) );
                break;

            case TextureType::Rectangle:
                GLCheck( glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_RECTANGLE, 0, 0) );
                break;

            default:
                throw std::runtime_error("Impossible to detach a texture of this type");
                break;
        }
*/
    }
















    void RenderTexture::checkValidity
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
                    description = "the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TURE_SAMPLES is the not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TURE_SAMPLES OR the value of GL_TURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_TURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures";
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

