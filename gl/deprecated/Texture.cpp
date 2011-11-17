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
#include "Texture.hpp"

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

namespace plt
{
    Texture::Texture
    (
    ) :
    m_texture(0)
    {
        GLCheck( glGenTextures(1, &m_texture) );
    }


    Texture::~Texture
    (
    )
    {
        cleanUp();   
    }


    void Texture::cleanUp
    (
    )
    {
        if( glIsTexture(m_texture) )
            GLCheck( glDeleteTextures(1, &m_texture) );
    }


    GLuint Texture::getGLHandle
    (
    )   
    {
        return m_texture;
    }


    PixelFormat Texture::getPixelFormat
    (
    )   
    {
        return m_format;
    }

    unsigned int Texture::getNbMipLevels(unsigned int width, unsigned int height)
    {
        unsigned int count = 0;

        while ((width > 1) || (height > 1))
        {
            if (width > 1)  width  /= 2;
            if (height > 1) height /= 2;
            ++count;
        }

        return count;
    }


    unsigned int Texture::nearestPlasticOfTwo(unsigned int value)
    {
        unsigned int temp = value;
        unsigned int plasticOfTwo = 0;

        while (temp > 1)
        {
            temp >>= 1;
            ++plasticOfTwo;
        }

        unsigned int retval = 1 << plasticOfTwo;

        return retval == value ? retval : retval << 1;
    }

} // namespace plt
