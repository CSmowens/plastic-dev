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
#include "VertexElementSemantic.hpp"

#include <stdexcept>

namespace plt
{
	std::map<VertexElementSemantic, VertexElementSemanticInfos> VertexElementSemanticInfos::m_semanticsInfos = 
    {
        std::make_pair(VertexElementSemantic::Position,    VertexElementSemanticInfos("VertexPosition")),
        std::make_pair(VertexElementSemantic::Normal,      VertexElementSemanticInfos("VertexNormal")),
        std::make_pair(VertexElementSemantic::Tangent,     VertexElementSemanticInfos("VertexTangent")),
        std::make_pair(VertexElementSemantic::BiNormal,    VertexElementSemanticInfos("VertexBiNormal")),
        std::make_pair(VertexElementSemantic::TexCoord0,   VertexElementSemanticInfos("VertexTexCoord0")),
        std::make_pair(VertexElementSemantic::Color,       VertexElementSemanticInfos("VertexColor")),
        std::make_pair(VertexElementSemantic::Weight,      VertexElementSemanticInfos("VertexWeight")),
        std::make_pair(VertexElementSemantic::MatrixIndex, VertexElementSemanticInfos("VertexMatrixIndex")),
    };



    VertexElementSemanticInfos& VertexElementSemanticInfos::getInfos
    (
        VertexElementSemantic semantic
    )
    {
        auto it = m_semanticsInfos.find(semantic);

        if(it == m_semanticsInfos.end())
            throw std::runtime_error("Unregistered VertexElementSemantic");

        else
            return it->second;
    }




    VertexElementSemantic VertexElementSemanticInfos::retrieveSemanticFromName
    (
        const std::string &name
    )
    {
        for(auto it = m_semanticsInfos.begin(); it != m_semanticsInfos.end(); ++it)
        {
            if (it->second.name() == name)
                return it->first;
        }


        throw std::runtime_error("Unknown semantic name");
    }
















    VertexElementSemanticInfos::VertexElementSemanticInfos
    (
        const std::string name
    ) :
    m_name(name)
    {

    }

    const std::string& VertexElementSemanticInfos::name
    (
    ) const
    {
        return m_name;
    }


} // namespace plt
