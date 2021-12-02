#ifndef ELEVEN_DIRECTXRENDERER_H
#define ELEVEN_DIRECTXRENDERER_H

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dxgi.lib")

#include <wrl.h>
#include <wrl/client.h>

#include <xstring>

#define INITGUID

#ifndef _WIN32
#include <wsl/winadapter.h>
#endif

#include <DirectXMath.h>

#include "../../vendor/dxsdk/include/dxcore.h"
#include "../../vendor/dxsdk/include/d3d11.h"
#include "../../vendor/dxsdk/include/dxgi1_2.h"
#include "../../vendor/dxsdk/include/dxgi1_4.h"
#include "../../vendor/dxsdk/include/dxgi1_6.h"

#include "../../vendor/dxsdk/include/d3d12.h"
#include "../../vendor/dxsdk/include/d3dx12.h"
#include "../../vendor/dxsdk/include/dxguids.h"

#include "IRendererAPI.h"

using Microsoft::WRL::ComPtr;

class DirectXRenderer : public IRendererAPI
{
public:
    DirectXRenderer(const u32 width, const u32 height);
    ~DirectXRenderer();
    void Render() override;
    void Setup(Eleven::Vertex* vertices) override;

    // custom methods

    void OnInit();
    void OnUpdate();
    void OnRender();
    void OnDestroy();

    // Samples override the event handlers to handle specific messages.
    virtual void OnKeyDown(UINT8 /*key*/)   {}
    virtual void OnKeyUp(UINT8 /*key*/)     {}

    UINT GetWidth() const           { return m_width; }
    UINT GetHeight() const          { return m_height; }
    const WCHAR* GetTitle() const   { return m_title.c_str(); }

    void ParseCommandLineArgs(_In_reads_(argc) WCHAR* argv[], int argc);

protected:
    std::wstring GetAssetFullPath(LPCWSTR assetName);

    void GetHardwareAdapter(
            _In_ IDXGIFactory1* pFactory,
            _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter,
            bool requestHighPerformanceAdapter = false);

    void SetCustomWindowText(LPCWSTR text);

    // Viewport dimensions.
    UINT m_width;
    UINT m_height;
    float _aspectRatio;

    // Adapter info.
    bool m_useWarpDevice;
private:
    HWND _hwnd;
    HDC _dc;

    // Root assets path.
    std::wstring _assetsPath;

    // Window title.
    std::wstring m_title;

    static const UINT FrameCount = 2;
    D3D12_VIEWPORT m_Viewport;

    // Pipeline objects.
    ComPtr<IDXGISwapChain3> m_swapChain;
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
    ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    ComPtr<ID3D12CommandQueue> m_commandQueue;
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    ComPtr<ID3D12PipelineState> m_pipelineState;
    ComPtr<ID3D12GraphicsCommandList> m_commandList;
    UINT m_rtvDescriptorSize;

    // Debug layer
    ID3D12Debug* d3d12debug = nullptr;

    // vertex buffer
    ID3D12Resource* m_pVertexBuffer = nullptr;

    // Synchronization objects.
    UINT m_frameIndex;
    HANDLE m_fenceEvent;
    ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue;

    void LoadPipeline();
    void LoadAssets();
    void PopulateCommandList();
    void WaitForPreviousFrame();

    void CreateVertexBuffer();
};


#endif //ELEVEN_DIRECTXRENDERER_H
