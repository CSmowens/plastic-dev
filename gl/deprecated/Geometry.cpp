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


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Geometry.hpp"

#include <Plastic/Core/Assert.hpp>

#include <limits>
#include <stdexcept>

namespace plt
{
    std::shared_ptr<Geometry> Geometry::createRightHandCoordinateSystem
    (
    )
    {
        struct VertexCoordinateSystem
        {
            float x,y,z,r,g,b;
        };


        VertexDeclaration declaration;
        declaration.add(VertexElementSemantic::Position, VertexElementType::Float3);
        declaration.add(VertexElementSemantic::Color, VertexElementType::Float3);

        std::vector<VertexCoordinateSystem> vertex;
        vertex.push_back( VertexCoordinateSystem{0,0,0,    0,0,1} );
        vertex.push_back( VertexCoordinateSystem{1,0,0,    0,0,1} );
        vertex.push_back( VertexCoordinateSystem{0,0,0,    0,1,0} );
        vertex.push_back( VertexCoordinateSystem{0,1,0,    0,1,0} );
        vertex.push_back( VertexCoordinateSystem{0,0,0,    1,0,0} );
        vertex.push_back( VertexCoordinateSystem{0,0,1,    1,0,0} );
        std::vector<unsigned char> index = {0,1,2,3,4,5};

        return std::make_shared<Geometry>(PrimitiveType::Lines, declaration, vertex, index);
    }


    std::shared_ptr<Geometry> Geometry::createFrustum
    (
        float fovy, 
        float ratio, 
        float near, 
        float far
    )
    {
	    float thetaY = radians(fovy * 0.5f);
	    float tanThetaY = tan(thetaY);
	    float tanThetaX = tanThetaY * ratio;


	    float half_w = tanThetaX * near;
	    float half_h = tanThetaY * near;

	    float vpLeft   = - half_w;
	    float vpRight  = + half_w;
	    float vpBottom = - half_h;
	    float vpTop    = + half_h;


        float radio = far / near;
        float farLeft = vpLeft * radio;
        float farRight = vpRight * radio;
        float farBottom = vpBottom * radio;
        float farTop = vpTop * radio;





        VertexDeclaration declaration;
        declaration.add(VertexElementSemantic::Position, VertexElementType::Float3);

        std::vector<vec3> vertex;
        vertex.push_back( vec3(vpLeft, vpTop, -near) );       // Near top left
        vertex.push_back( vec3(vpRight, vpTop, -near) );      // Near top right
        vertex.push_back( vec3(vpLeft, vpBottom, -near) );    // Near bottom left
        vertex.push_back( vec3(vpRight, vpBottom, -near) );   // Near bottom right

        vertex.push_back( vec3(farLeft, farTop, -far) );      // Far top left
        vertex.push_back( vec3(farRight, farTop, -far) );     // Far top right
        vertex.push_back( vec3(farLeft, farBottom, -far) );   // Far bottom left
        vertex.push_back( vec3(farRight, farBottom, -far) );  // Far bottom right

/*
        std::vector<unsigned char> index = {0, 1, 2, 1, 2, 3,   // Near plane
                                            4, 5, 6, 5, 6, 7,   // Far plane
                                            6, 2, 3, 6, 3, 7,   // Bottom plane
                                            4, 0, 5, 5, 0, 1,   // Top plane
                                            4, 0, 6, 6, 0, 2,   // Left plane
                                            5, 7, 1, 5, 1, 3};  // Right plane


        return std::make_shared<Geometry>(PrimitiveType::Triangles, declaration, vertex, index);
*/


        std::vector<unsigned char> index = {0,1,1,3,3,2,2,0,
                                            4,5,5,7,7,6,6,4,
                                            1,5,4,0,2,6,7,3 };

        return std::make_shared<Geometry>(PrimitiveType::Lines, declaration, vertex, index);
    }


