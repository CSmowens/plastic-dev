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
#include "ExampleApplication.hpp"

#include "../loaders/LoaderImageTGA.hpp"

#include "../gl/GLCheck.hpp"

#include <Plastic/OpenGL.hpp>

#include <iostream>

namespace plt
{
    ExampleApplication::ExampleApplication
    (
    ) :
    m_camera( Camera<float>(vec3(8,8,8), quat(), 70, 1, 0.1, 1200) )    // A supprimer
    {

    }


    ExampleApplication::~ExampleApplication
    (
    )
    {

    }


    void ExampleApplication::mainLoop
    (
    )
    {
        while (m_window.isOpen())
        {
            plt::Event event;
            while (m_window.getEvent(event))
            {
                if ((event.Type == plt::Event::KeyPressed) && (event.Key.Code == plt::Key::Escape))
                    m_window.close();

                if (event.Type == plt::Event::Closed)
                    m_window.close();

                if ((event.Type == plt::Event::KeyPressed) && (event.Key.Code == plt::Key::Tab))
                {
                    m_consoleEnable = !m_consoleEnable;
                    m_console.enable(m_consoleEnable);
                }

                if(m_consoleEnable)
                {
                    if ((event.Type == plt::Event::KeyPressed))
                    {
                        if((event.Key.Code >= plt::Key::A) && (event.Key.Code <= plt::Key::Z))
                        {
                            char ch = event.Key.Code;

                            if( m_window.getInput().isKeyDown(Key::LShift) || m_window.getInput().isKeyDown(Key::RShift) )
                                ch = std::toupper(ch);

                            m_console.sendChar(ch);
                        }

                        if((event.Key.Code == plt::Key::Back))
                            m_console.sendChar('\b');

                        if((event.Key.Code == plt::Key::Return))
                            m_console.sendChar('\n');
                    }
                }


                if (event.Type == plt::Event::Resized)
                {
                    unsigned int width = m_window.getWidth();
                    unsigned int height = m_window.getHeight();

                    m_camera.setRatio( static_cast<float>(width)/static_cast<float>(height) );

                    GLCheck( glViewport(0,0,width,height) );
                }
            }


            if(!m_consoleEnable)
                processEvents(); 

            m_window.setActive();

            onUpdate();
            onRender();

            m_window.display();
        }

    }


    void ExampleApplication::run
    (
    )
    {
        m_window.create(VideoMode(800, 640, 32), "ExampleApplication : Plastic Engine", ContextSettings(24, 0, 0));
        m_window.setFramerateLimit(60);


        m_mediaManager.registerLoader<Image>( std::make_shared<LoaderImageTGA>(), "tga");


        m_camera = Camera<float>( vec3(8,8,8), quat(), 70, static_cast<float>(m_window.getWidth())/static_cast<float>(m_window.getHeight()), 0.1, 1200);
        m_camera.setTarget( vec3(0,0,0) );
        //m_camera.setFixedYaw(true);


        std::function<std::string()> functionPrint = Print(helpMessage());
        m_console.registerCommand("help", functionPrint);
        m_consoleEnable = false;

        onInitialize();

        mainLoop();
    }


} // namespace plt
