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


#ifndef PLASTIC_GLENUM_HPP
#define PLASTIC_GLENUM_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/OpenGL.hpp>

#include <Plastic/Core/PixelFormat.hpp>

#include "Geometry.hpp"
#include "Sampler.hpp"
#include "Shader.hpp"
#include "VertexElement.hpp"

#include <vector>

namespace plt
{
    class GLEnum
    {
    public:
        static GLenum getPrimitiveType(PrimitiveType primitiveType);

        static GLenum getInternalFormat(PixelFormat format);
        static GLenum getExternalFormat(PixelFormat format);

        static GLenum getType(PixelFormat format);

        static GLenum getGLSLTypeTexture1D(PixelFormat format);
        static GLenum getGLSLTypeTexture2D(PixelFormat format);
        static GLenum getGLSLTypeTexture2DArray(PixelFormat format);
        static GLenum getGLSLTypeTextureRect(PixelFormat format);
        static GLenum getGLSLTypeTextureCubeMap(PixelFormat format);

        static GLenum getTexCoordWrapMode(SamplerTexCoordWrapMode mode);
        static GLenum getMinFilter(SamplerMinFilter filter);
        static GLenum getMagFilter(SamplerMagFilter filter);
        static GLenum getCompareMode(SamplerCompareMode mode);
        static GLenum getCompareFunc(SamplerCompareFunc func);

        static GLenum getShaderType(ShaderType type);

        static GLenum getType(VertexElementType type);

    private:
        static const std::vector<GLenum> m_primitivesTypes;

        static const std::vector<GLenum> m_internalsFormatsTypes;
        static const std::vector<GLenum> m_externalsFormatsTypes;

        static const std::vector<GLenum> m_pixelsFormatsTypes;

        static const std::vector<GLenum> m_glslTypeTexture1D;
        static const std::vector<GLenum> m_glslTypeTexture2D;
        static const std::vector<GLenum> m_glslTypeTexture2DArray;
        static const std::vector<GLenum> m_glslTypeTextureRect;
        static const std::vector<GLenum> m_glslTypeTextureCubeMap;

        static const std::vector<GLenum> m_samplerTexCoordWrapMode;
        static const std::vector<GLenum> m_samplerMinFilter;
        static const std::vector<GLenum> m_samplerMagFilter;
        static const std::vector<GLenum> m_samplerCompareMode;
        static const std::vector<GLenum> m_samplerCompareFunc;

        static const std::vector<GLenum> m_shaderTypes;

        static const std::vector<GLenum> m_vertexElementsTypes;
    };
    
} // namespace plt


#endif // PLASTIC_GLENUM_HPP



////////////////////////////////////////////////////////////
/// \class plt::GLEnum
///
////////////////////////////////////////////////////////////
