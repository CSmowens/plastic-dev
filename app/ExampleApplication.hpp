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

#ifndef PLASTIC_EXAMPLEAPPLICATION_HPP
#define PLASTIC_EXAMPLEAPPLICATION_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Gui.hpp>
#include <Plastic/Ressource.hpp>
#include <Plastic/Graphics.hpp>

#include "../console/Console.hpp"

#include <string>

namespace plt
{
    class ExampleApplication
    {
    public:
        ExampleApplication();

        virtual ~ExampleApplication();

        void run();

    protected:
        MediaManager   m_mediaManager;
        Console        m_console;
        Window         m_window;
        Camera<float>  m_camera;


        struct Print
        {
        public:
            Print(std::string mess) : m_mess(mess)  {}            
        
            std::string operator()()  { return m_mess; }

        private:
            std::string m_mess;
        };


    private:
        bool m_consoleEnable;

        void mainLoop();

        virtual void onInitialize() = 0;

        virtual void processEvents() = 0;

        virtual void onUpdate() = 0;

        virtual void onRender() const = 0;

        virtual std::string helpMessage() const = 0;
    };

} // namespace plt


#endif // PLASTIC_EXAMPLEAPPLICATION_HPP




////////////////////////////////////////////////////////////
/// \class plt::ExampleApplication
///
/// \todo Sortir la camera de la liste d'initialisation quand elle aura un constructeur par défaut
/// \todo Envoyer l'input dans le processEvents ?
///
////////////////////////////////////////////////////////////
