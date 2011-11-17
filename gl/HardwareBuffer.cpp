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
#include "HardwareBuffer.hpp"

#include "GLEnum.hpp"

#include <cstring>
#include <stdexcept>


////////////////////////////////////////////////////////////
// Offset compute
////////////////////////////////////////////////////////////
#define PLASTIC_BUFFER_OFFSET(n) ((char*)NULL + (n))


namespace plt
{
    HardwareBuffer::HardwareBuffer
    (
        const std::shared_ptr<Geometry> &geometry, 
        const std::shared_ptr<Shader> &shader
    )
    {
        try
        {
            initialize(geometry, shader);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during HardwareBuffer initialisation");
        }  
    }


    HardwareBuffer::~HardwareBuffer
    (
    )
    {
        cleanUp();
    }


    void HardwareBuffer::initialize
    (
        const std::shared_ptr<Geometry> &geometry, 
        const std::shared_ptr<Shader> &shader
    )
    {
        if(!geometry->hasSubGeometry())
            throw std::runtime_error("Empty geometry");    

        m_geometry = geometry;

        m_declaration = (*geometry)[0]->getVertexDeclaration();

        setShader(shader);


        unsigned int offsetVertex(0);
        unsigned int offsetIndex(0);




        GLCheck(glGenBuffers(1, &m_vbo));
	    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	    GLCheck(glBufferData(GL_ARRAY_BUFFER, m_declaration.size()*geometry->getVertexCount(), NULL, GL_STATIC_DRAW));

        for(std::size_t i(0); i<geometry->subGeometryCount(); ++i)
        {
            unsigned int size = (*geometry)[i]->getVertexCount() * m_declaration.size();

            GLCheck(glBufferSubData(GL_ARRAY_BUFFER, offsetVertex, size, (*geometry)[i]->getVertexRawData()));

            offsetVertex += size;
        }

	    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));







        GLCheck(glGenBuffers(1, &m_ibo));
	    GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	    GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*geometry)[0]->getSizeOfIndexType()*geometry->getIndexCount(), NULL, GL_STATIC_DRAW));

        for(std::size_t i(0); i<geometry->subGeometryCount(); ++i)
        {
            unsigned int size = (*geometry)[i]->getIndexCount() * (*geometry)[0]->getSizeOfIndexType();

            GLCheck(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offsetIndex, size, (*geometry)[i]->getIndexRawData()));

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


    void HardwareBuffer::cleanUp
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


    void HardwareBuffer::bind
    (
    ) const
    {
        GLCheck(glBindVertexArray(m_vao));
    }


    void HardwareBuffer::draw
    (
    ) const
    {
        GLCheck(glDrawElements(GLEnum::getPrimitiveType((*m_geometry)[0]->getPrimitiveType()), 
                               m_geometry->getIndexCount(),
                               (*m_geometry)[0]->getIndexType(), 
                               0));
    }


    void HardwareBuffer::setShader
    (
        const std::shared_ptr<Shader> &shader
    ) 
    {
        m_shader = shader;

        checkCompatibility();

        m_locations = m_shader->getAttribsLocations(m_declaration);
    }


    void HardwareBuffer::checkCompatibility
    (

    ) const
    {
        if( !areCompatible(m_declaration, m_shader->getVertexDeclaration()) )
            throw std::runtime_error("Impossible to associate HardwareBuffer and shader");
    }


    void HardwareBuffer::copyData
    (
        const void *src, 
        unsigned int sizeInByte, 
        unsigned int offsetInByte,
        bool VertexBufferOrIndexBuffer
    )
    {
        GLenum bufferType(0);

        unsigned int sizeOfBuffer(0);

        if(VertexBufferOrIndexBuffer)
        {
    	    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
            bufferType = GL_ARRAY_BUFFER;

            sizeOfBuffer = m_declaration.size()*m_geometry->getVertexCount();
        }

        else
        {
    	    GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
            bufferType = GL_ELEMENT_ARRAY_BUFFER;

            sizeOfBuffer = (*m_geometry)[0]->getSizeOfIndexType()*m_geometry->getIndexCount();
        }

        
        if(sizeInByte + offsetInByte > sizeOfBuffer)
            throw std::runtime_error("Size and/or offset is much bigger than size of buffer");


        void *adress = NULL;
        GLCheck( adress = glMapBuffer(bufferType, GL_WRITE_ONLY) );
        if(!adress)
            throw std::runtime_error("Access to the buffer is impossible");

        std::memcpy(adress + offsetInByte, src, sizeInByte);

        GLCheck( glUnmapBuffer(bufferType) );
    }

} // namespace plt
