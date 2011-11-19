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
#include "MyApplication.hpp"

#include "MyConsoleView.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>


namespace
{
    std::string loadFile(std::string const &filename)
    {
        std::string text;

        std::ifstream stream(filename.c_str(), std::ios::in);

        if(!stream.is_open())
            throw std::runtime_error(filename + " file doesn't exist");

        std::string line;

        while(std::getline(stream, line))
            text += '\n' + line;

        return text;
    } 
}



namespace plt
{
    MyApplication::MyApplication
    (
    ) : ExampleApplication()
    {

    }


    MyApplication::~MyApplication
    (
    )
    {

    }


    void MyApplication::onInitialize
    (
    )
    {
        m_console.setView( std::make_shared<MyConsoleView>() );

        glClearColor(0.f, 0.f, 0.f, 0.f);

        glEnable(GL_DEPTH_TEST);

        std::cout << glGetString(GL_VERSION) << std::endl;



        m_geomRepere = std::make_shared<Geometry>();
        m_geomRepere->addSubGeometry( Geometry::createRightHandCoordinateSystem() );


        std::vector<std::shared_ptr<Shader>> shaders;
        shaders.push_back( std::make_shared<Shader>(ShaderType::Vertex, loadFile("repere.vert")) );
        shaders.push_back( std::make_shared<Shader>(ShaderType::Fragment, loadFile("repere.frag")) );

        m_programRepere = std::make_shared<Program>(shaders);


        m_hbRepere = std::make_shared<HardwareBuffer>(m_geomRepere, m_programRepere);
    }


    void MyApplication::processEvents
    (
    )
    {

    }


    void MyApplication::onUpdate
    (
    )
    {
        m_camera.setPosition( vec3(3, 3, 3) );
        m_camera.setTarget( vec3(0, 0, 0) );
        m_camera.update();
    }


    void MyApplication::onRender
    (
    ) const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        m_programRepere->bind();
        m_programRepere->setParameter("WorldViewProjMatrix", m_camera.getViewProjMatrix());

        m_hbRepere->bind();
        m_hbRepere->draw();
    }


    std::string MyApplication::helpMessage
    (
    ) const
    {
        return "Welcome in first Plastic Engine sample!";
    }

} // namespace plt
