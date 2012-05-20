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


#ifndef PLASTIC_BEZIERCURVE_HPP
#define PLASTIC_BEZIERCURVE_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Core/Vector3.hpp>

#include "Spline.hpp"

#include <stdexcept>
#include <vector>

namespace plt
{
    template<typename T>
    class BezierCurve : public Spline<T>
    {
    public:
        class KeyPoint
        {
        public:
            tvec3<T> position;
            tvec3<T> tangent;
        };

    public:
        BezierCurve();

        BezierCurve(const std::vector<KeyPoint> &keys);

        virtual ~BezierCurve();

        void addControlsPoints(const std::vector<KeyPoint> &keys);

        virtual tvec3<T> getInterpoledPosition(const T &time) const;

    private:
        std::vector<KeyPoint> m_keyPoints;
    };



} // namespace plt


#include "BezierCurve.inl"


#endif // PLASTIC_BEZIERCURVE_HPP




////////////////////////////////////////////////////////////
/// \class plt::BezierCurve
///
///
////////////////////////////////////////////////////////////

