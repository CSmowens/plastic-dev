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
#include "SubGeometry.hpp"

#include "IndexBufferFormatted.hpp"
#include "VertexBufferFormatted.hpp"
#include "VertexBufferRaw.hpp"

#include "Plastic/Core.hpp"

#include <cstring>

namespace plt
{
    std::shared_ptr<SubGeometry> SubGeometry::createRightHandCoordinateSystem
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

        return std::make_shared<SubGeometry>(PrimitiveType::Lines, 
                                             std::make_shared<VertexBufferFormatted<VertexCoordinateSystem>>(declaration, std::move(vertex)),
                                             std::make_shared<IndexBufferFormatted<unsigned char>>(std::move(index)) );
    }


    std::shared_ptr<SubGeometry> createFullScreenQuad
    (
    )
    {
        struct VertexPosAndTexCoord
        {
            float x,y,u,v;
        };


        VertexDeclaration declaration;
        declaration.add(VertexElementSemantic::Position, VertexElementType::Float2);
        declaration.add(VertexElementSemantic::TexCoord0, VertexElementType::Float2);

        std::vector<VertexPosAndTexCoord> vertex;
        vertex.push_back( VertexPosAndTexCoord{0,0,    0,0} ); // Bottom left of screen
        vertex.push_back( VertexPosAndTexCoord{0,1,    0,1} ); // Top left of screen
        vertex.push_back( VertexPosAndTexCoord{1,1,    1,1} ); // Top right of screen
        vertex.push_back( VertexPosAndTexCoord{1,0,    1,0} ); // Bottom right of screen
        std::vector<unsigned char> index = {0,1,2,3,2,0};

        return std::make_shared<SubGeometry>(PrimitiveType::Triangles, 
                                             std::make_shared<VertexBufferFormatted<VertexPosAndTexCoord>>(declaration, std::move(vertex)),
                                             std::make_shared<IndexBufferFormatted<unsigned char>>(std::move(index)) );
    }


    std::shared_ptr<SubGeometry> SubGeometry::createFrustum
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


        std::vector<unsigned char> index = {0,1,1,3,3,2,2,0,
                                            4,5,5,7,7,6,6,4,
                                            1,5,4,0,2,6,7,3 };

        return std::make_shared<SubGeometry>(PrimitiveType::Lines, 
                                             std::make_shared<VertexBufferFormatted<vec3>>(declaration, std::move(vertex)),
                                             std::make_shared<IndexBufferFormatted<unsigned char>>(std::move(index)) );
    }


    std::shared_ptr<SubGeometry> SubGeometry::createBox
    (
        float width, 
        float height, 
        float depth,
        bool normals,
        bool texCoords
    )
    {

        struct VertexPosUV
        {
            float x,y,z,u,v;
        };

        VertexDeclaration declaration;
        declaration.add(VertexElementSemantic::Position, VertexElementType::Float3);
        declaration.add(VertexElementSemantic::TexCoord0, VertexElementType::Float2);

        std::vector<VertexPosUV> vertsBox;
        vertsBox.push_back( VertexPosUV{-0.5, 0.5, 0.5,   0,0}  );
        vertsBox.push_back( VertexPosUV{-0.5, 0.5, -0.5,   0,1}  );
        vertsBox.push_back( VertexPosUV{0.5, 0.5, -0.5,   1,1}  );
        vertsBox.push_back( VertexPosUV{0.5, 0.5, 0.5,   1,0}  );

        vertsBox.push_back( VertexPosUV{-0.5, -0.5, 0.5,   1,1}  );
        vertsBox.push_back( VertexPosUV{-0.5, -0.5, -0.5,   1,0}  );
        vertsBox.push_back( VertexPosUV{0.5, -0.5, -0.5,   0,0}  );
        vertsBox.push_back( VertexPosUV{0.5, -0.5, 0.5,   0,1}  );

        std::vector<unsigned char> indexBox = {0,1,2,    2,3,0,
                                               1,5,2,    2,5,6,
                                               0,1,4,    1,4,5,
                                               2,3,7,    2,7,6,
                                               4,5,6,    4,6,7,
                                               0,4,3,    3,4,7};


        return std::make_shared<SubGeometry>(PrimitiveType::Triangles, 
                                             std::make_shared<VertexBufferFormatted<VertexPosUV>>(declaration, std::move(vertsBox)),
                                             std::make_shared<IndexBufferFormatted<unsigned char>>(std::move(indexBox)) );
    }


    std::shared_ptr<SubGeometry> SubGeometry::createSphere
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

        return std::make_shared<SubGeometry>(PrimitiveType::Triangles, 
                                             std::make_shared<VertexBufferRaw>(declaration, vertexCount, std::move(mesh)),
                                             std::make_shared<IndexBufferFormatted<unsigned int>>(std::move(index)) );
    }















    SubGeometry::SubGeometry
    (
        PrimitiveType type, 
        const std::shared_ptr<VertexBuffer> &vertexBuffer, 
        const std::shared_ptr<IndexBuffer> &indexBuffer
    ) :
    m_primitiveType(type),
    m_vertexBuffer(vertexBuffer),
    m_indexBuffer(indexBuffer)
    {

    }


    const std::shared_ptr<VertexBuffer>& SubGeometry::getVertexBuffer
    (
    ) const
    {
        return m_vertexBuffer;
    }


    const std::shared_ptr<IndexBuffer>& SubGeometry::getIndexBuffer
    (
    ) const
    {
        return m_indexBuffer;
    }


    PrimitiveType SubGeometry::getPrimitiveType
    (
    ) const
    {
        return m_primitiveType;
    }


} // namespace plt
