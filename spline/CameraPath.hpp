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


#ifndef PLASTIC_CAMERAPATH_HPP
#define PLASTIC_CAMERAPATH_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#define PLASTIC_DEBUG 1

#include "Spline.hpp"

#include <memory>
#include <utility>

namespace plt
{
    template<typename T>
    class CameraPath
    {
    public:
        CameraPath();

        CameraPath(const std::shared_ptr< Spline<T> > &splinePosition, const std::shared_ptr< Spline<T> > &splineTarget);

        CameraPath(const std::shared_ptr< Spline<T> > &splinePosition, const tvec3<T> &target);

        CameraPath(const tvec3<T> &position, const std::shared_ptr< Spline<T> > &splineTarget);

        CameraPath(const tvec3<T> &position, const tvec3<T> &target);

        void setPositionPath(const std::shared_ptr< Spline<T> > &splinePosition);

        void setPositionPath(const tvec3<T> &position);

        void setTargetPath(const std::shared_ptr< Spline<T> > &splineTarget);

        void setTargetPath(const tvec3<T> &target);

        void setAnimationLoop(bool loop);

        std::pair< tvec3<T>, tvec3<T> > getInterpoledCameraInfos(const T &time);
        
    private:
        std::shared_ptr< Spline<T> > m_splinePosition;
        std::shared_ptr< Spline<T> > m_splineTarget;

        tvec3<T> m_position;
        tvec3<T> m_target;

        bool m_useDynamicPosition;
        bool m_useDynamicTarget;

        bool m_useAnimationLoop;
    };

} // namespace plt


#include "CameraPath.inl"


#endif // PLASTIC_CAMERAPATH_HPP




////////////////////////////////////////////////////////////
/// \class plt::CameraPath
///
/// \todo Retirer PLASTIC_DEBUG
/// \todo Si on tourne en boucle verifier si le début et fin des splines Pos et Target correspondent (si on utilise les splines!!)
///
////////////////////////////////////////////////////////////

