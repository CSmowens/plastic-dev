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
#include "GLEnum.hpp"


namespace plt
{
    const std::vector<GLenum> GLEnum::m_primitivesTypes =
    {
        GL_TRIANGLES,
        GL_LINES,
        GL_POINTS
    };


    const std::vector<GLenum> GLEnum::m_internalsFormatsTypes =
    {
        GL_RED,
        GL_RG,
        GL_RGB,
        GL_RGBA,
        GL_DEPTH_COMPONENT16,
        GL_DEPTH_COMPONENT24,
        GL_DEPTH_COMPONENT32
    };


    const std::vector<GLenum> GLEnum::m_externalsFormatsTypes =
    {
        GL_RED,
        GL_RG,
        GL_RGB,
        GL_RGBA,
        GL_DEPTH_COMPONENT,
        GL_DEPTH_COMPONENT,
        GL_DEPTH_COMPONENT
    };


    const std::vector<GLenum> GLEnum::m_pixelsFormatsTypes =
    {
        GL_UNSIGNED_BYTE,
        GL_UNSIGNED_BYTE,
        GL_UNSIGNED_BYTE,
        GL_UNSIGNED_BYTE,
        GL_UNSIGNED_BYTE,
        GL_UNSIGNED_BYTE,
        GL_UNSIGNED_BYTE,
    };


    const std::vector<GLenum> GLEnum::m_glslTypeTexture1D =
    {
        GL_SAMPLER_1D,
        GL_SAMPLER_1D,
        GL_SAMPLER_1D,
        GL_SAMPLER_1D,
        GL_SAMPLER_1D,
        GL_SAMPLER_1D,
        GL_SAMPLER_1D
    };


    const std::vector<GLenum> GLEnum::m_glslTypeTexture2D =
    {
        GL_SAMPLER_2D,
        GL_SAMPLER_2D,
        GL_SAMPLER_2D,
        GL_SAMPLER_2D,
        GL_SAMPLER_2D,
        GL_SAMPLER_2D,
        GL_SAMPLER_2D
    };


    const std::vector<GLenum> GLEnum::m_glslTypeTexture2DArray =
    {
        GL_SAMPLER_2D_ARRAY,
        GL_SAMPLER_2D_ARRAY,
        GL_SAMPLER_2D_ARRAY,
        GL_SAMPLER_2D_ARRAY,
        GL_SAMPLER_2D_ARRAY,
        GL_SAMPLER_2D_ARRAY,
        GL_SAMPLER_2D_ARRAY,
    };


    const std::vector<GLenum> GLEnum::m_glslTypeTextureRect =
    {
        GL_SAMPLER_2D_RECT,
        GL_SAMPLER_2D_RECT,
        GL_SAMPLER_2D_RECT,
        GL_SAMPLER_2D_RECT,
        GL_SAMPLER_2D_RECT,
        GL_SAMPLER_2D_RECT,
        GL_SAMPLER_2D_RECT
    };


    const std::vector<GLenum> GLEnum::m_glslTypeTextureCubeMap = 
    {
        GL_SAMPLER_CUBE,
        GL_SAMPLER_CUBE,
        GL_SAMPLER_CUBE,
        GL_SAMPLER_CUBE,
        GL_SAMPLER_CUBE,
        GL_SAMPLER_CUBE,
        GL_SAMPLER_CUBE
    };


    const std::vector<GLenum> GLEnum::m_samplerTexCoordWrapMode =
    {
        GL_REPEAT,
        GL_CLAMP_TO_EDGE
    };


    const std::vector<GLenum> GLEnum::m_samplerMinFilter =
    {
        GL_NEAREST,
        GL_LINEAR,
        GL_NEAREST_MIPMAP_NEAREST,
        GL_LINEAR_MIPMAP_NEAREST,
        GL_NEAREST_MIPMAP_LINEAR,
        GL_LINEAR_MIPMAP_LINEAR
    };


