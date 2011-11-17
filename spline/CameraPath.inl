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
    CameraPath<T>::CameraPath
    (
    ) :
    m_useAnimationLoop(false)
    {
        setPositionPath( tvec3<T>(3,3,3) );
        setTargetPath( tvec3<T>(0,0,0) );
    }


    template<typename T>
    CameraPath<T>::CameraPath
    (
        const std::shared_ptr< Spline<T> > &splinePosition, 
        const std::shared_ptr< Spline<T> > &splineTarget
    ) :
    m_useAnimationLoop(false)
    {
        setPositionPath(splinePosition);
        setTargetPath(splineTarget);
    }


    template<typename T>
    CameraPath<T>::CameraPath
    (
        const std::shared_ptr< Spline<T> > &splinePosition, 
        const tvec3<T> &target
    ) :
    m_useAnimationLoop(false)
    {
        setPositionPath(splinePosition);
        setTargetPath(target);
    }


    template<typename T>
    CameraPath<T>::CameraPath
    (
        const tvec3<T> &position, 
        const std::shared_ptr< Spline<T> > &splineTarget
    ) :
    m_useAnimationLoop(false)
    {
        setPositionPath(position);
        setTargetPath(splineTarget);
    }


    template<typename T>
    CameraPath<T>::CameraPath
    (
        const tvec3<T> &position, 
        const tvec3<T> &target
    ) : 
    m_useAnimationLoop(false)
    {
        setPositionPath(position);
        setTargetPath(target);
    }


    template<typename T>
    void CameraPath<T>::setPositionPath
    (
        const std::shared_ptr< Spline<T> > &splinePosition
    )
    {
        m_splinePosition = splinePosition;
        m_useDynamicPosition = true;
    }


    template<typename T>
    void CameraPath<T>::setPositionPath
    (
        const tvec3<T> &position
    )
    {
        m_position = position;
        m_useDynamicPosition = false;
    }


    template<typename T>
    void CameraPath<T>::setTargetPath
    (
        const std::shared_ptr< Spline<T> > &splineTarget
    )
    {
        m_splineTarget = splineTarget;
        m_useDynamicTarget = true;
    }


    template<typename T>
    void CameraPath<T>::setTargetPath
    (
        const tvec3<T> &target
    )
    {
        m_target = target;
        m_useDynamicTarget = false;
    }


    template<typename T>
    void CameraPath<T>::setAnimationLoop
    (
        bool loop
    )
    {
        m_useAnimationLoop = loop;
    }


    template<typename T>
    std::pair< tvec3<T>, tvec3<T> > CameraPath<T>::getInterpoledCameraInfos
    (
        const T &time
    )
    {
        T interpolationTime = time;

        if(m_useAnimationLoop)
            interpolationTime -= std::floor(time);

        PLASTIC_ASSERT(interpolationTime >= T(0) && interpolationTime <= T(1) );


        return std::make_pair(m_useDynamicPosition ? m_splinePosition->getInterpoledPosition(interpolationTime) : m_position, 
                              m_useDynamicTarget ? m_splineTarget->getInterpoledPosition(interpolationTime) : m_target );
    }

} // namespace plt
