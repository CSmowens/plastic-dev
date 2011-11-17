////////////////////////////////////////////////////////////
// Plastic, an open source high performance realtime 3D engine.
// Copyright (C) 2010-2011 Hiairrassary Victor
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////


#ifndef PLASTIC_XMLATTRIBUTE_HPP
#define PLASTIC_XMLATTRIBUTE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <utility>

namespace plt
{

    class XMLAttribute
    {
        public:
            XMLAttribute() = default;
            XMLAttribute(const std::string &name, const std::string &value);
            XMLAttribute(const XMLAttribute &) = default;

            XMLAttribute& operator=(const XMLAttribute &) = default;

            const std::string& getName() const;
            const std::string& getValue() const;

        private:
            std::pair<std::string, std::string> m_attribute;
    };

} //namespace plt


#endif // PLASTIC_XMLATTRIBUTE_HPP


