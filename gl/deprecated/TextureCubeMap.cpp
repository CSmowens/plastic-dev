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
#include "TextureCubeMap.hpp"

#include "GLEnum.hpp"

#include <Plastic/Core/Vector2.hpp>

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

namespace plt
{

    TextureCubeMap::TextureCubeMap
    (
        std::array<std::shared_ptr<Image>, 6> &images,
        TextureMipmapFlag mipmap
    )
    {
        try
        {
            if(mipmap == TMF_FROMIMAGE || mipmap == TMF_GENHARDWARE)
                m_hasMipmaps = true;

            initialize(images, mipmap);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during TextureCubeMap initialisation");
        }  
    }


    TextureCubeMap::~TextureCubeMap
    (
    )
    {
    
    }


    void TextureCubeMap::bind
    (
    )
    {
        GLCheck( glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture) );
    }


    GLenum TextureCubeMap::getGLSLType
    (
    )
    {
        return GLEnum::getGLSLTypeTexture2D(m_format);
    }


    void TextureCubeMap::initialize
    (
        std::array<std::shared_ptr<Image>, 6> &images,
        TextureMipmapFlag mipmap
    )
    {
        // L'assertion pourra être enlever si on garde le fait qu'une image à toujours au moins un niveau
        for(auto i(0); i<6; ++i)
        {
            if( images[i]->levels() < 1)
                throw std::runtime_error("An image haven't got image level");
        }

        PixelFormat m_format = (*images[0])[0].getFormat();

        uvec2 baseDimensions = (*images[0])[0].getDimensions();
        baseDimensions.x = nearestPlasticOfTwo(baseDimensions.x);
        baseDimensions.y = nearestPlasticOfTwo(baseDimensions.y);

        for(auto i(0); i<6; ++i)
        {
            if( (*images[i])[0].getDimensions() != baseDimensions)
                throw std::runtime_error("All image level[0] haven't got dimensions in plastic of two");

            if( (*images[i])[0].getFormat() != m_format)
                throw std::runtime_error("All image level[0] haven't got the same format ");
        }


        GLCheck( glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture) );
	    GLCheck( glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0) ); 

        for(auto i(0); i<6; ++i)
        {
            GLCheck( glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                                  0, 
                                  GLEnum::getInternalFormat(m_format), 
                                  baseDimensions.x, 
                                  baseDimensions.y, 
                                  0, 
                                  GLEnum::getExternalFormat(m_format), 
                                  GLEnum::getType(m_format), 
                                  (*images[i])[0].getPixels()) );
        }

        if(!m_hasMipmaps)
            GLCheck( glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0) );

        else
        {
            if(mipmap == TMF_FROMIMAGE)
            {
                throw std::runtime_error("Load mipmap with CPU is not allowed yet");
                //unsigned int nbMipmaps = getNbMipLevels(dimensions.x, dimensions.y);

                // Verifier que toutes ont le même nombre de niveau pour chaque image
                // Verifier que toutes ont les mêmes dimensions pour chaques niveaux
                // Verifier que toutes ont le même format pour chaques niveaux
            }

            else if(mipmap == TMF_GENHARDWARE)
            {
                if( isCompressedFormat(m_format) )
                    throw std::runtime_error("Hardware mipmap generation is impossible on compressed format");

                GLCheck( glGenerateMipmap(GL_TEXTURE_CUBE_MAP) );
            }

            GLCheck( glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) );
        }

        GLCheck( glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
    }

} // namespace plt
