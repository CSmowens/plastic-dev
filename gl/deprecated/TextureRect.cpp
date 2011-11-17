////////////////////////////////////////////////////////////
// Plastic, an open source high performance realtime 3D engine.
// Copyright (C) 2010-2011 Hiairrassary Victor
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "TextureRect.hpp"

#include "GLEnum.hpp"

#include <Plastic/Core/Vector2.hpp>

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

namespace plt
{

    TextureRect::TextureRect
    (
        std::shared_ptr<Image> &image
    ) 
    {
        try
        {
            initialize(image);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during TextureRect initialisation");
        }  
    }


    TextureRect::~TextureRect
    (
    )
    {
    
    }


    void TextureRect::bind
    (
    )
    {
        GLCheck( glBindTexture(GL_TEXTURE_RECTANGLE, m_texture) );
    }


    GLenum TextureRect::getGLSLType
    (
    )
    {
        return GLEnum::getGLSLTypeTextureRect(m_format);
    }


    void TextureRect::initialize
    (
        std::shared_ptr<Image> &image
    )
    {
        // L'assertion pourra être enlever si on garde le fait qu'une image à toujours au moins un niveau
        if( image->levels() < 1)
            throw std::runtime_error("Image haven't got image level");

        PixelFormat m_format = (*image)[0].getFormat();

        uvec2 dimensions = (*image)[0].getDimensions();

        GLCheck( glBindTexture(GL_TEXTURE_RECTANGLE, m_texture) );

        GLCheck( glTexImage2D(GL_TEXTURE_RECTANGLE, 
                              0, 
                              GLEnum::getInternalFormat(m_format), 
                              dimensions.x, 
                              dimensions.y, 
                              0, 
                              GLEnum::getExternalFormat(m_format), 
                              GLEnum::getType(m_format), 
                              (*image)[0].getPixels()) );

        GLCheck( glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
    }

} // namespace plt
