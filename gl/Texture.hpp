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


#ifndef PLASTIC_TEXTURE_HPP
#define PLASTIC_TEXTURE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Core/Image.hpp>
#include <Plastic/Core/PixelFormat.hpp>

#include <Plastic/OpenGL.hpp>

#include "TextureType.hpp"

#include <memory>
#include <vector>

namespace plt
{
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    enum class TextureMipmapFlag
    {
        NoMipMap,
        FromImage,
        GenHardware
    };


	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class Texture
    {

    public:
        Texture();

        Texture(TextureType texType, PixelFormat format, unsigned int image, const uvec2 &dimensions);

        Texture(TextureType texType, TextureMipmapFlag texMipMapFlag, const std::shared_ptr<Image> &image);

        Texture(TextureType texType, TextureMipmapFlag texMipMapFlag, const std::vector< std::shared_ptr<Image> > &images);

        ~Texture();

        void bind() const;

        void unbind() const;

        GLenum getGLSLType() const;

        GLuint getOpenGLTarget() const;

        GLuint getOpenGLHandle() const;

        PixelFormat getPixelFormat() const;

        TextureType getTextureType() const;

        const uvec2& getDimensions() const;

        bool hasMipmaps() const;




        static unsigned int getMipMapLevelsCount(unsigned int width, unsigned int height);

        static unsigned int nearestPowerOfTwo(unsigned int value);

    private:
        void initializeEmptyTexture(TextureType texType, PixelFormat format, unsigned int image, const uvec2 &dimensions);

        void initializeTextureSingle(TextureType texType, TextureMipmapFlag texMipMapFlag, const std::shared_ptr<Image> &image);

        void initializeTextureArray(TextureType texType, TextureMipmapFlag texMipMapFlag, const std::vector< std::shared_ptr<Image> > &images);

        void cleanUp();

		////////////////////////////////////////////////////////////
		// Member data
		//////////////////////////////////////////////////////////// 
        PixelFormat m_format;
        TextureType m_textureType;

        uvec2 m_dimensions;

        TextureMipmapFlag m_textureMipMapFlag;

        bool m_hasMipMap;
        
        GLuint m_texture;   
        GLenum m_target;
        GLenum m_glslType;
    };

} // namespace plt


#endif // PLASTIC_TEXTURE_HPP




////////////////////////////////////////////////////////////
/// \class plt::Texture
///
/// \todo Etre exception safe
/// \todo Sortir le #define PLASTIC_DEBUG 1
/// \todo Utiliser les delegating constructor pour le constructeur par defaut
/// 
/// \todo Les fonctions initialiaze nécessite un refactoring...
///
////////////////////////////////////////////////////////////
