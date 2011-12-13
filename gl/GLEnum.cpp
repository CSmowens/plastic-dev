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

#include <stdexcept>

namespace plt
{
    GLenum GLEnum::getPrimitiveType(PrimitiveType primitiveType)
    {
        switch(primitiveType)
        {
            case PrimitiveType::Triangles:    return GL_TRIANGLES;   break;
            case PrimitiveType::Lines:        return GL_LINES;       break;
            case PrimitiveType::Points:       return GL_POINTS;      break;

            default:    throw std::runtime_error("Unregistered PrimitiveType");    break;
        }
    }


    GLenum GLEnum::getInternalFormat(PixelFormat format)
    {
        switch(format)
        {
	        case PixelFormat::R8U:        return GL_RED;    break;
	        case PixelFormat::RG8U:       return GL_RG;     break;
	        case PixelFormat::RGB8U:      return GL_RGB;    break;
	        case PixelFormat::RGBA8U:     return GL_RGBA;   break;

            case PixelFormat::Depth16:    return GL_DEPTH_COMPONENT16;    break;
            case PixelFormat::Depth24:    return GL_DEPTH_COMPONENT24;    break;
            case PixelFormat::Depth32:    return GL_DEPTH_COMPONENT32;    break;

	        case PixelFormat::R16F:       return GL_RED;    break;
	        case PixelFormat::RG16F:      return GL_RG;     break;
	        case PixelFormat::RGB16F:     return GL_RGB;    break;
	        case PixelFormat::RGBA16F:    return GL_RGBA;   break;

	        case PixelFormat::R32F:       return GL_RED;    break;
	        case PixelFormat::RG32F:      return GL_RG;     break;
	        case PixelFormat::RGB32F:     return GL_RGB;    break;
	        case PixelFormat::RGBA32F:    return GL_RGBA;   break;

            default:    throw std::runtime_error("Unregistered PixelFormat");    break;
        }
    }


    GLenum GLEnum::getExternalFormat(PixelFormat format)
    {
        switch(format)
        {
	        case PixelFormat::R8U:
	        case PixelFormat::R16F:
	        case PixelFormat::R32F:
                return GL_RED;
                break;

	        case PixelFormat::RG8U:
	        case PixelFormat::RG16F:
	        case PixelFormat::RG32F:
                return GL_RG;
                break;

	        case PixelFormat::RGB8U:
	        case PixelFormat::RGB16F:
	        case PixelFormat::RGB32F:
                return GL_RGB;
                break;

	        case PixelFormat::RGBA8U:
	        case PixelFormat::RGBA16F:
	        case PixelFormat::RGBA32F:
                return GL_RGBA;
                break;

            case PixelFormat::Depth16:
            case PixelFormat::Depth24:
            case PixelFormat::Depth32:
                return GL_DEPTH_COMPONENT;
                break;

            default:    throw std::runtime_error("Unregistered PixelFormat");    break;
        }
    }


    GLenum GLEnum::getType(PixelFormat format)
    {
        switch(format)
        {
	        case PixelFormat::R8U:
	        case PixelFormat::RG8U:
	        case PixelFormat::RGB8U:
	        case PixelFormat::RGBA8U:

            case PixelFormat::Depth16:
            case PixelFormat::Depth24:
            case PixelFormat::Depth32:
                return GL_UNSIGNED_BYTE;
                break;

	        case PixelFormat::R16F:
	        case PixelFormat::RG16F:
	        case PixelFormat::RGB16F:
	        case PixelFormat::RGBA16F:

	        case PixelFormat::R32F:
	        case PixelFormat::RG32F:
	        case PixelFormat::RGB32F:
	        case PixelFormat::RGBA32F:
                return GL_FLOAT;
                break;

            default:    throw std::runtime_error("Unregistered PixelFormat");    break;
        }
    }


