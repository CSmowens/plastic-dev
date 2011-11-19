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

#include "GLEnum.hpp"

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

#include <algorithm>
#include <stdexcept>

namespace plt
{
    Shader::Shader
	(
        ShaderType type, 
        const std::string &shaderSource
	) :
    m_type(type),
	m_shader(0)
	{
        try
        {
            initialize(type, shaderSource);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during Shader initialization"
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
        ShaderType type, 
        const std::string &shaderSource
	)
	{
		char const *sourcePointer = shaderSource.c_str();

		GLCheck(m_shader = glCreateShader( GLEnum::getShaderType(type) ));

		if(m_shader == 0)
			throw std::runtime_error("Error during glCreateShader()");


		GLCheck(glShaderSource(m_shader, 1, &sourcePointer, NULL));
		GLCheck(glCompileShader(m_shader));

        GLint result = GL_TRUE;
        GLCheck(glGetShaderiv(m_shader, GL_COMPILE_STATUS, &result));

        if(result == GL_FALSE)
        {
		    int infoLogLength;
		    GLCheck(glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength));

		    std::vector<char> buffer(infoLogLength);
		    GLCheck(glGetShaderInfoLog(m_shader, infoLogLength, NULL, &buffer[0]));

            std::string error = &buffer[0];
            
			throw std::runtime_error("Error during glCompileShader() : " + error);
        }
	}


	void Shader::cleanUp
	(

	)
	{
		if( glIsShader(m_shader) )
			GLCheck(glDeleteShader(m_shader));
	}


    ShaderType Shader::getShaderType
    (
    ) const
    {
        return m_type;
    }


    GLuint Shader::getOpenGLHandle
    (
    ) const
    {
        return m_shader;
    }


} // namespace plt
