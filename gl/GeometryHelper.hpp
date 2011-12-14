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


#ifndef PLASTIC_GEOMETRYHELPER_HPP
#define PLASTIC_GEOMETRYHELPER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Geometry.hpp"
#include "SubGeometry.hpp"

namespace plt
{
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class GeometryHelper
    {
    public:
        static std::shared_ptr<SubGeometry> createRightHandCoordinateSystem();

        static std::shared_ptr<SubGeometry> createFullScreenQuad();

        static std::shared_ptr<SubGeometry> createFrustum(float fovy, float ratio, float near, float far);

        static std::shared_ptr<SubGeometry> createBox(float width, float height, float depth, bool normals, bool texCoords);

        static std::shared_ptr<SubGeometry> createSphere(float radius, unsigned int segmentsCount, unsigned int ringsCount, bool normals, bool texCoords);





        static std::shared_ptr<Geometry> addSpaceTangent(const std::shared_ptr<Geometry> &geom, bool withTangents, bool withBiNormals);

        static std::shared_ptr<Geometry> createGeometryWithNormalsOnly(const std::shared_ptr<Geometry> &geom, bool onlyNormals);
    };

} // namespace plt


#endif // PLASTIC_GEOMETRYHELPER_HPP




////////////////////////////////////////////////////////////
/// \class plt::GeometryHelper
///
///
////////////////////////////////////////////////////////////
