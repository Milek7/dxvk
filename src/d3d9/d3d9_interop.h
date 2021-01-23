#pragma once

#include "../dxgi/dxgi_interfaces.h"

namespace dxvk {

  class D3D9DeviceEx;

  class D3D9VkInterop : public ComObject<IDXGIVkInteropDevice> {

  public:

    D3D9VkInterop(D3D9DeviceEx* pDevice);
    ~D3D9VkInterop();

    ULONG STDMETHODCALLTYPE AddRef();

    ULONG STDMETHODCALLTYPE Release();

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                  riid,
            void**                  ppvObject);

    void STDMETHODCALLTYPE GetVulkanHandles(
            VkInstance*           pInstance,
            VkPhysicalDevice*     pPhysDev,
            VkDevice*             pDevice);

    void STDMETHODCALLTYPE GetSubmissionQueue(
            VkQueue*              pQueue,
            uint32_t*             pQueueFamilyIndex);

    void STDMETHODCALLTYPE TransitionSurfaceLayout(
            IDXGIVkInteropSurface*    pSurface,
      const VkImageSubresourceRange*  pSubresources,
            VkImageLayout             OldLayout,
            VkImageLayout             NewLayout);

    void STDMETHODCALLTYPE FlushRenderingCommands();

    void STDMETHODCALLTYPE LockSubmissionQueue();

    void STDMETHODCALLTYPE ReleaseSubmissionQueue();

  private:

    D3D9DeviceEx* m_device;

  };
}