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
#include "Program.hpp"

#include <Plastic/Config.hpp>

#include <Plastic/Core/Assert.hpp>

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

#include "VertexElementSemantic.hpp"

#include <algorithm>
#include <stdexcept>

namespace plt
{
    Program::Program
	(
        const std::vector<std::shared_ptr<Shader>> &shaders
	) :
	m_program(0)
	{
        try
        {
            initialize(shaders);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during Program initialization"
        }
	}


	Program::~Program
	(

	)
	{
		cleanUp();
	}


	void Program::initialize
	(
        const std::vector<std::shared_ptr<Shader>> &shaders
	)
	{
	    GLCheck(m_program = glCreateProgram());
	
	    if(m_program == 0)
		    throw std::runtime_error("Error during glCreateProgram()");

        for(auto it = shaders.begin(); it != shaders.end(); ++it)
	        GLCheck(glAttachShader(m_program, (*it)->getOpenGLHandle()));

        assignAttribsLocations();

	    GLCheck(glLinkProgram(m_program));
        checkProgram();

	    getUniformsInfos();
	    getAttributesInfos();

	    extractDeclaration();
	}


	void Program::cleanUp
	(

	)
	{
		if( glIsProgram(m_program) )
			GLCheck(glDeleteProgram(m_program));
	}


    const VertexDeclaration& Program::getVertexDeclaration
    (
    
    ) const
    {
        return m_declaration;
    }


    void Program::assignAttribsLocations
    (
    ) const
    {
        for(auto it = VertexElementSemanticInfos::m_semanticsInfos.begin(); it != VertexElementSemanticInfos::m_semanticsInfos.end(); ++it)
        {
            GLCheck(glBindAttribLocation (m_program,
                                          static_cast<unsigned int>(it->first),
                                          &it->second.name()[0]
                                          ));
        }
    }


    void Program::checkProgram
    (

    )
    {
        GLint result = GL_TRUE;
		GLCheck(glGetProgramiv(m_program, GL_LINK_STATUS, &result));

        if(result == GL_FALSE)
        {
		    int infoLogLength;
		    GLCheck(glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength));

		    std::vector<char> buffer(infoLogLength);
		    GLCheck(glGetProgramInfoLog(m_program, infoLogLength, NULL, &buffer[0]));

            std::string error = &buffer[0];
            
			throw std::runtime_error("Error during glLinkProgram() : " + error);
        }
    }


	void Program::getUniformsInfos
	(
	)
	{
        GLint nbUniform = 0;
        GLCheck(glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &nbUniform));

        GLint maxLength = 0;
        GLCheck(glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength));

        
        if(maxLength == 0)
            throw std::runtime_error("Program haven't got uniform");


        // Seems that some implementation use an extra null terminator
        ++maxLength;


        for(GLint i(0); i<nbUniform; ++i)
        {
            std::vector<char> str(maxLength);

            GLenum type = 0;
            GLint location = 0;
            GLint size = 0;

            GLCheck(glGetActiveUniform(m_program, i, maxLength, NULL, &size, &type, &str[0]));

            GLCheck(location = glGetUniformLocation(m_program, &str[0]));

            std::string name = &str[0];

            if(location == -1)   
                throw std::runtime_error("glGetUniformLocation : uniform \"" + name + "\" doesn't exist!");
        
            m_uniforms.push_back( UniformInfo {location, type, name} );
        }

	}


	void Program::getAttributesInfos
	(
	)
	{
        GLint nbAttributes = 0;
        GLCheck(glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &nbAttributes));

        GLint maxLength = 0;
        GLCheck(glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength));

        
        if(maxLength == 0)
            throw std::runtime_error("Program haven't got attributes");


        // Seems that some implementation use an extra null terminator
        ++maxLength;


        for(GLint i(0); i<nbAttributes; ++i)
        {
            std::vector<char> str(maxLength);

            GLenum type = 0;
            GLint location = 0;
            GLint size = 0;

            GLCheck(glGetActiveAttrib(m_program, i, maxLength, NULL, &size, &type, &str[0]));

            std::string name = &str[0];

            GLCheck(location = glGetAttribLocation(m_program, &str[0]));

            if(location == -1)   
                throw std::runtime_error("glGetAttribLocation : attribute \"" + name + "\" doesn't exist!");
        
            m_attributes.push_back( AttributeInfo{location, type, name} );
        }
	}


	void Program::extractDeclaration
	(
	)
	{
		for(auto it=m_attributes.begin(); it!=m_attributes.end(); ++it)
        {
            m_declaration.add( 
                              VertexElementSemanticInfos::retrieveSemanticFromName(it->name),
                              VertexElementTypeInfos::retrieveTypeFromGLType(it->type) 
                             );
        }
	}


    void Program::bind
    (
    ) const
    {
        GLCheck(glUseProgram(m_program));
    }


    GLint Program::getUniformLocation
    (
        const std::string &name
    ) const
    {
        auto it = std::find_if(m_uniforms.begin(), m_uniforms.end(), [&name](const UniformInfo &u) {return u.name == name;} );

        if( it != m_uniforms.end() )
            return (*it).location;

        else
            throw std::runtime_error("glUniform : The uniform \"" + name + "\" doesn't exist in shader (maybe is remove by GLSL compiler if is not use)");
    }


    void Program::checkUniformFromLocation
    (
        GLint location, 
        GLenum type 
    ) const
    {
        auto it = std::find_if(m_uniforms.begin(), m_uniforms.end(), [&location](const UniformInfo &u) {return u.location == location;} );

        if(it == m_uniforms.end())
            throw std::runtime_error("Use an uniform that doesn't exist");

        if( (*it).type != type )
            throw std::runtime_error("The uniform type doesn't matches for " + (*it).name);
    }
















