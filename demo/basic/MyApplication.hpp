#ifndef PLASTIC_MYAPPLICATION_HPP
#define PLASTIC_MYAPPLICATION_HPP

#include "../../app/ExampleApplication.hpp"

#include "../../gl/Geometry.hpp"
#include "../../gl/HardwareBuffer.hpp"
#include "../../gl/Program.hpp"

#include <memory>

namespace plt
{
    class MyApplication : public ExampleApplication
    {
    public:
        MyApplication();

        virtual ~MyApplication();

    private:
        virtual void processEvents();

        virtual void onInitialize();

        virtual void onUpdate();

        virtual void onRender() const;

        virtual std::string helpMessage() const;
        

        std::shared_ptr<Geometry> m_geomRepere;

        std::shared_ptr<Program> m_programRepere;

        std::shared_ptr<HardwareBuffer> m_hbRepere;
    };

} // namespace plt


#endif // PLASTIC_MYAPPLICATION_HPP
