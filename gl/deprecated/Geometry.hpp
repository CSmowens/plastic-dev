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


#ifndef PLASTIC_GEOMETRY_HPP
#define PLASTIC_GEOMETRY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "VertexDeclaration.hpp"
#include "Skeleton.hpp"
#include "Bone.hpp"

#include <Plastic/Core/AxisAlignedBox.hpp>
#include <Plastic/Core/Types.hpp>
#include <Plastic/Core/Vector2.hpp>
#include <Plastic/Core/Vector3.hpp>
#include <Plastic/OpenGL.hpp>

#include <algorithm>
#include <vector>
#include <cstring>
#include <memory>


namespace plt
{	
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class Geometry
    {

    public:
        Geometry();

        template<typename T, typename U>
        Geometry(PrimitiveType primType, const VertexDeclaration &declaration, const std::vector<T> &vertexData, const std::vector<U> &indexData);

        template<typename U>
        Geometry(PrimitiveType primType, const VertexDeclaration &declaration, unsigned int vertexCount, const std::vector<ubyte> &vertexData, const std::vector<U> &indexData);





        void addSubGeometry(const std::shared_ptr<Geometry> &sub);

        const std::shared_ptr<Geometry>& operator[](std::size_t index) const;

        bool hasSubGeometry() const;

        std::size_t subGeometryCount() const;





        const VertexDeclaration& getVertexDeclaration() const;

        PrimitiveType getPrimitiveType() const;

        const void* getVertexRawData() const;

        const void* getIndexRawData() const;

        unsigned int getVertexCount() const;

        unsigned int getIndexCount() const;

        GLenum getIndexType() const;

        unsigned int getSizeOfIndexType() const;






        static std::shared_ptr<Geometry> createRightHandCoordinateSystem();

        static std::shared_ptr<Geometry> createFrustum(float fovy, float ratio, float zNear, float zFar);

        static std::shared_ptr<Geometry> createSphere(float radius, unsigned int segmentsCount, unsigned int ringsCount, bool normals, bool texCoords);

        static std::shared_ptr<Geometry> createGeometryWithSpaceTangent(const std::shared_ptr<Geometry> &geom, bool withTangents, bool withBiNormals);

        static std::shared_ptr<Geometry> createGeometryWithNormalsOnly(const std::shared_ptr<Geometry> &geom, bool onlyNormals);

    private:
        void checkStaticGeometryValidity() const;

        GLenum computeIndexType(std::size_t size);


		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////   
        PrimitiveType m_primitiveType;

        VertexDeclaration m_declaration;

        //AxisAlignedBox m_box;

        unsigned int m_vertexCount;
        unsigned int m_indexCount;

        GLenum m_indexType;        
        unsigned int m_sizeOfIndexType;

        std::vector<ubyte> m_vertexData;
        std::vector<ubyte> m_indexData; 


        std::vector< std::shared_ptr<Geometry> > m_geometry;
    };


    unsigned int vertexPerPrimitiveCount(PrimitiveType primitive);

} // namespace plt


#include "Geometry.inl"


#endif // PLASTIC_GEOMETRY_HPP




////////////////////////////////////////////////////////////
/// \class plt::Geometry
///
///
/// \todo Rajouter l'optimisation d'index
/// \todo Ajouter la construction depuis une geometry dynamique
/// \todo Voir pour le calcul de l'aabb ou dans le constructeur
/// \todo Pour la création de sphere pouvoir changer le type des index (template ou typedef interne)
/// \todo Pour le constructeur de geometry dynamique, pouvoir rajouter espace tangent, soit avec juste un vecteur soit avec binormal ET tangent
/// \todo Factoriser les constructeurs pour éviter les redondances!
/// \todo Constructeur par défaut
/// \todo Merger les aabbs
/// \todo Ajouter une fonction qui renvoie une geometrie avec des lines representants les normales
///
////////////////////////////////////////////////////////////

