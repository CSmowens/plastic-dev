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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////


#ifndef PLASTIC_TEXTURE_HPP
#define PLASTIC_TEXTURE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Core/Image.hpp>
#include <Plastic/Core/PixelFormat.hpp>

#include <Plastic/OpenGL.hpp>

namespace plt
{

	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    enum TextureMipmapFlag
    {
        TMF_NOMIPMAP,
        TMF_FROMIMAGE,
        TMF_GENHARDWARE
    };


	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class Texture
    {

    public:
        Texture();

        virtual ~Texture();

        virtual void bind() = 0;

        virtual GLenum getGLSLType() = 0;

        GLuint getGLHandle();

        PixelFormat getPixelFormat();

        ////////////////////////////////////////////////////////////////
        /// Compute max number of mipmap level
        ///
        /// \param width  : Texture width
        /// \param height : Texture height
        ///
        /// \return Max number of mipmap level
        ///
        ////////////////////////////////////////////////////////////
        static unsigned int getNbMipLevels(unsigned int width, unsigned int height);

        ////////////////////////////////////////////////////////////
        /// Return next puissance of two of value
        ///
        /// \param value : Test number
        ///
        /// \return Return next puissance of two of value
        ///
        ////////////////////////////////////////////////////////////
        static unsigned int nearestPlasticOfTwo(unsigned int value);

    protected:
        void cleanUp();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
        PixelFormat m_format;
        GLuint m_texture; 
    };

} // namespace plt


#endif // PLASTIC_TEXTURE_HPP




////////////////////////////////////////////////////////////
/// \class plt::Texture
///
/// \todo Etre exception safe
/// \todo Sortir le #define PLASTIC_DEBUG 1
/// \todo Faire de nearestPlasticOfTwo une fonction endianess safe
/// \todo Penser à ajouter les format PXF_DEPTH* et PXF_DXT*. Ne pas oublier de changer GLenum ensuite
/// \todo Voir si unbind les textures apres chargement
/// \todo Factoriser en une unique classa
///
////////////////////////////////////////////////////////////
