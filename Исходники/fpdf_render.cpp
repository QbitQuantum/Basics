void CPDF_RenderContext::Render(CFX_RenderDevice* pDevice,
                                const CPDF_PageObject* pStopObj,
                                const CPDF_RenderOptions* pOptions,
                                const CFX_Matrix* pLastMatrix) {
  int count = m_Layers.GetSize();
  for (int j = 0; j < count; j++) {
    pDevice->SaveState();
    Layer* pLayer = m_Layers.GetDataPtr(j);
    if (pLastMatrix) {
      CFX_Matrix FinalMatrix = pLayer->m_Matrix;
      FinalMatrix.Concat(*pLastMatrix);
      CPDF_RenderStatus status;
      status.Initialize(this, pDevice, pLastMatrix, pStopObj, nullptr, nullptr,
                        pOptions, pLayer->m_pObjectHolder->m_Transparency,
                        FALSE, nullptr);
      status.RenderObjectList(pLayer->m_pObjectHolder, &FinalMatrix);
      if (status.m_Options.m_Flags & RENDER_LIMITEDIMAGECACHE) {
        m_pPageCache->CacheOptimization(status.m_Options.m_dwLimitCacheSize);
      }
      if (status.m_bStopped) {
        pDevice->RestoreState(false);
        break;
      }
    } else {
      CPDF_RenderStatus status;
      status.Initialize(this, pDevice, nullptr, pStopObj, nullptr, nullptr,
                        pOptions, pLayer->m_pObjectHolder->m_Transparency,
                        FALSE, nullptr);
      status.RenderObjectList(pLayer->m_pObjectHolder, &pLayer->m_Matrix);
      if (status.m_Options.m_Flags & RENDER_LIMITEDIMAGECACHE) {
        m_pPageCache->CacheOptimization(status.m_Options.m_dwLimitCacheSize);
      }
      if (status.m_bStopped) {
        pDevice->RestoreState(false);
        break;
      }
    }
    pDevice->RestoreState(false);
  }
}