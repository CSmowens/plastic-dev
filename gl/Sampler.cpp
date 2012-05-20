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
#include "Sampler.hpp"

#include <Plastic/Core/Vector4.hpp>

#include "GLEnum.hpp"

#include <stdexcept>

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

namespace plt
{
    Sampler::Sampler
    (
    ) :
    m_sampler(0),
    m_wrapModeS(SamplerTexCoordWrapMode::Repeat),
    m_wrapModeT(SamplerTexCoordWrapMode::Repeat),
    m_wrapModeR(SamplerTexCoordWrapMode::Repeat),
    m_minFilter(SamplerMinFilter::NearestMipmapLinear),
    m_magFilter(SamplerMagFilter::Linear),
    m_compareMode(SamplerCompareMode::None),
    m_compareFunc(SamplerCompareFunc::LessOrEqual)
    {
        try
        {
            initialize();
        }
        
        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during Sampler initialisation");
        }  
    }


    Sampler::~Sampler
    (
    )
    {
        cleanUp();
    }


    void Sampler::initialize
    (
    )
    {
        GLCheck( glGenSamplers(1, &m_sampler) );
    }


    void Sampler::bind
    (
        unsigned int unit
    )
    {
        GLCheck( glBindSampler(unit, m_sampler) );
    }


    void Sampler::cleanUp
    (
    )
    {
        if(glIsSampler(m_sampler))
            GLCheck( glDeleteSamplers(1, &m_sampler) );
    }


    void Sampler::setTexCoordSWrapMode
    (
        SamplerTexCoordWrapMode mode
    )
    {
        m_wrapModeS = mode;

        GLCheck( glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GLEnum::getTexCoordWrapMode(mode)) );
    }


    void Sampler::setTexCoordTWrapMode
    (
        SamplerTexCoordWrapMode mode
    )
    {
        m_wrapModeT = mode;

        GLCheck( glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GLEnum::getTexCoordWrapMode(mode)) );
    }


    void Sampler::setTexCoordRWrapMode
    (
        SamplerTexCoordWrapMode mode
    )
    {
        m_wrapModeR = mode;

        GLCheck( glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, GLEnum::getTexCoordWrapMode(mode)) );
    }


    void Sampler::setMinFilter
    (
        SamplerMinFilter filter
    )
    {
        m_minFilter = filter;

        GLCheck( glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GLEnum::getMinFilter(filter)) );
    }

    void Sampler::setMagFilter
    (
        SamplerMagFilter filter
    )
    {
        m_magFilter = filter;

        GLCheck( glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GLEnum::getMagFilter(filter)) );
    }


    void Sampler::setCompareMode
    (
        SamplerCompareMode mode
    )
    {
        m_compareMode = mode;

        GLCheck( glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_MODE, GLEnum::getCompareMode(mode)) );
    }


    void Sampler::setCompareFunc
    (
        SamplerCompareFunc func
    )
    {
        m_compareFunc = func;

        GLCheck( glSamplerParameteri(m_sampler, GL_TEXTURE_COMPARE_FUNC, GLEnum::getCompareFunc(func)) );
    }

} // namespace plt
