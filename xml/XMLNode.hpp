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


#ifndef PLASTIC_XMLNODE_HPP
#define PLASTIC_XMLNODE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "XMLAttribute.hpp"

#include <vector>
#include <string>
#include <memory>

namespace plt
{

    enum XMLNodeType
    {
        ROOT,
        PROLOGUE,
        ELEMENT,
        TEXT,
        UNDEFINED
    };


    class XMLNode
    {
        public:
            XMLNode();
            XMLNode(const XMLNode &node) = default;
            XMLNode(XMLNodeType type, const std::shared_ptr<XMLNode> &parent, const std::string &data);

            XMLNode& operator=(const XMLNode &node) = default;

            std::size_t childsCount() const;
            std::size_t attribsCount() const;

            const std::shared_ptr<XMLNode>& getChild(std::size_t index) const;
            const std::string& getData() const;
            const std::shared_ptr<XMLNode>& getParent() const;
            const XMLAttribute& getAttribute(std::size_t index) const;

            XMLNodeType getType() const;

            void addChild(const std::shared_ptr<XMLNode> &child);
            void addData(const std::string &data);
            void addAttribute(const XMLAttribute &attribute);
            void addAttributes(const std::vector< XMLAttribute > &attributes);

        private:
            XMLNodeType m_type;
            std::shared_ptr<XMLNode> m_parent;
            std::vector< std::shared_ptr<XMLNode> > m_childs;
            std::string m_data;
            std::vector< XMLAttribute > m_attributes;
    };

} //namespace plt


#endif // PLASTIC_XMLNODE_HPP


