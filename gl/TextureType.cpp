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
#include "TextureType.hpp"

#include <stdexcept>


namespace plt
{
	std::map<TextureType, TextureTypeInfos> TextureTypeInfos::m_typesInfos = 
    {
        std::make_pair(TextureType::OneDimension,         TextureTypeInfos(true, false)),
        std::make_pair(TextureType::TwoDimensions,        TextureTypeInfos(true, false)),
        std::make_pair(TextureType::Rectangle,            TextureTypeInfos(true, false)),

        std::make_pair(TextureType::Cubemap,              TextureTypeInfos(false, true)),

        std::make_pair(TextureType::OneDimensionArray,    TextureTypeInfos(false, true)),
        std::make_pair(TextureType::TwoDimensionsArray,   TextureTypeInfos(false, true)),
        std::make_pair(TextureType::CubemapArray,         TextureTypeInfos(false, true))
    };



    TextureTypeInfos& TextureTypeInfos::getInfos
    (
        TextureType type
    )
    {
        auto it = m_typesInfos.find(type);

        if(it == m_typesInfos.end())
            throw std::runtime_error("Unregistered TextureType");

        else
            return it->second;
    }














    TextureTypeInfos::TextureTypeInfos
    (
        bool hasSingleImage, 
        bool hasMultiImages
    ) :
    m_hasSingleImage(hasSingleImage),
    m_hasMultiImages(hasMultiImages)
    {

    }


    bool TextureTypeInfos::hasSingleImage
    (
    ) const
    {
        return m_hasSingleImage;
    }


    bool TextureTypeInfos::hasMultiImages
    (
    ) const
    {
        return m_hasMultiImages;
    }


} // namespace plt
