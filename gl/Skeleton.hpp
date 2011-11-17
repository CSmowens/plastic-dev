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


#ifndef PLASTIC_SKELETON_HPP
#define PLASTIC_SKELETON_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Core/Assert.hpp>

#include "Bone.hpp"

#include <vector>
#include <stdexcept>
#include <algorithm>


namespace plt
{

    ////////////////////////////////////////////////////////////
    /// A collection of bones used to animate a skinned mesh
    ////////////////////////////////////////////////////////////
    template<typename T>
    class Skeleton
    {  
    public:
        Skeleton();

        void addBone(int parent, const tvec3<T> &position, const tquat<T> &orientation);

        const Bone<T>& operator[](std::size_t i) const;

        std::size_t bonesCount() const;

    private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        bool m_haveRootBone; ///< 
        std::vector< Bone<T> > m_bones; ///<

        static const unsigned int m_maxBones;
    };


    template<typename T>
    Skeleton<T> interpolate(const Skeleton<T> &a, const Skeleton<T> &b, const T &t);


} // namespace plt


#include "Skeleton.inl"


#endif // PLASTIC_SKELETON_HPP




////////////////////////////////////////////////////////////
/// \class plt::Skeleton
///
/// \todo Avoir plusieurs RootBone?
/// \todo Implémenter l'interpolation des squelettes
/// \todo Imposer un nombre limite de bones?
///
////////////////////////////////////////////////////////////

