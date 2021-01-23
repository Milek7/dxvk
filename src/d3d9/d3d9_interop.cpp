#include "d3d9_interop.h"

#include "d3d9_device.h"

#include "../dxvk/dxvk_adapter.h"
#include "../dxvk/dxvk_device.h"
#include "../dxvk/dxvk_instance.h"

namespace dxvk {

  D3D9VkInterop::D3D9VkInterop(
          D3D9DeviceEx* pDevice)
  : m_device    (pDevice) { }


  D3D9VkInterop::~D3D9VkInterop() {

  }


  ULONG STDMETHODCALLTYPE D3D9VkInterop::AddRef() {
    return m_device->AddRef();
  }


  ULONG STDMETHODCALLTYPE D3D9VkInterop::Release() {
    return m_device->Release();
  }


  HRESULT STDMETHODCALLTYPE D3D9VkInterop::QueryInterface(
          REFIID                  riid,
          void**                  ppvObject) {
    return m_device->QueryInterface(riid, ppvObject);
  }


  void STDMETHODCALLTYPE D3D9VkInterop::GetVulkanHandles(
          VkInstance*           pInstance,
          VkPhysicalDevice*     pPhysDev,
          VkDevice*             pDevice) {
    auto device   = m_device->GetDXVKDevice();
    auto adapter  = device->adapter();
    auto instance = device->instance();

    if (pDevice != nullptr)
      *pDevice = device->handle();

    if (pPhysDev != nullptr)
      *pPhysDev = adapter->handle();

    if (pInstance != nullptr)
      *pInstance = instance->handle();
  }


  void STDMETHODCALLTYPE D3D9VkInterop::GetSubmissionQueue(
          VkQueue*              pQueue,
          uint32_t*             pQueueFamilyIndex) {
    auto device = m_device->GetDXVKDevice();
    DxvkDeviceQueue queue = device->queues().graphics;

    if (pQueue != nullptr)
      *pQueue = queue.queueHandle;

    if (pQueueFamilyIndex != nullptr)
      *pQueueFamilyIndex = queue.queueFamily;
  }


  void STDMETHODCALLTYPE D3D9VkInterop::TransitionSurfaceLayout(
          IDXGIVkInteropSurface*    pSurface,
    const VkImageSubresourceRange*  pSubresources,
          VkImageLayout             OldLayout,
          VkImageLayout             NewLayout) {
    m_device->TransitionSurfaceLayout(
      pSurface, pSubresources, OldLayout, NewLayout);
  }

  void STDMETHODCALLTYPE D3D9VkInterop::FlushRenderingCommands() {
    m_device->Flush();
    m_device->SynchronizeCsThread();
  }


  void STDMETHODCALLTYPE D3D9VkInterop::LockSubmissionQueue() {
    m_device->GetDXVKDevice()->lockSubmission();
  }


  void STDMETHODCALLTYPE D3D9VkInterop::ReleaseSubmissionQueue() {
    m_device->GetDXVKDevice()->unlockSubmission();
  }

}