    std::shared_ptr<Geometry> Geometry::createSphere
    (
        float radius, 
        unsigned int segmentsCount,
        unsigned int ringsCount, 
        bool normals, 
        bool texCoords
    )
    {
        if(radius<=0 || segmentsCount<3 || ringsCount<3)
            throw std::runtime_error("Error in sphere creation parameters");

        unsigned int vertexCount = (ringsCount + 1)*(segmentsCount+1);

/*
        unsigned int indexCount = 6*ringsCount*(segmentsCount + 1);
        typedef unsigned short IndexType;

        if(indexCount > std::numeric_limits<IndexType>::max())
            throw std::runtime_error("Too much index, try a greater type, change the typedef");
*/


        VertexDeclaration declaration;
        declaration.add(VertexElementSemantic::Position, VertexElementType::Float3);

        if(normals)
            declaration.add(VertexElementSemantic::Normal, VertexElementType::Float3);

        if(texCoords)
            declaration.add(VertexElementSemantic::TexCoord0, VertexElementType::Float2);


        std::vector<ubyte> mesh(vertexCount * declaration.size());

        std::vector<unsigned int> index;

        std::size_t offset = 0;


        float deltaRingAngle = (Maths<float>::PI / static_cast<float>(ringsCount));
        float deltaSegAngle = (Maths<float>::TWO_PI / static_cast<float>(segmentsCount));

        unsigned int currentVerticeIndex = 0;

        for(unsigned int ring(0); ring <= ringsCount; ++ring) 
        {
            float r0 = radius * plt::sin (static_cast<float>(ring) * deltaRingAngle);
            float y0 = radius * plt::cos (static_cast<float>(ring) * deltaRingAngle);

            for(unsigned int seg(0); seg <= segmentsCount; ++seg) 
            {
                float x0 = r0 * plt::sin(static_cast<float>(seg) * deltaSegAngle);
                float z0 = r0 * plt::cos(static_cast<float>(seg) * deltaSegAngle);

                vec3 P(x0, y0, z0);

                std::memcpy(&mesh[offset], &P[0], 12);
                offset += 12;

                if(normals)
                {
                    vec3 N = normalize(P);

                    std::memcpy(&mesh[offset], &N[0], 12);
                    offset += 12;
                }
                
                if(texCoords)
                {
                    vec2 T;
                    T.s = static_cast<float>(seg) / static_cast<float>(segmentsCount);
                    T.y = static_cast<float>(ring) / static_cast<float>(ringsCount);

                    std::memcpy(&mesh[offset], &T[0], 8);
                    offset += 8;
                }

                if (ring != ringsCount) 
                {
                    // Each vertex (except the last) has six indices pointing to it
                    index.push_back(currentVerticeIndex + segmentsCount + 1);
                    index.push_back(currentVerticeIndex);
                    index.push_back(currentVerticeIndex + segmentsCount);
                    index.push_back(currentVerticeIndex + segmentsCount + 1);
                    index.push_back(currentVerticeIndex + 1);
                    index.push_back(currentVerticeIndex);
                    currentVerticeIndex ++;
                }
            }
        } 

        return std::make_shared<Geometry>(PrimitiveType::Triangles, declaration, vertexCount, mesh, index);
    }


    std::shared_ptr<Geometry> Geometry::createGeometryWithSpaceTangent
    (
        const std::shared_ptr<Geometry> &geom, 
        bool withTangents,
        bool withBiNormals
    )
    {
        // 1. Vérifier que la geometry envoyer est faite de triangles
        // 2. Vérifier que la VertexDeclaration est compatible avec :
                // { VertexPosition, Float3 }
                // { VertexTexCoords, Float2 }
                // { VertexNormal, Float3 }

        // 3. Si y manque juste les normales, voir si on les calcules

        // 3. Recopier la geometry avec en plus la place pour les tangentes et les BiNormals si voulus
        // 4. Calculer l'espace local :)

        return std::make_shared<Geometry>();
    }


