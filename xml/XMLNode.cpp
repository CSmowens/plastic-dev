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


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "XMLNode.hpp"

#include <stdexcept>

namespace plt
{
    XMLNode::XMLNode
    (
    ) : 
    m_type(UNDEFINED)
    {
    }


    XMLNode::XMLNode
    (
        XMLNodeType type, 
        const std::shared_ptr<XMLNode> &parent, 
        const std::string &data
    ) : 
    m_type(type),
    m_parent(parent), 
    m_data(data)
    {
    }


    void XMLNode::addChild
    (
        const std::shared_ptr<XMLNode> &child
    )
    {
        m_childs.push_back(child);
    }


    void XMLNode::addData
    (
        const std::string &data
    )
    {
        m_data += data;
    }


    void XMLNode::addAttribute
    (
        const XMLAttribute &attribute
    )
    {
        m_attributes.push_back(attribute);
    }

    void XMLNode::addAttributes
    (
        const std::vector< XMLAttribute > &attributes
    )
    {
        for(std::size_t i(0); i<attributes.size(); ++i)
            m_attributes.push_back( attributes[i] );
    }


    std::size_t XMLNode::childsCount
    (
    ) const
    {
        return m_childs.size();
    }


    std::size_t XMLNode::attribsCount
    (
    ) const
    {
        return m_attributes.size();
    }


    const std::string& XMLNode::getData
    (
    ) const
    {
        return m_data;
    }


    const std::shared_ptr<XMLNode>& XMLNode::getChild
    (
        std::size_t index
    ) const
    {
        if(index > m_childs.size())
            throw std::runtime_error("The child requested doesn't exist");

        return m_childs[index];
    }


    const std::shared_ptr<XMLNode>& XMLNode::getParent
    (
    ) const
    {
        return m_parent;
    }


    const XMLAttribute& XMLNode::getAttribute
    (
        std::size_t index
    ) const
    {
        if(index > m_attributes.size())
            throw std::runtime_error("The attribute requested doesn't exist");

        return m_attributes[index];
    }


    XMLNodeType XMLNode::getType
    (
    ) const
    {
        return m_type;
    }

} // namespace plt