    GLenum GLEnum::getGLSLTypeTexture1D(PixelFormat format)
    {
        switch(format)
        {
	        case PixelFormat::R8U:
	        case PixelFormat::RG8U:
	        case PixelFormat::RGB8U:
	        case PixelFormat::RGBA8U:

            case PixelFormat::Depth16:
            case PixelFormat::Depth24:
            case PixelFormat::Depth32:

	        case PixelFormat::R16F:
	        case PixelFormat::RG16F:
	        case PixelFormat::RGB16F:
	        case PixelFormat::RGBA16F:

	        case PixelFormat::R32F:
	        case PixelFormat::RG32F:
	        case PixelFormat::RGB32F:
	        case PixelFormat::RGBA32F:
                return GL_SAMPLER_1D;
                break;

            default:    throw std::runtime_error("Unregistered PixelFormat");    break;
        }
    }


    GLenum GLEnum::getGLSLTypeTexture2D(PixelFormat format)
    {
        switch(format)
        {
	        case PixelFormat::R8U:
	        case PixelFormat::RG8U:
	        case PixelFormat::RGB8U:
	        case PixelFormat::RGBA8U:

            case PixelFormat::Depth16:
            case PixelFormat::Depth24:
            case PixelFormat::Depth32:

	        case PixelFormat::R16F:
	        case PixelFormat::RG16F:
	        case PixelFormat::RGB16F:
	        case PixelFormat::RGBA16F:

	        case PixelFormat::R32F:
	        case PixelFormat::RG32F:
	        case PixelFormat::RGB32F:
	        case PixelFormat::RGBA32F:
                return GL_SAMPLER_2D;
                break;

            default:    throw std::runtime_error("Unregistered PixelFormat");    break;
        }
    }


    GLenum GLEnum::getGLSLTypeTexture2DArray(PixelFormat format)
    {
        switch(format)
        {
	        case PixelFormat::R8U:
	        case PixelFormat::RG8U:
	        case PixelFormat::RGB8U:
	        case PixelFormat::RGBA8U:

            case PixelFormat::Depth16:
            case PixelFormat::Depth24:
            case PixelFormat::Depth32:

	        case PixelFormat::R16F:
	        case PixelFormat::RG16F:
	        case PixelFormat::RGB16F:
	        case PixelFormat::RGBA16F:

	        case PixelFormat::R32F:
	        case PixelFormat::RG32F:
	        case PixelFormat::RGB32F:
	        case PixelFormat::RGBA32F:
                return GL_SAMPLER_2D_ARRAY;
                break;

            default:    throw std::runtime_error("Unregistered PixelFormat");    break;
        }
    }


    GLenum GLEnum::getGLSLTypeTextureRect(PixelFormat format)
    {
        switch(format)
        {
	        case PixelFormat::R8U:
	        case PixelFormat::RG8U:
	        case PixelFormat::RGB8U:
	        case PixelFormat::RGBA8U:

            case PixelFormat::Depth16:
            case PixelFormat::Depth24:
            case PixelFormat::Depth32:

	        case PixelFormat::R16F:
	        case PixelFormat::RG16F:
	        case PixelFormat::RGB16F:
	        case PixelFormat::RGBA16F:

	        case PixelFormat::R32F:
	        case PixelFormat::RG32F:
	        case PixelFormat::RGB32F:
	        case PixelFormat::RGBA32F:
                return GL_SAMPLER_2D_RECT;
                break;

            default:    throw std::runtime_error("Unregistered PixelFormat");    break;
        }
    }


    GLenum GLEnum::getGLSLTypeTextureCubeMap(PixelFormat format)
    {
        switch(format)
        {
	        case PixelFormat::R8U:
	        case PixelFormat::RG8U:
	        case PixelFormat::RGB8U:
	        case PixelFormat::RGBA8U:

            case PixelFormat::Depth16:
            case PixelFormat::Depth24:
            case PixelFormat::Depth32:

	        case PixelFormat::R16F:
	        case PixelFormat::RG16F:
	        case PixelFormat::RGB16F:
	        case PixelFormat::RGBA16F:

	        case PixelFormat::R32F:
	        case PixelFormat::RG32F:
	        case PixelFormat::RGB32F:
	        case PixelFormat::RGBA32F:
                return GL_SAMPLER_CUBE;
                break;

            default:    throw std::runtime_error("Unregistered PixelFormat");    break;
        }
    }


