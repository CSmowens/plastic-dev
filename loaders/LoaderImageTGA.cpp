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
#include "LoaderImageTGA.hpp"

#include <Plastic/Core/Assert.hpp>
#include <Plastic/Core/PixelFormat.hpp>
#include <Plastic/Core/Types.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace plt
{
    namespace
    {

#pragma pack(push, 1)
        struct HeaderTGA
        {
            uint8    id_lenght;          // Size of image id
            uint8    colormap_type;      // 1 is has a colormap
            uint8    image_type;         // Compression type

            uint16   cm_first_entry;     // Colormap origin
            uint16   cm_length;          // Colormap length
            uint8    cm_size;            // Colormap size

            uint16   x_origin;           // Bottom left x coord origin
            uint16   y_origin;           // Bottom left y coord origin

            uint16   width;              // Picture width (in pixels)
            uint16   height;             // Picture height (in pixels)

            uint8    pixel_depth;        // Bits per pixel: 8, 16, 24 or 32
            uint8    image_descriptor;   // 24 bits = 0x00; 32 bits = 0x80 
        };
#pragma pack(pop)

        static_assert( sizeof(HeaderTGA) == 18, "sizeof(HeaderTGA) must be 18" );



        void readTGA8bitsIndex(std::stringstream &buffer, std::vector<ubyte> &pixels, const std::vector<ubyte> &colormap, const uvec2 &dim)
        {        
            for(auto i = 0u; i<dim.x*dim.y; ++i)
            {
                ubyte c;

                // Read and convert BGR to RGB
                buffer.read(reinterpret_cast<char*>(&c), sizeof(ubyte));

                pixels[(i * 3) + 2] = colormap[(c * 3) + 0];
                pixels[(i * 3) + 1] = colormap[(c * 3) + 1];
                pixels[(i * 3) + 0] = colormap[(c * 3) + 2];
            }
        }


        void readTGA16bits(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {
            for(auto i = 0u; i<dim.x*dim.y; ++i)
            {
                uint16 color = 0;

                // Read and convert BGR to RGB
                buffer.read(reinterpret_cast<char*>(&color), sizeof(uint16)); 

                pixels[(i * 3) + 0] = static_cast<ubyte>( ( (color & 0x7C00) >> 10) << 3 );
                pixels[(i * 3) + 1] = static_cast<ubyte>( ( (color & 0x03E0) >>  5) << 3 );
                pixels[(i * 3) + 2] = static_cast<ubyte>( ( (color & 0x001F) >>  0) << 3 );
            }
        }

   
        void readTGA24bits(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {
            for(auto i = 0u; i<dim.x*dim.y; ++i)
            {
                ubyte c[3];

                // Read and convert BGR to RGB
                buffer.read(reinterpret_cast<char*>(&c[0]), 3*sizeof(ubyte));

                pixels[(i * 3) + 2] = c[0];
                pixels[(i * 3) + 1] = c[1];
                pixels[(i * 3) + 0] = c[2];
            }
        }


        void readTGA32bits(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {
            for(auto i = 0u; i<dim.x*dim.y; ++i)
            {
                ubyte c[4];

                // Read and convert BGRA to RGBA
                buffer.read(reinterpret_cast<char*>(&c[0]), 4*sizeof(ubyte));

                pixels[(i * 4) + 2] = c[0];
                pixels[(i * 4) + 1] = c[1];
                pixels[(i * 4) + 0] = c[2];
                pixels[(i * 4) + 3] = c[3];
            }
        }


        void readTGAgray8bits(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {
            buffer.read(reinterpret_cast<char*>(&pixels[0]), sizeof(ubyte)*dim.x*dim.y);
        }


        void readTGAgray16bits(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {
            buffer.read(reinterpret_cast<char*>(&pixels[0]), 2*sizeof(ubyte)*dim.x*dim.y);
        }


        void readTGA8bitsIndexRLE(std::stringstream &buffer, std::vector<ubyte> &pixels, const std::vector<ubyte> &colormap, const uvec2 &dim)
        {        

        }


        void readTGA16bitsRLE(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {
            
        }

   
        void readTGA24bitsRLE(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {
            for(auto i = 0u; i<dim.x*dim.y; ++i)
            {
                ubyte packet_header;
                buffer.read(reinterpret_cast<char*>(&packet_header), sizeof(ubyte));

                unsigned int size = 1 + (packet_header & 0x7f);

                if (packet_header & 0x80)
                {
                    // Run-length packet
                    ubyte c[3];
                    buffer.read(reinterpret_cast<char*>(&c[0]), 3*sizeof(ubyte));

                    for (auto j = 0u; j < size; ++j)
                    {
                        pixels[i*3 + j*3 + 0] = c[2];
                        pixels[i*3 + j*3 + 1] = c[1];
                        pixels[i*3 + j*3 + 2] = c[0];
                    }
                }

                else
                {
                    // Non run-length packet
                    ubyte c[3];

                    for (auto j = 0u; j < size; ++j)
                    {
                        buffer.read(reinterpret_cast<char*>(&c[0]), 3*sizeof(ubyte));

                        pixels[i*3 + j*3 + 0] = c[2];
                        pixels[i*3 + j*3 + 1] = c[1];
                        pixels[i*3 + j*3 + 2] = c[0];
                    }
                }

                i+=size-1;
            }
        }


        void readTGA32bitsRLE(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {
           
        }


        void readTGAgray8bitsRLE(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {

        }


        void readTGAgray16bitsRLE(std::stringstream &buffer, std::vector<ubyte> &pixels, const uvec2 &dim)
        {

        }

    } // namespace






    std::shared_ptr<Image> LoaderImageTGA::loadFromFile
    (
        const std::string& filename
    )
    {
        std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);

        std::stringstream buffer; 
        buffer << in.rdbuf();

        in.close();


        HeaderTGA header;
        buffer.read(reinterpret_cast<char*>(&header), sizeof(HeaderTGA));



        uvec2 dimensions;
        dimensions.x = static_cast<unsigned int>(header.width);
        dimensions.y = static_cast<unsigned int>(header.height);
        unsigned int pixel_depth = static_cast<unsigned int>(header.pixel_depth);

        PixelFormat format;




        switch( header.image_type )
        {
            case 3:     // 8 bits grayscale
            case 11:    // 8 bits grayscale (RLE)
            {
                if( pixel_depth == 8 )
                {
                    throw std::runtime_error("No supported format L8");
                    //format = PixelFormat::L8;       
                }         

                else // 16 bits
                {
                    throw std::runtime_error("No supported format L8A8");
                    //format = PixelFormat::L8A8;       
                }         

                break;
            }

            case 1:     // 8 bits color index
            case 2:     // 16-24-32 bits BVR
            case 9:     // 8 bits color index (RLE)
            case 10:    // 16-24-32 bits BVR (RLE) 
            {
                // Pictures 8 et 16 bits will be convert in 24 bits
                if( pixel_depth <= 24 ) 
                     format = PixelFormat::RGB8U; 
              
                else // 32 bits
                    format = PixelFormat::RGBA8U;                

                break;
            }


            default:
                throw std::runtime_error("Unsupported tga format");
                break;
        }


        std::vector<ubyte> pixels(dimensions.x * dimensions.y * PixelFormatInfos::getInfos(format).size(), 0xD3);
        std::vector<ubyte> colormap;

        buffer.seekg(static_cast<int>(header.id_lenght), std::ios::cur);

        if (header.colormap_type)
        {
            colormap.resize( header.cm_length * (header.cm_size >> 3) );

            buffer.read(reinterpret_cast<char*>(&colormap[0]), header.cm_length * (header.cm_size >> 3));
        }


        // Read image data
        switch (header.image_type)
        {
            case 0:
                throw std::runtime_error("No data in image");
                break;

            case 1:
                readTGA8bitsIndex(buffer, pixels, colormap, dimensions);
                break;

            case 2:
                switch (header.pixel_depth)
                {
                    case 16:
                        readTGA16bits(buffer, pixels, dimensions);
                        break;

                    case 24:
                        readTGA24bits(buffer, pixels, dimensions);
                        break;

                    case 32:
                        readTGA32bits(buffer, pixels, dimensions);
                        break;
                }

                break;

            case 3:
                if (header.pixel_depth == 8)
                    readTGAgray8bits(buffer, pixels, dimensions);

                else 
                    readTGAgray16bits(buffer, pixels, dimensions);

                break;

            case 9:
                readTGA8bitsIndexRLE(buffer, pixels, colormap, dimensions);
                break;

            case 10:
                switch (header.pixel_depth)
                {
                    case 16:
                        readTGA16bitsRLE(buffer, pixels, dimensions);
                        break;

                    case 24:
                        readTGA24bitsRLE(buffer, pixels, dimensions);
                        break;

                    case 32:
                        readTGA32bitsRLE(buffer, pixels, dimensions);
                        break;
                }

                break;

            case 11:
                if (header.pixel_depth == 8)
                    readTGAgray8bitsRLE(buffer, pixels, dimensions);

                else 
                    readTGAgray16bitsRLE(buffer, pixels, dimensions);

                break;
     
            default:
                throw std::runtime_error("Unknow tga data");
                break;
        }



        Image img(1);
        img[0] = Image::ImageLevel(dimensions, format, &pixels[0]);

        return std::make_shared<Image>(img);
    }


} // namespace plt
