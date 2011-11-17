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


#ifndef PLASTIC_SAMPLER_HPP
#define PLASTIC_SAMPLER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/OpenGL.hpp>

namespace plt
{
    /////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    enum class SamplerTexCoordWrapMode
    {
        Repeat,
        ClampToEdge
    };


    /////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    enum class SamplerMinFilter
    {
        Nearest,
        Linear,
        NearestMipmapNearest,
        LinearMipmapNearest,
        NearestMipmapLinear,
        LinearMipmapLinear
    };


    /////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    enum class SamplerMagFilter
    {
        Nearest,
        Linear
    };


    /////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    enum class SamplerCompareMode
    {
        CompareRefToTexture,
        None
    };



    /////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    enum class SamplerCompareFunc
    {
        LessOrEqual,
        GreaterOrEqual,
        Less,
        Greater,
        Equal,
        NotEqual,
        Always,
        Never
    };







	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class Sampler
    {

    public:
        Sampler();

        ~Sampler();

        void bind(unsigned int unit);

        void setTexCoordSWrapMode(SamplerTexCoordWrapMode mode);

        void setTexCoordTWrapMode(SamplerTexCoordWrapMode mode);

        void setTexCoordRWrapMode(SamplerTexCoordWrapMode mode);

        void setMinFilter(SamplerMinFilter filter);

        void setMagFilter(SamplerMagFilter filter);

        void setCompareMode(SamplerCompareMode mode);

        void setCompareFunc(SamplerCompareFunc func);

    private:
        void initialize();

        void cleanUp();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
        GLuint m_sampler;

        SamplerTexCoordWrapMode m_wrapModeS, m_wrapModeT, m_wrapModeR;

        SamplerMinFilter m_minFilter;
        SamplerMagFilter m_magFilter;

        SamplerCompareMode m_compareMode;
        SamplerCompareFunc m_compareFunc;
    };

} // namespace plt


#endif // PLASTIC_SAMPLER_HPP




////////////////////////////////////////////////////////////
/// \class plt::Sampler
///
/// \todo Etre exception safe
/// \todo Renvoyer aussi l'erreur OpenGL
/// \todo Rajouter de quoi changer les differents stats du sampler
///
////////////////////////////////////////////////////////////
