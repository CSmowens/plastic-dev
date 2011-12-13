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
#include "LoaderGeometryOBJ.hpp"

#include "../gl/VertexBufferFormatted.hpp"
#include "../gl/IndexBufferFormatted.hpp"

#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <iostream>


namespace plt
{

    template<typename T>
    bool operator<(const tvec3<T> &v, const tvec3<T> &u) 
    {
        if(v.x == u.x)
        {
            if(v.y == u.y)
                return v.z < u.z;
            
            else       
                return v.y < u.y;
        }

        else 
            return v.x < u.x;
    }









    std::shared_ptr<Geometry> LoaderGeometryOBJ::loadFromFile
    (
        const std::string& filename
    )
    {
        std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);

        std::stringstream buffer; 
        buffer << in.rdbuf();

        in.close();




        std::shared_ptr<Geometry> geom = std::make_shared<Geometry>();

        bool firstSubGeometry = true;



        std::vector< vec3 > positions;
        std::vector< vec3 > normals;
        std::vector< vec2 > textures;

        std::vector< uvec3 > indices;


        std::map< plt::uvec3, unsigned int > indexMap;
        unsigned int index = 0;


        std::string line;    

        vec3 v, vn;
        vec2 vt;
        std::array<uvec3, 3> f;

	    while(std::getline(buffer, line))
        {
            const char *str = line.c_str();

            switch(str[0])
            {
                case '#':
                    break;
                    

                case 'g':
                    if(!firstSubGeometry)
                    {
                        //std::sort(indices.begin(), indices.end());
                        geom->addSubGeometry( createSubGeometry(indexMap, index, positions, normals, textures, indices) );

                        indices.clear();
                    }

                    else
                        firstSubGeometry = false;

                    break;


                case 's':
                    break;

                case 'o':
                    break;

                case ' ':
                    break;


                case 'u':
                    break;


                case 'v':
                    switch(str[1])
                    {
                        case ' ':
                            if( std::sscanf(str + 2, "%f %f %f", &v.x, &v.y, &v.z) != 3)
                                throw std::runtime_error("Error when read a vertex position");     

                            positions.push_back( v );
                            break;

                        case 'n':
                            if( std::sscanf(str + 2, "%f %f %f", &vn.x, &vn.y, &vn.z) != 3)
                                throw std::runtime_error("Error when read a vertex normal");     

                            normals.push_back( vn );
                            break;

                        case 't':
                            if( std::sscanf(str + 2, "%f %f", &vt.x, &vt.y) != 2)
                                throw std::runtime_error("Error when read a vertex texture");     

                            textures.push_back( vt );
                            break;

                        
                        default:
                            throw std::runtime_error("Error when declaring a vertex (position, normal, texture)");
                            break;
                    }
                    break;

                
                case 'f':
                    if( std::sscanf(str + 1, "%u/%u/%u %u/%u/%u %u/%u/%u", &f[0].x, &f[0].y, &f[0].z, &f[1].x, &f[1].y, &f[1].z, &f[2].x, &f[2].y, &f[2].z) != 9)
                        throw std::runtime_error("Error when read a index");     

                    for(auto i(0); i<3; ++i)
                        indices.push_back(f[i]);
                    break;


                default:
                    std::cout << "Unknow symbol : " << line << std::endl;
                    break;
            }
        }

        // On ajoute la géométrie en cours

        //std::sort(indices.begin(), indices.end());
        geom->addSubGeometry( createSubGeometry(indexMap, index, positions, normals, textures, indices) );

        return geom;
    }





    std::shared_ptr<SubGeometry> LoaderGeometryOBJ::createSubGeometry
    (
        std::map< plt::uvec3, unsigned int > &indexMap,
        unsigned int &index,
        const std::vector< vec3 > &positions,
        const std::vector< vec3 > &normals,
        const std::vector< vec2 > &textures,
        const std::vector< uvec3 > &indices
    )
    {
        std::vector< unsigned int > gl_indices;
        std::vector< VertexObj > gl_vertex;


        for(unsigned int i(0); i<indices.size(); ++i)
        {
            auto it = std::find(indices.begin(), indices.begin()+i, indices.at(i));

            if(it != indices.begin()+i)
            {
                auto iter = indexMap.find(indices.at(i));

                    if(iter == indexMap.end())
                        throw std::runtime_error("Error"); // Just a little verification, but it's impossible  

                gl_indices.push_back(  (*iter).second );
            }
            
            else
            {
                VertexObj  v{ positions.at(indices.at(i).x - 1),
                              textures.at(indices.at(i).y - 1),
                              normals.at(indices.at(i).z - 1)  };

                gl_vertex.push_back(v);


                indexMap.insert( std::make_pair(indices.at(i), index) );

                gl_indices.push_back(index);
                index++;
            }
        }


        VertexDeclaration dec;
        dec.add(VertexElementSemantic::Position, VertexElementType::Float3);
        dec.add(VertexElementSemantic::TexCoord0, VertexElementType::Float2);
        dec.add(VertexElementSemantic::Normal, VertexElementType::Float3);

        return std::make_shared<SubGeometry>(PrimitiveType::Triangles, 
                                             std::make_shared<VertexBufferFormatted<VertexObj>>(dec, std::move(gl_vertex)),
                                             std::make_shared<IndexBufferFormatted<unsigned int>>(std::move(gl_indices)) );
    }


} // namespace plt
