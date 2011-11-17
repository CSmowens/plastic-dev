#include <iostream>

#include "MyApplication.hpp"

using namespace plt;

int main() 
{
    try
    {
        MyApplication app;

        app.run();
    }

    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
