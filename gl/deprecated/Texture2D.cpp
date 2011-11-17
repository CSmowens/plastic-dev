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
#include "Texture2D.hpp"

#include "GLEnum.hpp"

#include <Plastic/Core/Vector2.hpp>

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

namespace plt
{

    Texture2D::Texture2D
    (
        std::shared_ptr<Image> &image,
        TextureMipmapFlag mipmap
    )
    {
        try
        {
            if(mipmap == TMF_FROMIMAGE || mipmap == TMF_GENHARDWARE)
                m_hasMipmaps = true;

            initialize(image, mipmap);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during Texture2D initialisation");
        }  
    }


    Texture2D::~Texture2D
    (
    )
    {
    
    }


    void Texture2D::bind
    (
    )
    {
        GLCheck( glBindTexture(GL_TEXTURE_2D, m_texture) );
    }


    GLenum Texture2D::getGLSLType
    (
    )
    {
        return GLEnum::getGLSLTypeTexture2D(m_format);
    }


    void Texture2D::initialize
    (
        std::shared_ptr<Image> &image,
        TextureMipmapFlag mipmap
    )
    {
        // L'assertion pourra être enlever si on garde le fait qu'une image à toujours au moins un niveau
        if( image->levels() < 1)
            throw std::runtime_error("Image haven't got image level");

        PixelFormat m_format = (*image)[0].getFormat();

        uvec2 dimensions = (*image)[0].getDimensions();

        if( dimensions.x != nearestPlasticOfTwo(dimensions.x) || dimensions.y != nearestPlasticOfTwo(dimensions.y) )
            throw std::runtime_error("Image haven't got dimensions in plastic of two, try TextureRect instead");


        GLCheck( glBindTexture(GL_TEXTURE_2D, m_texture) );
	    GLCheck( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0) );   

        GLCheck( glTexImage2D(GL_TEXTURE_2D, 
                              0, 
                              GLEnum::getInternalFormat(m_format), 
                              dimensions.x, 
                              dimensions.y, 
                              0, 
                              GLEnum::getExternalFormat(m_format), 
                              GLEnum::getType(m_format), 
                              (*image)[0].getPixels()) );

        if(!m_hasMipmaps)
            GLCheck( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0) );

        else
        {
            if(mipmap == TMF_FROMIMAGE)
            {
                unsigned int nbMipmaps = getNbMipLevels(dimensions.x, dimensions.y);

                if(image->levels()-1 != nbMipmaps)
                    throw std::runtime_error("The image doesn't contains all mipmap to 1x1");

                for(std::size_t i(1); i<image->levels(); ++i)
                {
                    if( (*image)[i].getFormat() != m_format)
                        throw std::runtime_error("All mipmaps haven't the same format than base level image");

                    uvec2 dim = (*image)[i-1].getDimensions() / 2;

                    if(dim.x < 1) dim.x = 1;
                    if(dim.y < 1) dim.y = 1;

                    if(dim != (*image)[i].getDimensions())
                        throw std::runtime_error("A mipmap hasn't got good dimensions");  
                }

                for(std::size_t i(1); i<image->levels(); ++i)
                {
                    uvec2 dim = (*image)[i].getDimensions();

                    GLCheck( glTexImage2D(GL_TEXTURE_2D, 
                                          i, 
                                          GLEnum::getInternalFormat(m_format), 
                                          dim.x, 
                                          dim.y, 
                                          0, 
                                          GLEnum::getExternalFormat(m_format), 
                                          GLEnum::getType(m_format), 
                                          (*image)[i].getPixels()) );
                }
            }

            else if(mipmap == TMF_GENHARDWARE)
            {
                if( isCompressedFormat(m_format) )
                    throw std::runtime_error("Hardware mipmap generation is impossible on compressed format");

                GLCheck( glGenerateMipmap(GL_TEXTURE_2D) );
            }

            GLCheck( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) );
        }

        GLCheck( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
    }


    bool Texture2D::hasMipmaps
    (   
    )
    {
        return m_hasMipmaps;
    }

} // namespace plt
