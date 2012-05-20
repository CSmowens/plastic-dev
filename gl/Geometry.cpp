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

#include <stdexcept>

namespace plt
{
    Geometry::Geometry
    (
    ) :
    m_vertexCount(0),
    m_indexCount(0)
    {

    }


    void Geometry::addSubGeometry
    (
        const std::shared_ptr<SubGeometry> &sub
    )
    {
        if(!m_subGeometry.empty())
        {
            if( m_subGeometry[0]->getVertexBuffer()->getVertexDeclaration() != sub->getVertexBuffer()->getVertexDeclaration() ||
                m_subGeometry[0]->getIndexBuffer()->getIndexSize() != sub->getIndexBuffer()->getIndexSize() ||
                m_subGeometry[0]->getPrimitiveType() != sub->getPrimitiveType() )

                throw std::runtime_error("SubGeometry's attributes don't match");
        }

        m_subGeometry.push_back(sub);

        m_vertexCount += sub->getVertexBuffer()->getVertexCount();
        m_indexCount += sub->getIndexBuffer()->getIndexCount();
    }


    const std::shared_ptr<SubGeometry>& Geometry::operator[]
    (
        std::size_t index
    ) const
    {
        PLASTIC_ASSERT(index < m_subGeometry.size());

        return m_subGeometry[index];
    }

    bool Geometry::hasSubGeometry
    (
    ) const
    {
        return !m_subGeometry.empty(); 
    }


    std::size_t Geometry::subGeometryCount
    (
    ) const
    {
        return m_subGeometry.size();
    }


    unsigned int Geometry::getVertexCount() const
    {
        return m_vertexCount;
    }


    unsigned int Geometry::getIndexCount() const
    {
        return m_indexCount;
    }



} // namespace plt
