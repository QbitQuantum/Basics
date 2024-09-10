void ProcessClearBE(DRAW_CONTEXT* pDC, uint32_t workerId, uint32_t macroTile, void* pUserData)
{
    SWR_CONTEXT* pContext           = pDC->pContext;
    HANDLE       hWorkerPrivateData = pContext->threadPool.pThreadData[workerId].pWorkerPrivateData;

    if (KNOB_FAST_CLEAR)
    {
        CLEAR_DESC*           pClear      = (CLEAR_DESC*)pUserData;
        SWR_MULTISAMPLE_COUNT sampleCount = pDC->pState->state.rastState.sampleCount;
        uint32_t              numSamples  = GetNumSamples(sampleCount);

        SWR_ASSERT(pClear->attachmentMask != 0); // shouldn't be here without a reason.

        RDTSC_BEGIN(BEClear, pDC->drawId);

        if (pClear->attachmentMask & SWR_ATTACHMENT_MASK_COLOR)
        {
            unsigned long rt   = 0;
            uint32_t      mask = pClear->attachmentMask & SWR_ATTACHMENT_MASK_COLOR;
            while (_BitScanForward(&rt, mask))
            {
                mask &= ~(1 << rt);

                HOTTILE* pHotTile =
                    pContext->pHotTileMgr->GetHotTile(pContext,
                                                      pDC,
                                                      hWorkerPrivateData,
                                                      macroTile,
                                                      (SWR_RENDERTARGET_ATTACHMENT)rt,
                                                      true,
                                                      numSamples,
                                                      pClear->renderTargetArrayIndex);

                // All we want to do here is to mark the hot tile as being in a "needs clear" state.
                pHotTile->clearData[0] = *(uint32_t*)&(pClear->clearRTColor[0]);
                pHotTile->clearData[1] = *(uint32_t*)&(pClear->clearRTColor[1]);
                pHotTile->clearData[2] = *(uint32_t*)&(pClear->clearRTColor[2]);
                pHotTile->clearData[3] = *(uint32_t*)&(pClear->clearRTColor[3]);
                pHotTile->state        = HOTTILE_CLEAR;
            }
        }

        if (pClear->attachmentMask & SWR_ATTACHMENT_DEPTH_BIT)
        {
            HOTTILE* pHotTile      = pContext->pHotTileMgr->GetHotTile(pContext,
                                                                  pDC,
                                                                  hWorkerPrivateData,
                                                                  macroTile,
                                                                  SWR_ATTACHMENT_DEPTH,
                                                                  true,
                                                                  numSamples,
                                                                  pClear->renderTargetArrayIndex);
            pHotTile->clearData[0] = *(uint32_t*)&pClear->clearDepth;
            pHotTile->state        = HOTTILE_CLEAR;
        }

        if (pClear->attachmentMask & SWR_ATTACHMENT_STENCIL_BIT)
        {
            HOTTILE* pHotTile = pContext->pHotTileMgr->GetHotTile(pContext,
                                                                  pDC,
                                                                  hWorkerPrivateData,
                                                                  macroTile,
                                                                  SWR_ATTACHMENT_STENCIL,
                                                                  true,
                                                                  numSamples,
                                                                  pClear->renderTargetArrayIndex);

            pHotTile->clearData[0] = pClear->clearStencil;
            pHotTile->state        = HOTTILE_CLEAR;
        }

        RDTSC_END(BEClear, 1);
    }
    else
    {
        // Legacy clear
        CLEAR_DESC* pClear = (CLEAR_DESC*)pUserData;
        RDTSC_BEGIN(BEClear, pDC->drawId);

        if (pClear->attachmentMask & SWR_ATTACHMENT_MASK_COLOR)
        {
            uint32_t clearData[4];
            clearData[0] = *(uint32_t*)&(pClear->clearRTColor[0]);
            clearData[1] = *(uint32_t*)&(pClear->clearRTColor[1]);
            clearData[2] = *(uint32_t*)&(pClear->clearRTColor[2]);
            clearData[3] = *(uint32_t*)&(pClear->clearRTColor[3]);

            PFN_CLEAR_TILES pfnClearTiles = gClearTilesTable[KNOB_COLOR_HOT_TILE_FORMAT];
            SWR_ASSERT(pfnClearTiles != nullptr);

            unsigned long rt   = 0;
            uint32_t      mask = pClear->attachmentMask & SWR_ATTACHMENT_MASK_COLOR;
            while (_BitScanForward(&rt, mask))
            {
                mask &= ~(1 << rt);

                pfnClearTiles(pDC,
                              hWorkerPrivateData,
                              (SWR_RENDERTARGET_ATTACHMENT)rt,
                              macroTile,
                              pClear->renderTargetArrayIndex,
                              clearData,
                              pClear->rect);
            }
        }

        if (pClear->attachmentMask & SWR_ATTACHMENT_DEPTH_BIT)
        {
            uint32_t clearData[4];
            clearData[0]                  = *(uint32_t*)&pClear->clearDepth;
            PFN_CLEAR_TILES pfnClearTiles = gClearTilesTable[KNOB_DEPTH_HOT_TILE_FORMAT];
            SWR_ASSERT(pfnClearTiles != nullptr);

            pfnClearTiles(pDC,
                          hWorkerPrivateData,
                          SWR_ATTACHMENT_DEPTH,
                          macroTile,
                          pClear->renderTargetArrayIndex,
                          clearData,
                          pClear->rect);
        }

        if (pClear->attachmentMask & SWR_ATTACHMENT_STENCIL_BIT)
        {
            uint32_t clearData[4];
            clearData[0]                  = pClear->clearStencil;
            PFN_CLEAR_TILES pfnClearTiles = gClearTilesTable[KNOB_STENCIL_HOT_TILE_FORMAT];

            pfnClearTiles(pDC,
                          hWorkerPrivateData,
                          SWR_ATTACHMENT_STENCIL,
                          macroTile,
                          pClear->renderTargetArrayIndex,
                          clearData,
                          pClear->rect);
        }

        RDTSC_END(BEClear, 1);
    }
}