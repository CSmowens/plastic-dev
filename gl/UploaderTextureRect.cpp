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
#include "UploaderTextureRect.hpp"

#include <Plastic/Core/PixelFormatInfos.hpp>

#include "GLCheck.hpp"
#include "GLEnum.hpp"

namespace plt
{
    TextureType UploaderTextureRect::getTextureTypeToLoad
    (
    )   
    {
        return TextureType::Rectangle;
    }


    GLenum UploaderTextureRect::getGLSLType
    (
        PixelFormat format
    )
    {
        return GLEnum::getGLSLTypeTextureRect(format);
    }


    GLenum UploaderTextureRect::getGLTarget
    (
    )
    {
        return GL_TEXTURE_RECTANGLE;
    }


    void UploaderTextureRect::checkImages
    (
        TextureMipmapFlag texMipMapFlag,
        const std::vector< std::shared_ptr<Image> > &images
    )
    {
        if(texMipMapFlag != TextureMipmapFlag::NoMipMap)
            throw std::runtime_error("Mipmapping is impossible with texture rectangle");
    }


    void UploaderTextureRect::uploadImages
    (
        TextureMipmapFlag texMipMapFlag,
        const std::vector< std::shared_ptr<Image> > &images
    )
    {
        auto image = images[0];
        PixelFormat format = (*image)[0].getFormat();

        uvec2 dim = (*image)[0].getDimensions();

        if( !getPixelFormatInfos(format).isCompressed() )
            GLCheck( glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, dim.x, dim.y, GLEnum::getExternalFormat(format), GLEnum::getType(format), (*image)[0].getPixels() ));

        else
            GLCheck( glCompressedTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0 , dim.x, dim.y, GLEnum::getExternalFormat(format), dim.x * dim.y * getPixelFormatInfos(format).size(), (*image)[0].getPixels()));
    }


    void UploaderTextureRect::allocateTextureMemory
    (
        PixelFormat format, 
        const uvec2 &dimensions,
        unsigned int levels
    )
    {
        // Use glTexStorage2D instead, it's the same but OpenGL 4.2!!
		//GLCheck(glTexStorage2D(GL_TEXTURE_RECTANGLE, 1, GLEnum::getInternalFormat(format), dimensions.x, dimensions.y));

        if(levels != 1)
            throw std::runtime_error("Levels != 1");

        GLCheck( glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GLEnum::getInternalFormat(format), dimensions.x, dimensions.y, 0, GLEnum::getExternalFormat(format), GLEnum::getType(format), NULL ));
    }


} // namespace plt
