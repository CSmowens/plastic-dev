#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include <stdexcept>

#include <Plastic/Core.hpp>

#include <boost/program_options.hpp>


namespace po = boost::program_options;



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
            throw plt::UnsupportedException("Compute of local space");







        std::ifstream in(fileIn.c_str(), std::ios::in);

		if(!in.is_open())
            throw std::runtime_error("Impossible to open : " + fileIn);







        int nbJoints = 0;
        int nbMeshes = 0;



        std::string line;


	    while(std::getline(in, line))
        {
            std::string token;

            std::istringstream iss(line);
            iss >> token;
            
            //std::cout << token << std::endl;


            if(token == "//" || token == "commandline") 
                continue;


            else if(token == "MD5Version") 
            {
                int version;
                iss >> version;

                if(version != 10) 
                    throw plt::Exception("The file isn't a .md5 version 10");
            }


            else if(token == "numJoints") 
            {
                iss >> nbJoints;

                if(nbJoints < 1)
                    throw plt::Exception("The file haven't got joints");
            }


            else if(token == "numMeshes") 
            {
                iss >> nbMeshes;

                if(nbMeshes < 1)
                    throw plt::Exception("The file haven't got meshes");
            }


            else if(token == "joints")
            {
                std::string nothing, name, line2;
                int parent = 0;
                plt::vec3 v;
                plt::quat q;

                for(auto i(0); i<nbJoints; ++i)
                {
                    std::getline(in, line2);

                    std::istringstream iss2(line2);

                    if( !(iss2 >> name >> parent >> nothing >> v.x >> v.y >> v.z >> nothing >> nothing >> q.x >> q.y >> q.z) )
                        throw plt::Exception("Invalid bone");


                    std::cout << name << " " << parent << " " << v.x << " " << v.y << " " << v.z << " " << q.x << " " << q.y << " " << q.z << std::endl;  
                      


                    // Stocké le bone en cours dans le squelette
                }

                std::cout << std::endl;

                std::getline(in, line2); // Pour enlever la ligne avec "}"
            }



            else if(token == "mesh")
            {
                std::string token2;

                do
                {
                    token2 = "";

                    std::string line2;
                    
                    std::getline(in, line2);
            
                    std::istringstream iss2(line2);
                    iss2 >> token2;


                    if(token2 == "//" || token2 == "shader" || token2 == "}")
                        continue;


                    else if(token2 == "numverts")
                    {
                        int nbVerts(0);

                        if( !(iss2 >> nbVerts) )
                            throw plt::Exception("Invalid numverts");



                        for(auto i(0); i<nbVerts; ++i)
                        {
                            std::string line3;                                

                            std::getline(in, line3);


                            
                            std::string nothing;
                            plt::vec2 tex;
                            int index(0), starWeight(0), countWeight(0);
                            

                            std::istringstream iss3(line3);

                            if( !(iss3 >> nothing >> index >> nothing >> tex.x >> tex.y >> nothing >> starWeight >> countWeight) )
                                throw plt::Exception("Invalid vert");

                            //std::cout << index << " " << tex.x << " " << tex.y << " " << starWeight << " " << countWeight << std::endl;
                        }

                    }



                    else if(token2 == "numtris")
                    {
                        int nbTris(0);

                        if( !(iss2 >> nbTris) )
                            throw plt::Exception("Invalid numtris");


                        for(auto i(0); i<nbTris; ++i)
                        {
                            std::string line3;                                

                            std::getline(in, line3);

                            std::string nothing;
                            plt::uvec3 index;
                            int trisIndex(0);
                            

                            std::istringstream iss3(line3);

                            if( !(iss3 >> nothing >> trisIndex >> index.x >> index.y >> index.z) )
                                throw plt::Exception("Invalid tris");

                            //std::cout << trisIndex << " " << index.x << " " << index.y << " " << index.z << std::endl;
                        }

                    }



                    else if(token2 == "numweights")
                    {
                        int nbWeights(0);

                        if( !(iss2 >> nbWeights) )
                            throw plt::Exception("Invalid numverts");


                        for(auto i(0); i<nbWeights; ++i)
                        {
                            std::string line3;                                

                            std::getline(in, line3);




                            std::string nothing;
                            plt::vec3 pos;
                            int weightIndex(0);
                            float joint(0), bias(0);
                            

                            std::istringstream iss3(line3);

                            if( !(iss3 >> nothing >> weightIndex >> joint >> bias >> nothing >> pos.x >> pos.y >> pos.z) )
                                throw plt::Exception("Invalid weight");

                            //std::cout << weightIndex << " " << joint << " " << bias << " " << pos.x << " " << pos.y << " " << pos.z << std::endl;
                        }

                    }


                    

                } while(token2 != "}");



                // Maintenant on peut stocker le mesh


            }


            // A rajouter une fois que les joints et meshes seront chargé,
            // sinon on a des erreurs sur "shader", "tri", "weight", etc. 
            //
            //else
                //throw plt::Exception("Invalid argument in file " + fileIn);
        }

        in.close();













        std::ofstream out(fileOut.c_str(), std::ios::out | std::ios::trunc);

		if(!out.is_open())
            throw std::runtime_error("Impossible to open : " + fileOut);



        out.close();

    }

    catch(const std::exception &e)
    {
        std::cout << "Exception cautch : " << e.what() << std::endl;
    }


    return 0;
}
