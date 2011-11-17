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


#ifndef PLASTIC_TEXTURE2DARRAY_HPP
#define PLASTIC_TEXTURE2DARRAY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Texture.hpp"

#include <memory>
#include <vector>

namespace plt
{
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class Texture2DArray : public Texture
    {

    public:
        Texture2DArray(std::vector< std::shared_ptr<Image> > &images, TextureMipmapFlag mipmap);

        virtual ~Texture2DArray();

        virtual void bind();

        virtual GLenum getGLSLType();

        bool hasMipmaps();

    protected:
        void initialize(std::vector< std::shared_ptr<Image> > &images, TextureMipmapFlag mipmap);

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
        bool m_hasMipmaps;
    };

} // namespace plt


#endif // PLASTIC_TEXTURE2DARRAY_HPP




////////////////////////////////////////////////////////////
/// \class plt::Texture2DArray
///
/// \todo Etre exception safe
/// \todo Renvoyer aussi l'erreur OpenGL
/// \todo Sortir le #define PLASTIC_DEBUG 1
/// \todo Voir la possibilité de créer une texture vide, sans image (constructeur par défaut)
///
////////////////////////////////////////////////////////////
