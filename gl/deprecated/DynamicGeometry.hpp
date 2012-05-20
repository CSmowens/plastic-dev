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


#ifndef PLASTIC_DYNAMICGEOMETRY_HPP
#define PLASTIC_DYNAMICGEOMETRY_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Core/Vector3.hpp>
#include <Plastic/Core/Vector2.hpp>

#include "Geometry.hpp"

#include "Skeleton.hpp"
#include "VertexDeclaration.hpp"

#include <vector>
#include <stdexcept>


namespace plt
{

    ////////////////////////////////////////////////////////////
    /// 
    ////////////////////////////////////////////////////////////
    template<typename T, typename U>
    class DynamicGeometry : public Geometry
    {  
    public:
        struct Vertex
        {
            tvec2<T> texCoord;

            std::size_t start; // Start weight
            unsigned int count; // Weight count
        };


        struct Triangle
        {
            tvec3<U> index;
        };


        struct Weight
        {
            std::size_t joint;
            T bias;

            tvec3<T> pos;
        };


    public:
        DynamicGeometry() = default;

        DynamicGeometry(const Skeleton<T> &baseSkeleton, std::vector< Vertex > vertices, std::vector< Triangle > triangles, std::vector< Weight > weights);

        const VertexDeclaration& getVertexDeclaration() const;
        

    private:
        void checkValidity() const;

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        Skeleton<T> m_baseSkeleton;

        std::vector< Vertex > m_vertices;
        std::vector< Triangle > m_triangles;
        std::vector< Weight > m_weights;
    };


} // namespace plt


#include "DynamicGeometry.inl"


#endif // PLASTIC_DYNAMICGEOMETRY_HPP




////////////////////////////////////////////////////////////
/// \class plt::Dynamic$Geometry
///
/// \todo Faire en sorte que les templates soient float ou double pour T, et uint16 ou uint32 pour U.
/// \todo Possibilité d'avoir autre chose que des positions
/// \todo Fixer la VertexDeclaration
/// \todo Faire les verifications avant les copies de données
/// \todo Voir pour le type de primitive 
///
////////////////////////////////////////////////////////////