    GLenum GLEnum::getTexCoordWrapMode(SamplerTexCoordWrapMode mode)
    {
        switch(mode)
        {
            case SamplerTexCoordWrapMode::Repeat:         return GL_REPEAT;           break;
            case SamplerTexCoordWrapMode::ClampToEdge:    return GL_CLAMP_TO_EDGE;    break;

            default:    throw std::runtime_error("Unregistered SamplerCompareMode");    break;
        }
    }


    GLenum GLEnum::getMinFilter(SamplerMinFilter filter)
    {
        switch(filter)
        {
            case SamplerMinFilter::Nearest:                return GL_NEAREST;                  break;
            case SamplerMinFilter::Linear:                 return GL_LINEAR;                   break;
            case SamplerMinFilter::NearestMipmapNearest:   return GL_NEAREST_MIPMAP_NEAREST;   break;
            case SamplerMinFilter::LinearMipmapNearest:    return GL_LINEAR_MIPMAP_NEAREST;    break;
            case SamplerMinFilter::NearestMipmapLinear:    return GL_NEAREST_MIPMAP_LINEAR;    break;
            case SamplerMinFilter::LinearMipmapLinear:     return GL_LINEAR_MIPMAP_LINEAR;     break;

            default:    throw std::runtime_error("Unregistered SamplerMinFilter");    break;
        }
    }


    GLenum GLEnum::getMagFilter(SamplerMagFilter filter)
    {
        switch(filter)
        {
            case SamplerMagFilter::Nearest:   return GL_NEAREST;  break;
            case SamplerMagFilter::Linear:    return GL_LINEAR;   break;

            default:    throw std::runtime_error("Unregistered SamplerMagFilter");    break;
        }
    }


    GLenum GLEnum::getCompareMode(SamplerCompareMode mode)
    {
        switch(mode)
        {
            case SamplerCompareMode::CompareRefToTexture:    return GL_COMPARE_REF_TO_TEXTURE;     break;
            case SamplerCompareMode::None:                   return GL_NONE;                       break;

            default:    throw std::runtime_error("Unregistered SamplerCompareMode");    break;
        }
    }


    GLenum GLEnum::getCompareFunc(SamplerCompareFunc func)
    {
        switch(func)
        {
            case SamplerCompareFunc::LessOrEqual:       return GL_LEQUAL;     break;
            case SamplerCompareFunc::GreaterOrEqual:    return GL_GEQUAL;     break;
            case SamplerCompareFunc::Less:              return GL_LESS;       break;
            case SamplerCompareFunc::Greater:           return GL_GREATER;    break;
            case SamplerCompareFunc::Equal:             return GL_EQUAL;      break;
            case SamplerCompareFunc::NotEqual:          return GL_NOTEQUAL;   break;
            case SamplerCompareFunc::Always:            return GL_ALWAYS;     break;
            case SamplerCompareFunc::Never:             return GL_NEVER;      break;

            default:    throw std::runtime_error("Unregistered SamplerCompareFunc");    break;
        }
    }


    GLenum GLEnum::getShaderType(ShaderType type)
    {
        switch(type)
        {
            case ShaderType::Vertex:      return GL_VERTEX_SHADER;     break;
            case ShaderType::Geometry:    return GL_GEOMETRY_SHADER;   break;
            case ShaderType::Fragment:    return GL_FRAGMENT_SHADER;   break;

            default:    throw std::runtime_error("Unregistered ShaderType");    break;
        }
    }


    GLenum GLEnum::getType(VertexElementType type)
    {
        switch(type)
        {
            case VertexElementType::Float1:
            case VertexElementType::Float2:
            case VertexElementType::Float3:
            case VertexElementType::Float4:
                return GL_FLOAT; 
                break;

            default:    throw std::runtime_error("Unregistered VertexElementType");    break;
        }
    }


    GLenum GLEnum::getIndexType(unsigned int size)
    {
        switch(size)
        {
            case 1:    return GL_UNSIGNED_BYTE;    break;
            case 2:    return GL_UNSIGNED_SHORT;   break;
            case 4:    return GL_UNSIGNED_INT;     break;

            default:    throw std::runtime_error("Unregistered size index");    break;
        }
    }

} // namespace plt
