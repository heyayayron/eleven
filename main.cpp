#include <iostream>
#include "src/Application.h"

int main()
{
    auto application = new Application(480, 320, EBackend::DIRECTX);
    application->Run();
    return 0;
}
