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
#include "VertexElement.hpp"

#include <stdexcept>

namespace plt
{
    const std::vector<std::size_t> VertexElement::m_sizeFromType =
    {
        4,
        8,
        12,
        16
    };


    const std::vector<std::size_t> VertexElement::m_countFromType =
    {
        1,
        2,
        3,
        4
    };


    const std::vector<std::string> VertexElement::m_nameFromSemantic = 
    {
        "VertexPosition",
        "VertexNormal",
        "VertexTangent",
        "VertexBinormal",
        "VertexTexCoord0",
        "VertexColor",
        "VertexWeight", 
        "VertexMatrixIndex" 
    };


    const std::map<std::string, VertexElementSemantic> VertexElement::m_semanticFromName = 
    {
        std::make_pair("VertexPosition", VertexElementSemantic::Position),
        std::make_pair("VertexNormal", VertexElementSemantic::Normal),
        std::make_pair("VertexTangent", VertexElementSemantic::Tangent),
        std::make_pair("VertexBinormal", VertexElementSemantic::BiNormal),
        std::make_pair("VertexTexCoord0", VertexElementSemantic::TexCoord0),
        std::make_pair("VertexColor", VertexElementSemantic::Color),
        std::make_pair("VertexWeight", VertexElementSemantic::Weight),
        std::make_pair("VertexMatrixIndex", VertexElementSemantic::MatrixIndex)
    };











    VertexElementType VertexElement::toType
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


    VertexElementSemantic VertexElement::toSemantic
    (
        const std::string &str
    )
    {
        auto it = m_semanticFromName.find(str);

        if (it != m_semanticFromName.end())
            return it->second;

        else
            throw std::runtime_error("Unknown semantic");
    }


    std::string VertexElement::toString
    (
        VertexElementSemantic semantic
    )
    {
        return m_nameFromSemantic[ static_cast<std::size_t>(semantic) ];
    }


    std::size_t VertexElement::size
    (
        VertexElementType type
    )
    {
        return m_sizeFromType[ static_cast<std::size_t>(type) ];
    }


    std::size_t VertexElement::count
    (
        VertexElementType type
    )
    {
        return m_countFromType[ static_cast<std::size_t>(type) ];
    }









    VertexElement::VertexElement
    (
        VertexElementSemantic semantic, 
        VertexElementType type,
        std::size_t offset
    ) :
    m_semantic(semantic),
    m_type(type),
    m_offset(offset)
    {

    }


    VertexElementSemantic VertexElement::getSemantic
    (
    ) const
    {
        return m_semantic;
    }


    VertexElementType VertexElement::getType
    (
    ) const
    {
        return m_type;
    }


    std::size_t VertexElement::getOffset
    (
    ) const
    {
        return m_offset;
    }





    bool operator==
    (
        const VertexElement &u, 
        const VertexElement &v
    )
    {
        return u.getSemantic() == v.getSemantic() && 
               u.getType() == v.getType() && 
               u.getOffset() == v.getOffset();
    }


    bool operator!=
    (
        const VertexElement &u, 
        const VertexElement &v
    )
    {
        return !(u == v);
    }

} // namespace plt
