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


namespace plt
{
    template<typename U>
    inline StaticGeometry<U> StaticGeometry<U>::createSphere
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


        VertexDeclaration declaration;
        declaration.add(VES_POSITION, VET_FLOAT3);

        if(normals)
            declaration.add(VES_NORMAL, VET_FLOAT3);

        if(texCoords)
            declaration.add(VES_TEXCOORD0, VET_FLOAT2);


        unsigned int vertexCount = (ringsCount + 1)*(segmentsCount+1);

        //unsigned int indexCount = 6*ringsCount*(segmentsCount + 1);


        std::vector<ubyte> mesh(vertexCount * declaration.size());

        std::vector<U> index;

        std::size_t offset = 0;


        float deltaRingAngle = (Maths<float>::PI / static_cast<float>(ringsCount));
        float deltaSegAngle = (Maths<float>::TWO_PI / static_cast<float>(segmentsCount));

        U currentVerticeIndex = 0;

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

        return StaticGeometry<U>(PT_TRIANGLES, declaration, mesh, vertexCount, index);
    }













    template<typename U>
    template<typename T>
    inline StaticGeometry<U>::StaticGeometry
    (
        PrimitiveType primType,
        const VertexDeclaration &declaration, 
        const std::vector<T> &vertexData, 
        const std::vector<U> &indexData
    ) :
    Geometry(primType, declaration),
    m_indexData(indexData)
    {
        if(m_declaration.empty())
            throw std::runtime_error("Declaration is empty");

        if(sizeof(T) != m_declaration.size())
            throw std::runtime_error("Size declaration and sizeof(T) aren't compatible, may be check the padding");

        m_vertexCount = vertexData.size();
        m_indexCount = indexData.size();

        std::size_t size = vertexData.size()*sizeof(T);

        m_vertexData.resize(size);

        std::memcpy(&m_vertexData[0], &vertexData[0], size);

        checkValidity();
    }


    template<typename U>
    inline StaticGeometry<U>::StaticGeometry
    (
        PrimitiveType primType,
        const VertexDeclaration &declaration, 
        const std::vector<ubyte> &vertexData, 
        unsigned int vertexCount, 
        const std::vector<U> &indexData
    ) :
    Geometry(primType, declaration),
    m_vertexData(vertexData),
    m_indexData(indexData)
    {
        if(m_declaration.empty())
            throw std::runtime_error("Declaration is empty");

        if(vertexCount*m_declaration.size() != m_vertexData.size())
            throw std::runtime_error("Data are imcompatible with vertexCount and VertexDeclaration");

        m_vertexCount = vertexCount;
        m_indexCount = indexData.size();

        checkValidity();
    }


    template<typename U>
    inline const void* StaticGeometry<U>::getVertexRawData
    (
    
    ) const
    {
        return &m_vertexData[0];
    }


    template<typename U>
    inline const void* StaticGeometry<U>::getIndexRawData
    (
    
    ) const
    {
        return &m_indexData[0];
    }


    template<typename U>
    inline void StaticGeometry<U>::checkValidity
    (
    
    ) const
    {
        auto maxIndex = std::max_element(m_indexData.begin(), m_indexData.end());

        if((*maxIndex) >= m_vertexCount)
            throw std::runtime_error("The max index is greater than or equal vertex count");

        if(getIndexCount() % vertexPerPrimitiveCount(m_primitiveType) != 0)
            throw std::runtime_error("Index count doesn't correspond");
    }

} // namespace plt