#if PLASTIC_DEBUG == 0
    #define PLASTIC_CHECK_UNIFORM(location, type)
#else
    #define PLASTIC_CHECK_UNIFORM(location, type) checkUniformFromLocation(location, type)
#endif


	void Program::setParameter
    (
        GLint location,
        const mat4 &matrix
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_MAT4);
                      
        GLCheck( glUniformMatrix4fv(location, 1, false, &matrix[0][0]) );
	}


	void Program::setParameter
    (
        GLint location,
        const mat3 &matrix
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_MAT3);

        GLCheck( glUniformMatrix3fv(location, 1, false, &matrix[0][0]) );
	}


    void Program::setParameter
    (
        GLint location, 
        GLfloat data
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT);

        GLCheck( glUniform1fv(location, 1, &data) );
	}


    void Program::setParameter
    (
        GLint location, 
        const vec2 &vector
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_VEC2);

        GLCheck( glUniform2fv(location, 1, &vector[0]) );
	}


    void Program::setParameter
    (
        GLint location, 
        const vec3 &vector
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_VEC3);

        GLCheck( glUniform3fv(location, 1, &vector[0]) );
	}


    void Program::setParameter
    (
        GLint location, 
        const vec4 &vector
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_VEC4);

        GLCheck( glUniform4fv(location, 1, &vector[0]) );
	}


    void Program::setParameter
    (
        GLint location, 
        GLuint data
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_UNSIGNED_INT);

        GLCheck( glUniform1uiv(location, 1, &data) );
	}


    void Program::setParameter
    (
        GLint location, 
        GLint data
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_INT);

        GLCheck( glUniform1iv(location, 1, &data) );
	}














    void Program::setParameter
    (
        const std::string &name, 
        const std::shared_ptr<Texture> &tex, 
        unsigned int textureUnit
    ) const
    {
        GLint location = getUniformLocation(name);

        setParameter(location, tex, textureUnit);
    }


    void Program::setParameter
    (
        GLint location, 
        const std::shared_ptr<Texture> &tex, 
        unsigned int textureUnit
    ) const
    {
        // Si on a un Depth** Format il faut tester aussi avec les 
        PLASTIC_CHECK_UNIFORM(location, tex->getGLSLType());

        GLCheck( glUniform1i(location, textureUnit) );
    }

#undef PLASTIC_CHECK_UNIFORM



} // namespace plt
