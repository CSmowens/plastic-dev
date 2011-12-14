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
///////////////////////////////////////////////////////////
#include "HardwareGeometry.hpp"

#include "GLEnum.hpp"
#include "VertexElement.hpp"

#include <cstring>
#include <stdexcept>


////////////////////////////////////////////////////////////
// Offset compute
////////////////////////////////////////////////////////////
#define PLASTIC_BUFFER_OFFSET(n) ((char*)NULL + (n))


namespace plt
{
    HardwareGeometry::HardwareGeometry
    (
        const std::shared_ptr<Geometry> &geometry
    )
    {
        try
        {
            initialize(geometry);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during HardwareGeometry initialisation");
        }  
    }


    HardwareGeometry::~HardwareGeometry
    (
    )
    {
        cleanUp();
    }


    void HardwareGeometry::initialize
    (
        const std::shared_ptr<Geometry> &geometry
    )
    {
        if(!geometry->hasSubGeometry())
            throw std::runtime_error("Empty geometry");    

        m_geometry = geometry;

        m_indexType = GLEnum::getIndexType((*geometry)[0]->getIndexBuffer()->getIndexSize());

        m_declaration = (*geometry)[0]->getVertexBuffer()->getVertexDeclaration();

        extractLocations();





        unsigned int offsetVertex(0);
        unsigned int offsetIndex(0);




        GLCheck(glGenBuffers(1, &m_vbo));
	    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	    GLCheck(glBufferData(GL_ARRAY_BUFFER, m_declaration.size()*geometry->getVertexCount(), NULL, GL_STATIC_DRAW));

        for(std::size_t i(0); i<geometry->subGeometryCount(); ++i)
        {
            unsigned int size = (*geometry)[i]->getVertexBuffer()->getVertexCount() * m_declaration.size();

            GLCheck(glBufferSubData(GL_ARRAY_BUFFER, offsetVertex, size, (*geometry)[i]->getVertexBuffer()->getVertexRawData()));

            offsetVertex += size;
        }

	    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));







        GLCheck(glGenBuffers(1, &m_ibo));
	    GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	    GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*geometry)[0]->getIndexBuffer()->getIndexSize()*geometry->getIndexCount(), NULL, GL_STATIC_DRAW));

        for(std::size_t i(0); i<geometry->subGeometryCount(); ++i)
        {
            unsigned int size = (*geometry)[i]->getIndexBuffer()->getIndexCount() * (*geometry)[0]->getIndexBuffer()->getIndexSize();

            GLCheck(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offsetIndex, size, (*geometry)[i]->getIndexBuffer()->getIndexRawData()));

            offsetIndex += size;
        }

	    GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));




	    GLCheck(glGenVertexArrays(1, &m_vao));
        GLCheck(glBindVertexArray(m_vao));
		    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

            for(std::size_t i(0); i<m_declaration.count(); ++i)
            {
                GLCheck(glVertexAttribPointer(m_locations[i], 
                                              VertexElement::count(m_declaration[i].getType()), 
                                              GLEnum::getType(m_declaration[i].getType()), 
                                              GL_FALSE, 
                                              m_declaration.size(), 
                                              PLASTIC_BUFFER_OFFSET(m_declaration[i].getOffset()) ));

                GLCheck(glEnableVertexAttribArray(m_locations[i]));
            }

		    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

            GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	    GLCheck(glBindVertexArray(0));
    }


    void HardwareGeometry::cleanUp
    (

    )
    {
        if( glIsBuffer(m_vbo) )
            GLCheck(glDeleteBuffers(1, &m_vbo));

        if( glIsBuffer(m_ibo) )
            GLCheck(glDeleteBuffers(1, &m_ibo));

        if( glIsVertexArray(m_vao) )
            GLCheck(glDeleteVertexArrays(1, &m_vao));
    }


    void HardwareGeometry::bind
    (
    ) const
    {
        GLCheck(glBindVertexArray(m_vao));
    }


    void HardwareGeometry::unbind
    (
    ) const
    {
        GLCheck(glBindVertexArray(0));
    }


    void HardwareGeometry::draw
    (
    ) const
    {
        GLCheck(glDrawElements(GLEnum::getPrimitiveType((*m_geometry)[0]->getPrimitiveType()), 
                               m_geometry->getIndexCount(),
                               m_indexType, 
                               0));
    }


    void HardwareGeometry::extractLocations
    (
    ) 
    {
        for(std::size_t i(0); i<m_declaration.count(); ++i)
            m_locations.push_back(static_cast<unsigned int>(m_declaration[i].getSemantic()));
    }


} // namespace plt
