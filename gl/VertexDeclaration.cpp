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
#include "VertexDeclaration.hpp"

#include <Plastic/Core/Assert.hpp>

#include <stdexcept>

namespace plt
{
    VertexDeclaration::VertexDeclaration
    (
    ) :
    m_size(0)
    {

    }


    void VertexDeclaration::add
    (
        VertexElementSemantic semantic, 
        VertexElementType type
    )
    {
        if( hasSemantic(semantic) )
            throw std::runtime_error("The vertex declaration have already the element with semantic \"" + VertexElementSemanticInfos::getInfos(semantic).name() + '"');

        m_declaration.push_back( VertexElement(semantic, type, m_size) );

        m_size += VertexElementTypeInfos::getInfos(type).size();
    }


    const VertexElement& VertexDeclaration::operator[]
    (
        std::size_t i
    ) const
    {
        PLASTIC_ASSERT(i < size());

        return m_declaration[i];
    }


    std::size_t VertexDeclaration::count
    (
    ) const
    {
        return m_declaration.size();
    }


    std::size_t VertexDeclaration::size
    (
    ) const
    {
        return m_size;
    }


    bool VertexDeclaration::empty
    (
    ) const
    {
        return m_declaration.empty();
    }


    bool VertexDeclaration::hasSemantic
    (
        VertexElementSemantic semantic
    ) const
    {
        for(auto it = m_declaration.begin(); it != m_declaration.end(); ++it)
        {
            if( it->getSemantic() == semantic )
                return true;
        }

        return false;
    }









    bool areCompatible
    (
        const VertexDeclaration &u, 
        const VertexDeclaration &v
    )
    {
        if( u.count() != v.count() )
            return false;

        for(std::size_t i(0); i<u.count(); ++i)
        {
            bool have = false;

            for(std::size_t j(0); j<v.count(); ++j)
            {
                if(u[i].getSemantic() == v[j].getSemantic() && u[i].getType() == v[j].getType() )
                    have = true;

                if(have)
                    break;
            }

            if(!have)
                return false;
        }

        return true;
    }


    bool operator==
    (
        const VertexDeclaration &u, 
        const VertexDeclaration &v
    )
    {
        if( u.count() != v.count() )
            return false;

        for(std::size_t i(0); i<u.count(); ++i)
        {
            if( u[i] != v[i] )
                return false;
        }

        return true;
    }


    bool operator!=
    (
        const VertexDeclaration &u, 
        const VertexDeclaration &v
    )
    {
        return !(u == v);
    }

} // namespace plt
