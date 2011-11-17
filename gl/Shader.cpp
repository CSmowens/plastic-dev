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
#include "Shader.hpp"

#include <Plastic/Config.hpp>

#include <Plastic/Core/Assert.hpp>

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

#include <algorithm>
#include <stdexcept>

namespace plt
{
    Shader::Shader
	(
		const std::string &vertexShaderSource, 
		const std::string &fragmentShaderSource
	) :
	m_program(0)
	{
        try
        {
            initialize(vertexShaderSource, fragmentShaderSource);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during TextureRect initialisation"
        }
	}


	Shader::~Shader
	(

	)
	{
		cleanUp();
	}


	void Shader::initialize
	(
		const std::string &vertexShaderSource, 
		const std::string &fragmentShaderSource
	)
	{
	    GLCheck(m_program = glCreateProgram());
	
	    if(m_program == 0)
		    throw std::runtime_error("Error during glCreateProgram()");


        GLuint vertexShader = 0, fragmentShader = 0;

        vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
        fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	    GLCheck(glAttachShader(m_program, vertexShader));
	    GLCheck(glAttachShader(m_program, fragmentShader));

	    GLCheck(glLinkProgram(m_program));


        checkProgram();


        if(glIsShader(vertexShader))
	        GLCheck(glDeleteShader(vertexShader));

        if(glIsShader(fragmentShader))
	        GLCheck(glDeleteShader(fragmentShader));


	    getUniformsInfos();
	    getAttributesInfos();

	    extractDeclaration();
	}


	void Shader::cleanUp
	(

	)
	{
		if( glIsProgram(m_program) )
			GLCheck(glDeleteProgram(m_program));
	}


    const VertexDeclaration& Shader::getVertexDeclaration
    (
    
    ) const
    {
        return m_declaration;
    }


    std::vector<GLint> Shader::getAttribsLocations
    (
        const VertexDeclaration &declaration
    ) const
    {
        if( !areCompatible(declaration, m_declaration) )
            throw std::runtime_error("Declarations aren't compatible");

        std::vector<GLint> locations(m_declaration.count());

        for(std::size_t i(0); i<declaration.count(); ++i)
        {
            for(std::size_t j(0); j<m_declaration.count(); ++j)
            {
                if(declaration[i].getSemantic() == m_declaration[j].getSemantic() && declaration[i].getType() == m_declaration[j].getType() )
                    locations[i] = m_attributes[j].location;
            }
        }

        return locations;
    }


	GLuint Shader::createShader
    (
        GLenum type, 
        const std::string &source
    )
    {
		char const * SourcePointer = source.c_str();


		GLuint shader = 0;
		GLCheck(shader = glCreateShader(type));

		if(shader == 0)
			throw std::runtime_error("Error during glCreateShader()");


		GLCheck(glShaderSource(shader, 1, &SourcePointer, NULL));
		GLCheck(glCompileShader(shader));

        GLint Result = GL_TRUE;
        GLCheck(glGetShaderiv(shader, GL_COMPILE_STATUS, &Result));

        if(Result == GL_FALSE)
        {
		    int InfoLogLength;
		    GLCheck(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength));

		    std::vector<char> Buffer(InfoLogLength);
		    GLCheck(glGetShaderInfoLog(shader, InfoLogLength, NULL, &Buffer[0]));

            std::string error = &Buffer[0];
            
			throw std::runtime_error("Error during glCompileShader() : " + error);
        }

        return shader;
    }


    void Shader::checkProgram
    (

    )
    {
        GLint Result = GL_TRUE;
		GLCheck(glGetProgramiv(m_program, GL_LINK_STATUS, &Result));

        if(Result == GL_FALSE)
        {
		    int InfoLogLength;
		    GLCheck(glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &InfoLogLength));

		    std::vector<char> Buffer(InfoLogLength);
		    GLCheck(glGetProgramInfoLog(m_program, InfoLogLength, NULL, &Buffer[0]));

            std::string error = &Buffer[0];
            
			throw std::runtime_error("Error during glLinkProgram() : " + error);
        }
    }


	void Shader::getUniformsInfos
	(
	)
	{
        GLint nbUniform = 0;
        GLCheck(glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &nbUniform));

        GLint maxLength = 0;
        GLCheck(glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength));

        
        if(maxLength == 0)
            throw std::runtime_error("Shader haven't got uniform");


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


	void Shader::getAttributesInfos
	(
	)
	{
        GLint nbAttributes = 0;
        GLCheck(glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &nbAttributes));

        GLint maxLength = 0;
        GLCheck(glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength));

        
        if(maxLength == 0)
            throw std::runtime_error("Shader haven't got attributes");


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


	void Shader::extractDeclaration
	(
	)
	{
		for(auto it=m_attributes.begin(); it!=m_attributes.end(); ++it)
            m_declaration.add( VertexElement::toSemantic(it->name), VertexElement::toType(it->type) );
	}


    void Shader::bind
    (
    ) const
    {
        GLCheck(glUseProgram(m_program));
    }


    GLint Shader::getUniformLocation
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


    void Shader::checkUniformFromLocation
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


	void Shader::setParameter
    (
        GLint location,
        const mat4 &matrix
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_MAT4);
                      
        GLCheck( glUniformMatrix4fv(location, 1, false, &matrix[0][0]) );
	}


	void Shader::setParameter
    (
        GLint location,
        const mat3 &matrix
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_MAT3);

        GLCheck( glUniformMatrix3fv(location, 1, false, &matrix[0][0]) );
	}


    void Shader::setParameter
    (
        GLint location, 
        GLfloat data
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT);

        GLCheck( glUniform1fv(location, 1, &data) );
	}


    void Shader::setParameter
    (
        GLint location, 
        const vec2 &vector
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_VEC2);

        GLCheck( glUniform2fv(location, 1, &vector[0]) );
	}


    void Shader::setParameter
    (
        GLint location, 
        const vec3 &vector
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_VEC3);

        GLCheck( glUniform3fv(location, 1, &vector[0]) );
	}


    void Shader::setParameter
    (
        GLint location, 
        const vec4 &vector
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_FLOAT_VEC4);

        GLCheck( glUniform4fv(location, 1, &vector[0]) );
	}


    void Shader::setParameter
    (
        GLint location, 
        GLuint data
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_UNSIGNED_INT);

        GLCheck( glUniform1uiv(location, 1, &data) );
	}


    void Shader::setParameter
    (
        GLint location, 
        GLint data
    ) const
	{
        PLASTIC_CHECK_UNIFORM(location, GL_INT);

        GLCheck( glUniform1iv(location, 1, &data) );
	}














    void Shader::setParameter
    (
        const std::string &name, 
        const std::shared_ptr<Texture> &tex, 
        unsigned int textureUnit
    ) const
    {
        GLint location = getUniformLocation(name);

        setParameter(location, tex, textureUnit);
    }


    void Shader::setParameter
    (
        GLint location, 
        const std::shared_ptr<Texture> &tex, 
        unsigned int textureUnit
    ) const
    {
        PLASTIC_CHECK_UNIFORM(location, tex->getGLSLType());

        // \todo Voir si textureUnit < (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1)

        GLCheck( glUniform1i(location, textureUnit) );
    }

#undef PLASTIC_CHECK_UNIFORM



} // namespace plt
