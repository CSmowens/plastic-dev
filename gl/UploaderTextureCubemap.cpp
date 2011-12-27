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
#include "UploaderTextureCubemap.hpp"

#include <Plastic/Core/PixelFormat.hpp>

#include "GLCheck.hpp"
#include "GLEnum.hpp"

namespace plt
{
    TextureType UploaderTextureCubemap::getTextureTypeToLoad
    (
    )   
    {
        return TextureType::Cubemap;
    }


    GLenum UploaderTextureCubemap::getGLSLType
    (
        PixelFormat format
    )
    {
        return GLEnum::getGLSLTypeTextureCubemap(format);
    }


    GLenum UploaderTextureCubemap::getGLTarget
    (
    )
    {
        return GL_TEXTURE_CUBE_MAP;
    }


    void UploaderTextureCubemap::checkImages
    (
        TextureMipmapFlag texMipMapFlag,
        const std::vector< std::shared_ptr<Image> > &images
    )
    {
        if(images.size() != 6)
            throw std::runtime_error("CubeMap must have 6 images");

        checkFirstImage(texMipMapFlag, images[0]);
        checkOtherImages(texMipMapFlag, images);
    }


    void UploaderTextureCubemap::uploadImages
    (
        TextureMipmapFlag texMipMapFlag,
        const std::vector< std::shared_ptr<Image> > &images
    )
    {
        PixelFormat format = (*images[0])[0].getFormat();

        unsigned int levelsCount = (texMipMapFlag == TextureMipmapFlag::FromImage) ? (*images[0]).levels() : 1;

        for(std::size_t i(0); i<levelsCount; ++i)
        {
            for (unsigned int j = 0; j<6; j++)
            {
                uvec2 dim = (*images[j])[i].getDimensions();
    
                if( !PixelFormatInfos::getInfos(format).isCompressed() )
                    GLCheck( glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, i, 0, 0, dim.x, dim.y, GLEnum::getExternalFormat(format), GLEnum::getType(format), (*images[j])[i].getPixels() ));

                else
                    GLCheck( glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, i, 0, 0 , dim.x, dim.y, GLEnum::getExternalFormat(format), dim.x * dim.y * PixelFormatInfos::getInfos(format).size(), (*images[j])[i].getPixels()));
            }

        }

        if(texMipMapFlag == TextureMipmapFlag::GenHardware)
            GLCheck( glGenerateMipmap(GL_TEXTURE_CUBE_MAP) );
    }


    void UploaderTextureCubemap::allocateTextureMemory
    (
        PixelFormat format, 
        const uvec2 &dimensions,
        unsigned int levels
    )
    {
        checkDimensionsArePowerOfTwo(dimensions);

        unsigned int width = dimensions.x;
        unsigned int height = dimensions.y;

        for (unsigned int i = 0; i<levels; ++i)
        {
            for (unsigned int j = 0; j<6; j++)
            {
                GLCheck( glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, i, GLEnum::getInternalFormat(format), width, height, 0, GLEnum::getExternalFormat(format), GLEnum::getType(format), NULL));
            }
            width = std::max(1u, width/2);
            height = std::max(1u, height/2);
        }
    }


} // namespace plt
