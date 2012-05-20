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

#ifndef PLASTIC_UPLOADERTEXTURE1D_HPP
#define PLASTIC_UPLOADERTEXTURE1D_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "UploaderTextureSingle.hpp"

namespace plt
{
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class UploaderTexture1D : public UploaderTextureSingle
    {
    public:
        virtual TextureType getTextureTypeToLoad();

        virtual GLenum getGLSLType(PixelFormat format);

        virtual GLenum getGLTarget();

        virtual void checkImage(TextureMipmapFlag texMipMapFlag, const std::shared_ptr<Image> &image);

        virtual void uploadImage(TextureMipmapFlag texMipMapFlag, const std::shared_ptr<Image> &image);

        virtual void allocateTextureMemory(PixelFormat format, const uvec2 &dimensions, unsigned int levels);
    };

} // namespace plt


#endif // PLASTIC_UPLOADERTEXTURE1D_HPP




////////////////////////////////////////////////////////////
/// \class plt::UploaderTexture1D
///
///
////////////////////////////////////////////////////////////
