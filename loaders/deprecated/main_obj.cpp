#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include <stdexcept>

#include <Plastic/Core/Vector3.hpp>
#include <Plastic/Core/Vector2.hpp>

#include <boost/program_options.hpp>


namespace po = boost::program_options;



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
}



/// \todo Ajouter le numero de la line où une erreur de lecture se produit
/// \todo Changer la fonction find, pour une méthode membre
/// \todo Stocker les mtl
/// \todo Charger toutes geometry



void doIndentation(unsigned int x)
{
    for(unsigned int i(0); i<x; ++i)
        std::cout << " ";
}


int main(int argc, char *argv[])
{
    try
    {
        std::string fileIn, fileOut;



        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("version", "print version string")
            ("in", po::value<std::string>(&fileIn), "input file")
            ("out", po::value<std::string>(&fileOut)->default_value("out"), "output file")
            ("tangent", "compute local space for each vertex")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) 
        {
            std::cout << desc << std::endl;
            return EXIT_SUCCESS;
        }


        if (vm.count("version")) 
        {
            std::cout << "mesh_converter version 0.1" << std::endl;
            return EXIT_SUCCESS;
        }


        if (!vm.count("in"))
            throw std::runtime_error("No input file specified");


        if (vm.count("tangent")) 
            throw std::runtime_error("Error : compute of local space non supported");













        std::vector< plt::vec3 > positions;
        std::vector< plt::vec3 > normals;
        std::vector< plt::vec2 > textures;

        std::vector< plt::uvec3 > indices;


        std::ifstream in(fileIn.c_str(), std::ios::in);

		if(!in.is_open())
            throw std::runtime_error("Impossible to open : " + fileIn);



        plt::vec3 v, vn;
        plt::vec2 vt;

        plt::uvec3 f[3];


        
        std::string line;    



	    while(std::getline(in, line))
        {
            const char *str = line.c_str();

            switch(str[0])
            {
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
                    }
                    break;

                
                case 'f':
                    if( std::sscanf(str + 1, "%u/%u/%u %u/%u/%u %u/%u/%u", &f[0].x, &f[0].y, &f[0].z, &f[1].x, &f[1].y, &f[1].z, &f[2].x, &f[2].y, &f[2].z) != 9)
                        throw std::runtime_error("Error when read a index");     

                    for(auto i(0); i<3; ++i)
                        indices.push_back(f[i]);
                    break;
            }
        }

        in.close();












        std::vector< unsigned int > gl_indices;
        std::vector< float > gl_vertex;

        unsigned int index = 0;


        std::map< plt::uvec3, unsigned int > tmp;


        for(unsigned int i(0); i<indices.size(); ++i)
        {
            auto it = std::find(indices.begin(), indices.begin()+i, indices.at(i));

            if(it != indices.begin()+i)
            {
                auto iter = tmp.find(indices.at(i));

                    if(iter == tmp.end())
                        throw std::runtime_error("Error"); // Just a little verification, but it's impossible  

                gl_indices.push_back(  (*iter).second );
            }
            
            else
            {
                gl_vertex.push_back( positions.at(indices.at(i).x - 1).x );
                gl_vertex.push_back( positions.at(indices.at(i).x - 1).y );
                gl_vertex.push_back( positions.at(indices.at(i).x - 1).z );

                gl_vertex.push_back( textures.at(indices.at(i).y - 1).x );
                gl_vertex.push_back( textures.at(indices.at(i).y - 1).y );

                gl_vertex.push_back( normals.at(indices.at(i).z - 1).x );
                gl_vertex.push_back( normals.at(indices.at(i).z - 1).y );
                gl_vertex.push_back( normals.at(indices.at(i).z - 1).z );


                tmp.insert( std::make_pair(indices.at(i), index) );

                gl_indices.push_back(index);
                index++;
            }
        }









        std::ofstream out(fileOut.c_str(), std::ios::out | std::ios::trunc);

		if(!out.is_open())
            throw std::runtime_error("Impossible to open : " + fileOut);



        out << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
        out << "<Plastic_Mesh version=\"0.1\">" << std::endl;

        out << "    <VertexDeclaration>" << std::endl;

        out << "        <VertexElement semantic=\"VES_POSITION\" type=\"VET_FLOAT3\"/>" << std::endl;
        out << "        <VertexElement semantic=\"VES_TEXCOORD0\" type=\"VET_FLOAT2\"/>" << std::endl;
        out << "        <VertexElement semantic=\"VES_NORMAL\" type=\"VET_FLOAT3\"/>" << std::endl;

        out << "    </VertexDeclaration>" << std::endl;
        out << "    <Vertex vertexCount=\"" << index << "\">" << std::endl;

        std::copy(gl_vertex.begin(), gl_vertex.end(), std::ostream_iterator<float>(out, " ")); 

        out << std::endl;
        out << "    </Vertex>" << std::endl;





        out << "    <Index indexCount=\"" << gl_indices.size() << "\">" << std::endl;

        std::copy(gl_indices.begin(), gl_indices.end(), std::ostream_iterator<unsigned int>(out, " ")); 

        out << std::endl;
        out << "    </Index>" << std::endl;

        out << "</Plastic_Mesh>" << std::endl;

        out.close();
    }

    catch(const std::exception &e)
    {
        std::cout << "Exception cautch : " << e.what() << std::endl;
    }


    return EXIT_SUCCESS;
}
