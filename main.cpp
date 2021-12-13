#include "src/Application.h"

int main()
{
    auto application = new el::Application(800, 600, el::EBackend::OPENGL);
    application->Run();
    return 0;
}
