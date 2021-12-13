#include "VulkanRenderer.h"

namespace el
{
    VulkanRenderer::VulkanRenderer(const el::u32 width, const el::u32 height)
    {

    }

    VulkanRenderer::~VulkanRenderer()
    {
        glfwDestroyWindow(_gfxContext);
        delete _gfxContext;
    }

    void VulkanRenderer::Setup(Vertex *vertices)
    {

    }

    void VulkanRenderer::Render()
    {

    }
}
