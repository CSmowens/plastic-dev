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
#include "VertexElementType.hpp"

#include <stdexcept>


namespace plt
{
	std::map<VertexElementType, VertexElementTypeInfos> VertexElementTypeInfos::m_typesInfos = 
    {
        std::make_pair(VertexElementType::Float1,    VertexElementTypeInfos(1, 4)),
        std::make_pair(VertexElementType::Float2,    VertexElementTypeInfos(2, 8)),
        std::make_pair(VertexElementType::Float3,    VertexElementTypeInfos(3, 12)),
        std::make_pair(VertexElementType::Float4,    VertexElementTypeInfos(4, 16)),
    };



    VertexElementTypeInfos& VertexElementTypeInfos::getInfos
    (
        VertexElementType type
    )
    {
        auto it = m_typesInfos.find(type);

        if(it == m_typesInfos.end())
            throw std::runtime_error("Unregistered VertexElementType");

        else
            return it->second;
    }




    VertexElementType VertexElementTypeInfos::retrieveTypeFromGLType
    (
        GLenum type
    )
    {
        switch(type)
        {
            case GL_FLOAT:        return VertexElementType::Float1;   break;
            case GL_FLOAT_VEC2:   return VertexElementType::Float2;   break;
            case GL_FLOAT_VEC3:   return VertexElementType::Float3;   break;
            case GL_FLOAT_VEC4:   return VertexElementType::Float4;   break;

            default: throw std::runtime_error("Unknown OpenGL type"); break;
        }
    }
















    VertexElementTypeInfos::VertexElementTypeInfos
    (
        unsigned int count,
        unsigned int size
    ) :
    m_count(count),
    m_size(size)
    {

    }


    unsigned int VertexElementTypeInfos::count
    (
    ) const
    {
        return m_count;
    }


    unsigned int VertexElementTypeInfos::size
    (
    ) const
    {
        return m_size;
    }


} // namespace plt
