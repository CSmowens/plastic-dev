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
#include "UploaderTexture.hpp"

#include "GLCheck.hpp"
#include "GLEnum.hpp"

#include <stdexcept>

namespace plt
{
    void UploaderTexture::checkDimensionsArePlasticOfTwo
    (
        const uvec2 &dimensions
    )
    {
        if( !isPlasticOfTwo(dimensions.x) || !isPlasticOfTwo(dimensions.y) )
            throw std::runtime_error("Image haven't got dimensions in plastic of two, try TextureRect instead");
    }


    void UploaderTexture::checkFirstImage
    (
        TextureMipmapFlag texMipMapFlag, 
        const std::shared_ptr<Image> &image
    )
    {
        PixelFormat format = (*image)[0].getFormat();
        uvec2 dimensions = (*image)[0].getDimensions();


        checkDimensionsArePlasticOfTwo(dimensions);


        if(texMipMapFlag == TextureMipmapFlag::FromImage)
        {
            unsigned int nbMipmaps = Texture::getMipMapLevelsCount(dimensions.x, dimensions.y);

            if(image->levels()-1 != nbMipmaps)
                throw std::runtime_error("The image doesn't contains all mipmap to 1x1");

            for(std::size_t i(1); i<image->levels(); ++i)
            {
                if( (*image)[i].getFormat() != format)
                    throw std::runtime_error("All mipmaps haven't the same format than base level image");

                uvec2 dim = (*image)[i-1].getDimensions() / 2;

                if(dim.x < 1) dim.x = 1;
                if(dim.y < 1) dim.y = 1;

                if(dim != (*image)[i].getDimensions())
                    throw std::runtime_error("A mipmap hasn't got good dimensions");  
            }
        }

        else if(texMipMapFlag == TextureMipmapFlag::GenHardware)
        {
            if( isCompressedFormat(format) )
                throw std::runtime_error("Hardware mipmap generation is impossible on compressed format");
        }
    }


    void UploaderTexture::checkOtherImages
    (
        TextureMipmapFlag texMipMapFlag, 
        const std::vector< std::shared_ptr<Image> > &images
    )
    {
        unsigned int mipmapCount = (*images[0]).levels();

        PixelFormat baseFormat = (*images[0])[0].getFormat();

        for(std::size_t i(0); i<images.size(); ++i)
        {
            if((*images[i]).levels() != mipmapCount)
                throw std::runtime_error("All images haven't got the same number of mipmap count");

            for(std::size_t j(0); j<mipmapCount; ++j)
            {
                if((*images[i])[j].getFormat() != baseFormat)
                    throw std::runtime_error("A level haven't got the same pixel format");

                if((*images[i])[j].getDimensions() != (*images[0])[j].getDimensions())
                    throw std::runtime_error("A level haven't got the same dimensions");
            }
        }
    }

} // namespace plt