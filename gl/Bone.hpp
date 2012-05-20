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


#ifndef PLASTIC_BONE_HPP
#define PLASTIC_BONE_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Core/Vector3.hpp>
#include <Plastic/Core/Quaternion.hpp>

#include <string>


namespace plt
{

    ////////////////////////////////////////////////////////////
    /// Represent a node for skeletal animation
    ////////////////////////////////////////////////////////////
    template<typename T>
    class Bone
    {  
    public:
        Bone(int parent, const tvec3<T> &position, const tquat<T> &orientation);

        int getParent() const;

        const tvec3<T>& getPosition() const;

        const tquat<T>& getOrientation() const;

    private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        int m_parent; ///< Parent
        tvec3<T> m_position; ///< Position
        tquat<T> m_orientation; ///< Orientation
    };


} // namespace plt


    #include "Bone.inl"


#endif // PLASTIC_BONE_HPP




////////////////////////////////////////////////////////////
/// \class plt::Bone
///
/// See Skeleton for more information about the principles 
/// behind skeletal animation. This class is a node in the 
/// joint hierarchy. Mesh vertices also have assignments
/// to bones to define how they move in relation to the 
/// skeleton.
///
/// \see Skeleton
///
////////////////////////////////////////////////////////////

