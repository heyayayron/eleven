#ifndef ELEVEN_VULKANRENDERER_H
#define ELEVEN_VULKANRENDERER_H

#include "../../Core/Core.h"

#include "../../Core/linmath.h"
#include "../Abstractions/IRendererAPI.h"
#include "../Abstractions/IShader.h"

namespace el
{
    class VulkanRenderer : public IRendererAPI
    {
    private:
        std::unique_ptr<IShader<u32>> _basicShader = nullptr;
    public:
        VulkanRenderer(const u32 width, const u32 height);
        ~VulkanRenderer();
        void Render() override;
        void Setup(Vertex *vertices) override;
    };
}

#endif //ELEVEN_VULKANRENDERER_H
