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

#ifndef PLASTIC_UPLOADERTEXTURESINGLE_HPP
#define PLASTIC_UPLOADERTEXTURESINGLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "UploaderTexture.hpp"

namespace plt
{
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class UploaderTextureSingle : public UploaderTexture
    {
    public:
        virtual TextureType getTextureTypeToLoad() = 0;

        virtual GLenum getGLSLType(PixelFormat format) = 0;

        virtual GLenum getGLTarget() = 0;

        virtual void checkImage(TextureMipmapFlag texMipMapFlag, const std::shared_ptr<Image> &image) = 0;

        virtual void uploadImage(TextureMipmapFlag texMipMapFlag, const std::shared_ptr<Image> &image) = 0;

        virtual void allocateTextureMemory(PixelFormat format, const uvec2 &dimensions, unsigned int levels) = 0;
    };

} // namespace plt


#endif // PLASTIC_UPLOADERTEXTURESINGLE_HPP




////////////////////////////////////////////////////////////
/// \class plt::UploaderTexture
///
/// \todo Utiliser glTexStorage* plutôt!! Nécéssite OpenGL 4.2
/// \todo Centraliser les fontions pour verifier qu'il y a bien une image ou plusieurs, etc
///
////////////////////////////////////////////////////////////
