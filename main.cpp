#include <iostream>
#include "src/Application.h"

int main()
{
    auto application = new Application(480, 320, EBackend::OPENGL);
    application->Run();
    return 0;
}
