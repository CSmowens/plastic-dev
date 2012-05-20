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
#include "CPUInfoLinux.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include <unistd.h>

namespace plt
{
    CPUInfoLinux::CPUInfoLinux
    (
    ) :
    m_file("/proc/stat", std::ios::in),
    m_coreCount(0),
    m_lastLoads(0)
    {
        if(!m_file)
            throw std::runtime_error("Impossible to open /proc/stat file");

        m_coreCount = sysconf(_SC_NPROCESSORS_ONLN);

        m_clocks.resize(m_coreCount);
        m_lastLoads.resize(m_coreCount);



        std::cout << "Threads count : " << m_coreCount << std::endl;
    }


    unsigned int CPUInfoLinux::getCoreCount
    (
    ) const
    {
        return m_coreCount;
    }


    std::vector<float> CPUInfoLinux::getCPULoad
    (
    )
    {
        m_file.seekg(0, std::ios::beg);

        std::string junk;
        std::getline(m_file, junk);



        std::vector<float> loads(m_coreCount);

        for(unsigned int i(0); i<m_coreCount; ++i)
        {
            std::string str;
            std::getline(m_file, str);
            std::istringstream iss(str);

            unsigned int user(0), nice(0), system(0);

            iss >> junk >> user >> nice >> system;
            //std::cout << junk << std::endl; // Must contains cpuX

            loads[i] = (user + nice + system - m_lastLoads[i]) / m_clocks[i].getElapsedTime();

            m_clocks[i].reset();
            m_lastLoads[i] = user + nice + system;
        }

        return loads;
    }

} // namespace plt
