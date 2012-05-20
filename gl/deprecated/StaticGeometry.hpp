////////////////////////////////////////////////////////////
// Copyright (c) 2011 - 2012 Hiairrassary Victor
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


#ifndef PLASTIC_STATICGEOMETRY_HPP
#define PLASTIC_STATICGEOMETRY_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Geometry.hpp"
#include "VertexDeclaration.hpp"

#include <Plastic/Core/Maths.hpp>
#include <Plastic/Core/Types.hpp>
#include <Plastic/Core/Vector2.hpp>
#include <Plastic/Core/Vector3.hpp>

#include <algorithm>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace plt
{

    ////////////////////////////////////////////////////////////
    /// 
    ////////////////////////////////////////////////////////////
    template<typename U>
    class StaticGeometry : public Geometry
    {  
    public:
        template<typename T>
        StaticGeometry(PrimitiveType primType, const VertexDeclaration &declaration, const std::vector<T> &vertexData, const std::vector<U> &indexData);

        StaticGeometry(PrimitiveType primType, const VertexDeclaration &declaration, const std::vector<ubyte> &vertexData, unsigned int vertexCount, const std::vector<U> &indexData);
        
        const void* getVertexRawData() const;

        const void* getIndexRawData() const;

        void checkValidity() const;

        static StaticGeometry createSphere(float radius, unsigned int segmentsCount, unsigned int ringsCount, bool normals, bool texCoord);

    private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        std::vector<ubyte> m_vertexData;
 
        std::vector<U> m_indexData; 
    };


} // namespace plt


#include "StaticGeometry.inl"


#endif // PLASTIC_STATICGEOMETRY_HPP




////////////////////////////////////////////////////////////
/// \class plt::StaticGeometry
///
/// \todo Voir pour le constructeur par défault
/// \todo Implementer la verification
/// \todo Factoriser les constructeurs
/// \todo Faire toutes les verifications avant les copies de données dans les constructeurs
/// \todo Pour les fonctions createSphere... prendre en compte espace tangent
/// \todo Pour les fonctions createSphere... voir pour le backface culling
///
////////////////////////////////////////////////////////////

