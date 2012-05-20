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

#ifndef PLASTIC_LOADERIMAGETGA_HPP
#define PLASTIC_LOADERIMAGETGA_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Core/Image.hpp>
#include <Plastic/Ressource/Loader.hpp>

#include <memory>

namespace plt
{   
    /////////////////////////////////////////////////////////////
    /// Loader for Targa (TGA) images
    /////////////////////////////////////////////////////////////
    class LoaderImageTGA : public Loader<Image>
    {
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Load a targa image
        ///
        /// Load a targa image from the filename in param
        ///
        /// \param filename : Specifies the name of the file to load
        ///
        /// \return Return a pointer of the image
        ///
        ////////////////////////////////////////////////////////////
        virtual std::shared_ptr<Image> loadFromFile(const std::string& filename);
    };


} // namespace plt


#endif // PLASTIC_LOADERIMAGETGA_HPP




////////////////////////////////////////////////////////////
/// \class plt::LoaderImageTGA
///
/// This class is used by a MediaManager for load and save 
/// targa image.
///
/// For moment save an targa image is not possible.
///
/// \todo Etre endianess safe
/// \todo Voir pour les Pixelformat des niveaux de gris
/// \todo Prendre en charge la compression RLE
/// \todo Optimiser les lectures : lecture complète puis swap BGR -> RGB
///
////////////////////////////////////////////////////////////
