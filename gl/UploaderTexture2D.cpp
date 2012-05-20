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


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "UploaderTexture2D.hpp"

#include <Plastic/Core/PixelFormat.hpp>

#include "GLCheck.hpp"
#include "GLEnum.hpp"

namespace plt
{
    TextureType UploaderTexture2D::getTextureTypeToLoad
    (
    )   
    {
        return TextureType::TwoDimensions;
    }


    GLenum UploaderTexture2D::getGLSLType
    (
        PixelFormat format
    )
    {
        return GLEnum::getGLSLTypeTexture2D(format);
    }


    GLenum UploaderTexture2D::getGLTarget
    (
    )
    {
        return GL_TEXTURE_2D;
    }


    void UploaderTexture2D::checkImage
    (
        TextureMipmapFlag texMipMapFlag,
        const std::shared_ptr<Image> &image
    )
    {
        checkFirstImage(texMipMapFlag, image);
    }


    void UploaderTexture2D::uploadImage
    (
        TextureMipmapFlag texMipMapFlag,
        const std::shared_ptr<Image> &image
    )
    {
        PixelFormat format = (*image)[0].getFormat();

        unsigned int levelsCount = (texMipMapFlag == TextureMipmapFlag::FromImage) ? image->levels() : 1;

        for(std::size_t i(0); i<levelsCount; ++i)
        {
            uvec2 dim = (*image)[i].getDimensions();

            if( !PixelFormatInfos::getInfos(format).isCompressed() )
                GLCheck( glTexSubImage2D(GL_TEXTURE_2D, i, 0, 0, dim.x, dim.y, GLEnum::getExternalFormat(format), GLEnum::getType(format), (*image)[i].getPixels() ));

            else
                GLCheck( glCompressedTexSubImage2D(GL_TEXTURE_2D, i, 0, 0 , dim.x, dim.y, GLEnum::getExternalFormat(format), dim.x * dim.y * PixelFormatInfos::getInfos(format).size(), (*image)[i].getPixels()));
        }

        if(texMipMapFlag == TextureMipmapFlag::GenHardware)
            GLCheck( glGenerateMipmap(GL_TEXTURE_2D) );
    }


    void UploaderTexture2D::allocateTextureMemory
    (
        PixelFormat format, 
        const uvec2 &dimensions,
        unsigned int levels
    )
    {
        checkDimensionsArePowerOfTwo(dimensions);
       
        // Use glTexStorage2D instead, it's the same but OpenGL 4.2!! Remplacer même l'exception
		//GLCheck(glTexStorage2D(GL_TEXTURE_2D, levels, GLEnum::getInternalFormat(format), dimensions.x, dimensions.y));

        if(levels < 1)
            throw std::runtime_error("Levels < 1");

        unsigned int width = dimensions.x;
        unsigned int height = dimensions.y;

        for (unsigned int i(0); i<levels; i++)
        {
            GLCheck( glTexImage2D(GL_TEXTURE_2D, i, GLEnum::getInternalFormat(format), width, height, 0, GLEnum::getExternalFormat(format), GLEnum::getType(format), NULL ));
            width = std::max(1u, width/2);
            height = std::max(1u, height/2);
        }
    }


} // namespace plt
