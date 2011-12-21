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
#include "UploaderTexture1DArray.hpp"

#include <Plastic/Core/PixelFormatInfos.hpp>

#include "GLCheck.hpp"
#include "GLEnum.hpp"

namespace plt
{
    TextureType UploaderTexture1DArray::getTextureTypeToLoad
    (
    )   
    {
        return TextureType::OneDimensionArray;
    }


    GLenum UploaderTexture1DArray::getGLSLType
    (
        PixelFormat format
    )
    {
        return GLEnum::getGLSLTypeTexture1DArray(format);
    }


    GLenum UploaderTexture1DArray::getGLTarget
    (
    )
    {
        return GL_TEXTURE_1D_ARRAY;
    }


    void UploaderTexture1DArray::checkImages
    (
        TextureMipmapFlag texMipMapFlag,
        const std::vector< std::shared_ptr<Image> > &images
    )
    {
        if((*images[0])[0].getDimensions().y != 1)
            throw std::runtime_error("1D texture must have an height of one");

        checkFirstImage(texMipMapFlag, images[0]);
        checkOtherImages(texMipMapFlag, images);
    }


    void UploaderTexture1DArray::uploadImages
    (
        TextureMipmapFlag texMipMapFlag,
        const std::vector< std::shared_ptr<Image> > &images
    )
    {

    }


    void UploaderTexture1DArray::allocateTextureMemory
    (
        PixelFormat format, 
        const uvec2 &dimensions,
        unsigned int levels
    )
    {
        checkDimensionsArePowerOfTwo(dimensions);
    }


} // namespace plt