    std::shared_ptr<Geometry> Geometry::createGeometryWithNormalsOnly
    (
        const std::shared_ptr<Geometry> &geom,
        bool onlyNormals
    )
    {
        // 1. Vérifier que la geometry envoyer est faite de triangles
        // 2. Vérifier que la VertexDeclaration est compatible avec :
                // { VertexPosition, Float3 }
                // { VertexTexCoords, Float2 }
                // { VertexNormal, Float3 }

                // { VertexTangent, Float3 }   
                // { VertexBiNormal, Float3 }

        // 4. On créer la geometry composé seulement de lignes :)

        return std::make_shared<Geometry>();
    }





















    Geometry::Geometry
    (
    ) :
    m_vertexCount(0),
    m_indexCount(0)
    {

    }


    void Geometry::addSubGeometry
    (
        const std::shared_ptr<Geometry> &sub
    )
    {
        if(!m_geometry.empty())
        {
            if( m_geometry[0]->getVertexDeclaration() != sub->getVertexDeclaration()  ||
                m_geometry[0]->getPrimitiveType() != sub->getPrimitiveType()  ||
                m_geometry[0]->getIndexType() != sub->getIndexType()  ||
                m_geometry[0]->getSizeOfIndexType() != sub->getSizeOfIndexType()  )
                throw std::runtime_error("SubGeometry's attributes don't match");
        }

        m_geometry.push_back(sub);

        m_vertexCount += sub->getVertexCount();
        m_indexCount += sub->getIndexCount();
    }


    const std::shared_ptr<Geometry>& Geometry::operator[]
    (
        std::size_t index
    ) const
    {
        PLASTIC_ASSERT(index < m_geometry.size());

        return m_geometry[index];
    }

    bool Geometry::hasSubGeometry
    (
    ) const
    {
        return !m_geometry.empty(); 
    }


    std::size_t Geometry::subGeometryCount
    (
    ) const
    {
        return m_geometry.size();
    }









    const VertexDeclaration& Geometry::getVertexDeclaration
    (

    ) const
    {
        return m_declaration;
    }


    PrimitiveType Geometry::getPrimitiveType
    (
    ) const
    {
        return m_primitiveType;
    }


    const void* Geometry::getVertexRawData
    (
    
    ) const
    {
        return &m_vertexData[0];
    }


    const void* Geometry::getIndexRawData
    (
    
    ) const
    {
        return &m_indexData[0];
    }


    unsigned int Geometry::getVertexCount
    ( 
  
    ) const
    {
        return m_vertexCount;
    }


    unsigned int Geometry::getIndexCount
    ( 
  
    ) const
    {
        return m_indexCount;
    }


    GLenum Geometry::getIndexType
    (
    ) const
    {
        return m_indexType;
    }


    unsigned int Geometry::getSizeOfIndexType
    (
    ) const
    {
        return m_sizeOfIndexType;
    }


    GLenum Geometry::computeIndexType
    (
        std::size_t size
    )
    {
        GLenum result;

        switch(size)
        {
            case 1:    result = GL_UNSIGNED_BYTE;    break;
            case 2:    result = GL_UNSIGNED_SHORT;   break;
            case 4:    result = GL_UNSIGNED_INT;     break;

            default: 
                throw std::runtime_error("Imcompatible size for index");
                break;
        }
    
        m_sizeOfIndexType = size;

        return result;
    }

    void Geometry::checkStaticGeometryValidity
    (
    ) const
    {
        /*
        auto maxIndex = std::max_element(m_indexData.begin(), m_indexData.end());

        if((*maxIndex) >= m_vertexCount)
            throw std::runtime_error("The max index is greater than or equal vertex count");
        */

        if(m_indexCount % vertexPerPrimitiveCount(m_primitiveType) != 0)
            throw std::runtime_error("Index count doesn't correspond with primitive type");
    }















    unsigned int vertexPerPrimitiveCount
    (
        PrimitiveType primitive
    )
    {
        static unsigned int size[] = {3, 2, 1};

        return size[ static_cast<std::size_t>(primitive) ];
    }

} // namespace plt
