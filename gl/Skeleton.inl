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


namespace plt
{
    template<typename T>
    const unsigned int Skeleton<T>::m_maxBones = 60;





    template<typename T>
    inline Skeleton<T>::Skeleton
    (
    ) :
    m_haveRootBone(false)
    {

    }

    template<typename T>
    inline void Skeleton<T>::addBone
    (
        int parent,
        const tvec3<T> &position, 
        const tquat<T> &orientation
    )
    {   
        if(bonesCount + 1 > m_maxBones)
            throw std::runtime_error("The skeleton have too much bones");


        if(parent == -1)
        {
            if(m_haveRootBone)
                throw std::runtime_error("The skeleton have already a root bone");

            m_bones.push_back( Bone<T>(parent, position, orientation) );
            m_haveRootBone = true;
        }


        else if(parent > -1)
        {
            if(!m_haveRootBone)
                throw std::runtime_error("The skeleton haven't got a root bone");

            if(parent >= static_cast<int>(m_bones.size()) )
                throw std::runtime_error("The skeleton haven't got the bone");

            m_bones.push_back( Bone<T>(parent, position, orientation) );
        }


        else
            throw std::runtime_error("An parent < -1 is an invalid param");
    }


    template<typename T>
    inline const Bone<T>& Skeleton<T>::operator[]
    (
        std::size_t i
    ) const
    {
        PLASTIC_ASSERT( i<bonesCount() );

        return m_bones[i];
    }


    template<typename T>
    inline std::size_t Skeleton<T>::bonesCount
    (
    ) const
    {
        return m_bones.size();
    }








    template<typename T>
    inline Skeleton<T> interpolate
    (
        const Skeleton<T> &a, 
        const Skeleton<T> &b, 
        const T &t
    )
    {        
        PLASTIC_ASSERT(t >= T(0) && t <= T(1) );

        PLASTIC_ASSERT(a.bonesCount() == b.bonesCount());
    }

} // namespace plt
