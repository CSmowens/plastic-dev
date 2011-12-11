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
    template<typename T, typename U>
    inline Geometry::Geometry
    (
        PrimitiveType primType,
        const VertexDeclaration &declaration, 
        const std::vector<T> &vertexData, 
        const std::vector<U> &indexData
    ) :
    m_primitiveType(primType),
    m_declaration(declaration)
    {
        if(m_declaration.empty())
            throw std::runtime_error("Declaration is empty");

        if(sizeof(T) != m_declaration.size())
            throw std::runtime_error("Size declaration and sizeof(T) aren't compatible, may be check the padding");

        m_vertexCount = vertexData.size();
        m_indexCount = indexData.size();

        std::size_t sizeVertex = vertexData.size()*sizeof(T);
        std::size_t sizeIndex = indexData.size()*sizeof(U);

        m_vertexData.resize(sizeVertex);
        m_indexData.resize(sizeIndex);

        std::memcpy(&m_vertexData[0], &vertexData[0], sizeVertex);
        std::memcpy(&m_indexData[0], &indexData[0], sizeIndex);

        m_indexType = computeIndexType(sizeof(U));

        checkStaticGeometryValidity();
    }


    template<typename U>
    inline Geometry::Geometry
    (
        PrimitiveType primType,
        const VertexDeclaration &declaration, 
        unsigned int vertexCount, 
        const std::vector<ubyte> &vertexData, 
        const std::vector<U> &indexData
    ) :
    m_primitiveType(primType),
    m_declaration(declaration)
    {
        if(m_declaration.empty())
            throw std::runtime_error("Declaration is empty");

        if(vertexCount*m_declaration.size() != vertexData.size()*sizeof(ubyte))
            throw std::runtime_error("Vertex data are imcompatible with vertexCount and VertexDeclaration");


        m_vertexData = vertexData;
        m_vertexCount = vertexCount;


        std::size_t sizeIndex = indexData.size()*sizeof(U);

        m_indexData.resize(sizeIndex);
        std::memcpy(&m_indexData[0], &indexData[0], sizeIndex);

        m_indexCount = indexData.size();
        m_indexType = computeIndexType(sizeof(U));


        checkStaticGeometryValidity();
    }

} // namespace plt