    const std::vector<GLenum> GLEnum::m_samplerMagFilter =
    {
        GL_NEAREST,
        GL_LINEAR
    };


    const std::vector<GLenum> GLEnum::m_samplerCompareMode =
    {
        GL_COMPARE_REF_TO_TEXTURE,
        GL_NONE
    };


    const std::vector<GLenum> GLEnum::m_samplerCompareFunc =
    {    
        GL_LEQUAL,
        GL_GEQUAL,
        GL_LESS,
        GL_GREATER,
        GL_EQUAL,
        GL_NOTEQUAL,
        GL_ALWAYS,
        GL_NEVER
    };


    const std::vector<GLenum> GLEnum::m_shaderTypes =
    {
        GL_VERTEX_SHADER,
        GL_FRAGMENT_SHADER
    };



    const std::vector<GLenum> GLEnum::m_vertexElementsTypes =
    {
        GL_FLOAT,
        GL_FLOAT,
        GL_FLOAT,
        GL_FLOAT
    };











    GLenum GLEnum::getPrimitiveType(PrimitiveType primitiveType)
    {
        return m_primitivesTypes[ static_cast<std::size_t>(primitiveType) ];
    }


    GLenum GLEnum::getInternalFormat(PixelFormat format)
    {
        return m_internalsFormatsTypes[ static_cast<std::size_t>(format) ];
    }


    GLenum GLEnum::getExternalFormat(PixelFormat format)
    {
        return m_externalsFormatsTypes[ static_cast<std::size_t>(format) ];
    }


    GLenum GLEnum::getType(PixelFormat format)
    {
        return m_pixelsFormatsTypes[ static_cast<std::size_t>(format) ];
    }


    GLenum GLEnum::getGLSLTypeTexture1D(PixelFormat format)
    {
        return m_glslTypeTexture1D[ static_cast<std::size_t>(format) ];
    }


    GLenum GLEnum::getGLSLTypeTexture2D(PixelFormat format)
    {
        return m_glslTypeTexture2D[ static_cast<std::size_t>(format) ];
    }


    GLenum GLEnum::getGLSLTypeTexture2DArray(PixelFormat format)
    {
        return m_glslTypeTexture2DArray[ static_cast<std::size_t>(format) ];
    }


    GLenum GLEnum::getGLSLTypeTextureRect(PixelFormat format)
    {
        return m_glslTypeTextureRect[ static_cast<std::size_t>(format) ];
    }


    GLenum GLEnum::getGLSLTypeTextureCubeMap(PixelFormat format)
    {
        return m_glslTypeTextureCubeMap[ static_cast<std::size_t>(format) ];
    }


    GLenum GLEnum::getTexCoordWrapMode(SamplerTexCoordWrapMode mode)
    {
        return m_samplerTexCoordWrapMode[ static_cast<std::size_t>(mode) ];
    }

    GLenum GLEnum::getMinFilter(SamplerMinFilter filter)
    {
        return m_samplerMinFilter[ static_cast<std::size_t>(filter) ];
    }

    GLenum GLEnum::getMagFilter(SamplerMagFilter filter)
    {
        return m_samplerMagFilter[ static_cast<std::size_t>(filter) ];
    }


    GLenum GLEnum::getCompareMode(SamplerCompareMode mode)
    {
        return m_samplerCompareMode[ static_cast<std::size_t>(mode) ];
    }


    GLenum GLEnum::getCompareFunc(SamplerCompareFunc func)
    {
        return m_samplerCompareFunc[ static_cast<std::size_t>(func) ];
    }


    GLenum GLEnum::getShaderType(ShaderType type)
    {
        return m_shaderTypes[ static_cast<std::size_t>(type) ];
    }


    GLenum GLEnum::getType(VertexElementType type)
    {
        return m_vertexElementsTypes[ static_cast<std::size_t>(type) ];
    }

} // namespace plt
