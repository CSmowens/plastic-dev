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



////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "XMLObject.hpp"

#include <fstream>
#include <stdexcept>
#include <locale>

namespace plt
{
    XMLObject::XMLObject(const std::string& path)
    :
    m_path(path)
    {
        m_root = std::make_shared<XMLNode>(ROOT, std::make_shared<XMLNode>(), "Root");
    }


    void XMLObject::parse()
    {
        std::ifstream file(m_path.c_str(), std::ios::in);
        if(!file)
            throw std::runtime_error("Error opening xml file");

        std::locale loc;
        std::shared_ptr<XMLNode> current(m_root);
        std::vector< XMLAttribute > attributes;

        bool commentaire(false);
        int nbBaliseOuverte(0);

        std::string line;

        while (std::getline(file, line))
        {
            auto it = line.begin();
            while (it != line.end())
            {
                // SUPPRIME ESPACE AVANT BALISE OU TEXTE
                if ((*it) == ' ' || (*it) == '\t' || (*it) == '\r' || (*it) == '\n')
                {
                    ++it;
                }


                // BALISE PROLOGUE <? ?>
                else if ((*it) == '<' && (*(it+1)) == '?')
                {
                    it += 2;
                    std::string baliseName;
                    while (std::isalnum(*it, loc))
                    {
                         baliseName += (*it);
                        ++it;
                    }

                    while ((*it) == ' ') // Attributs : nom="valeur"
                    {
                        ++it;

                        std::string attributName;
                        while (std::isalnum(*it, loc) || (*it) == '_') // Variable attributName
                        {
                            attributName += (*it);
                            ++it;
                        }

                        if ((*it) != '=' || (*(it+1)) != '"')
                            throw std::runtime_error("Variable attributName non suivi de =\"");

                        it += 2;

                        std::string attributValeur;
                        while ((*it) != '"' && it != line.end()) // Variable attributValeur
                        {
                            attributValeur += (*it);
                            ++it;
                        }

                        if ((*it) != '"')
                            throw std::runtime_error("Variable attributValeur non suivi de \"");

                        ++it;
                        attributes.push_back( XMLAttribute(attributName, attributValeur) );
                    }

                    if ((*it) == '?' && (*(it+1)) == '>')
                    {
                        auto newNode = std::make_shared<XMLNode>(PROLOGUE, current, baliseName);
                        current->addChild( newNode );

                        newNode->addAttributes( attributes );
                        attributes.clear();

                        it +=2;
                    }
                    else
                        throw std::runtime_error("Error name prologue balise");
                }


                // BALISE COMMENTAIRE <!-- -->
                else if (commentaire || ( (*it) == '<' && (*(it+1)) == '!' && (*(it+2)) == '-' && (*(it+3)) == '-' ) )
                {
                    if (!commentaire)
                    {
                        it += 4;
                    }
                    commentaire = true;

                    while ( ( (*it) != '-' || (*(it+1)) != '-' || (*(it+2)) != '>' ) && it != line.end() )
                    {
                        ++it;
                    }
        
                    if (it == line.end())
                    {
                        commentaire = true;
                    }
                    else
                    {
                        it += 3;
                        commentaire = false;
                    }
                }


                // BALISE OUVRANTE ELEMENT <balise> (ou <balise/>)
                else if ((*it) == '<' && (*(it+1)) != '/')
                {
                    ++it;
                    std::string baliseName;
                    while (std::isalnum(*it, loc) || (*it) == '_')
                    {
                        baliseName += (*it);
                        ++it;
                    }

                    while ((*it) == ' ') // Attributs : nom="valeur"
                    {
                        ++it;

                        std::string attributName;
                        while (std::isalnum(*it, loc) || (*it) == '_') // Variable attributName
                        {
                            attributName += (*it);
                            ++it;
                        }

                        if ((*it) != '=' || (*(it+1)) != '"')
                            throw std::runtime_error("Variable attributName non suivi de =\"");

                        it += 2;

                        std::string attributValeur;
                        while ((*it) != '"' && it != line.end()) // Variable attributValeur
                        {
                            attributValeur += (*it);
                            ++it;
                        }

                        if ((*it) != '"')
                            throw std::runtime_error("Variable attributValeur non suivi de \"");

                        ++it;

                        attributes.push_back( XMLAttribute(attributName, attributValeur) );
                    }

                    if ((*it) == '>') // Balise ouvrante ELEMENT normale
                    {
                        auto newNode = std::make_shared<XMLNode>(ELEMENT, current, baliseName);
                        current->addChild( newNode );
                        current = newNode;

                        current->addAttributes( attributes );
                        attributes.clear();

                        ++it;
                        ++nbBaliseOuverte;
                    }

                    else if ((*it) == '/' && (*(it+1)) == '>') // Balise ELEMENT simple
                    {
                        auto newNode = std::make_shared<XMLNode>(ELEMENT, current, baliseName);
                        current->addChild( newNode );

                        newNode->addAttributes( attributes );
                        attributes.clear();

                        it +=2;
                    }

                    else
                        throw std::runtime_error("Error name open balise");
                }


                // BALISE FERMANTE </balise>
                else if ((*it) == '<' && (*(it+1)) == '/' )
                {
                    it += 2;
                    std::string baliseName;
                    while ((*it) != '>')
                    {
                        if (!std::isalnum(*it, loc) && (*it) != '_')
                            throw std::runtime_error("Error name close balise");

                        baliseName += (*it);
                        ++it;
                    }
                    ++it;

                    if (nbBaliseOuverte-1 < 0)
                        throw std::runtime_error("Balise fermante seule");

                    if (baliseName != current->getData())
                        throw std::runtime_error("Balise fermante n'ayant pas le même nom que l'ouvrante");

                    current = current->getParent();
                    --nbBaliseOuverte;
                }


                // TEXTE ENTRE BALISE OUVRANTE ET FERMANTE
                else if ( (*it) != '<' && (*it) != '>')
                {
                    std::string texte;
                    while ( (*it) != '<' && (*it) != '>' && it != line.end() )
                    {
                        texte += (*it);
                        ++it;
                    }

                    bool haveList(false);

                    for (size_t i(0); i<current->childsCount(); ++i)
                    {
                        if (current->getChild(i)->getType() == TEXT)
                        {
                            haveList = true;
                            current->getChild(i)->addData(texte);
                            break;
                        }
                    }

                    if (!haveList)
                    {
                        auto newNode = std::make_shared<XMLNode>(ELEMENT, current, texte);
                        current->addChild( newNode );
                    }
                }

                // ERREUR
                else
                    throw std::runtime_error("Unknown xml symbol file");
            }
        }

        if (nbBaliseOuverte != 0)
            throw std::runtime_error("Il reste des balises ouvertes");
    }


    const std::shared_ptr<XMLNode>& XMLObject::getRoot
    (
    ) const
    {
        return m_root;
    }


    const std::string& XMLObject::getPath
    (
    ) const
    {
        return m_path;
    }

} // namespace plt


