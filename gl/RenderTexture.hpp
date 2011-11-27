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


#ifndef PLASTIC_RENDERIMAGE_HPP
#define PLASTIC_RENDERIMAGE_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Graphics/RenderTarget.hpp>

#include <Plastic/OpenGL.hpp>

#include <Plastic/Core/Vector2.hpp>

namespace plt
{

    ////////////////////////////////////////////////////////////
    /// 
    ///
    ////////////////////////////////////////////////////////////
    class RenderImage : public RenderTarget
    {

    public:
        ////////////////////////////////////////////////////////////
		/// \brief Default constructor
        ///
		////////////////////////////////////////////////////////////
        RenderImage();

        virtual ~RenderImage();

        ////////////////////////////////////////////////////////////
        /// \brief Return the width of the render target
        ///
        /// \return Width in pixels
        ///
        /// \see getHeight
        ///
        ////////////////////////////////////////////////////////////
        virtual unsigned int getWidth() const;

        ////////////////////////////////////////////////////////////
        /// \brief Return the height of the render target
        ///
        /// \return Height in pixels
        ///
        /// \see getWidth
        ///
        ////////////////////////////////////////////////////////////
        virtual unsigned int getHeight() const;

        virtual void bind() const;

        virtual void clear() const;

        GLuint getGLHandle();

    private:
        void initialize();

        void cleanUp();
        
        void checkFramebufferObject();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
        GLuint m_fbo;
        GLuint m_rboDepth;
    };


} // namespace plt


#endif // PLASTIC_RENDERIMAGE_HPP




////////////////////////////////////////////////////////////
/// \class plt::RenderImage
///
/// \todo Etre exception safe
/// \todo Renvoyer aussi l'erreur OpenGL
/// \todo Sortir le #define PLASTIC_DEBUG 1
///
////////////////////////////////////////////////////////////
