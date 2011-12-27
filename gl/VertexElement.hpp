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


#ifndef PLASTIC_VERTEXELEMENT_HPP
#define PLASTIC_VERTEXELEMENT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/OpenGL.hpp>

#include "VertexElementSemantic.hpp"
#include "VertexElementType.hpp"

#include <vector>


namespace plt
{
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class VertexElement
    {

    public:
        VertexElement() = default;

        VertexElement(VertexElementSemantic semantic, VertexElementType type, std::size_t offset);

        
        VertexElementSemantic getSemantic() const;

        VertexElementType getType() const;

        std::size_t getOffset() const;

    private:
		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////   
        VertexElementSemantic m_semantic; ///< The meaning of the element 
        VertexElementType m_type; ///< The type of element
        std::size_t m_offset; ///< 
    };


    bool operator==(const VertexElement &u, const VertexElement &v);
    bool operator!=(const VertexElement &u, const VertexElement &v);

} // namespace plt


#endif // PLASTIC_VERTEXELEMENT_HPP




////////////////////////////////////////////////////////////
/// \class plt::VertexElement
///
/// \todo Faire des assertions pour protégés les fonctions size, count...
/// \todo Ajouter les types int, uint...
///
/// \warning If you modify the source code from VertexElementSemantic
/// or VertexElementType, modify the others statics elements
/// in the class.
///
////////////////////////////////////////////////////////////
