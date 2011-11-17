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
    BezierCurve<T>::BezierCurve
    (
    )
    {
        std::vector<KeyFrame> keys;
        keys.push_back( KeyFrame { vec3(-5, 0, 0), vec3(-6, 0, 5) } );
        keys.push_back( KeyFrame { vec3(5, 0, 0), vec3(6, 0, -5) } );
        
        addControlsPoints(keys);
    }


    template<typename T>
    BezierCurve<T>::BezierCurve
    (
        const std::vector<KeyFrame> &keys
    )
    {
        addControlsPoints(keys);
    }


    template<typename T>
    BezierCurve<T>::~BezierCurve
    (
    )
    {

    }


    template<typename T>
    void BezierCurve<T>::addControlsPoints
    (
        const std::vector<KeyFrame> &keys
    )
    {
        for(auto it=keys.begin(); it!=keys.end(); ++it)
            m_keyFrames.push_back(*it);
    }


    template<typename T>
    tvec3<T> BezierCurve<T>::getInterpoledPosition
    (
        const T &time
    ) const
    {
        PLASTIC_ASSERT(time >= T(0) && time <= T(1) );

        PLASTIC_ASSERT( m_keyFrames.size() > 1 );



        T timePerCurve = T(1) / static_cast<T>(m_keyFrames.size()-1);

        std::size_t i = static_cast<std::size_t>( time / timePerCurve);



        T begin = static_cast<T>(i)*timePerCurve;
        T end = static_cast<T>(i+1)*timePerCurve;
    
        T interpolationFactor = (time-begin) / (end-begin);



        T t = interpolationFactor;
        T u = T(1) - interpolationFactor;

        // To ensure continuity
        tvec3<T> newTangent = T(2)*m_keyFrames[i].position - m_keyFrames[i].tangent;

        return m_keyFrames[i].position * u * u * u +
               newTangent * 3 * t * u * u +
               m_keyFrames[i+1].tangent * 3 * t * t * u  +
               m_keyFrames[i+1].position * t * t * t;
    }

} // namespace plt
