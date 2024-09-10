void BackendSingleSample(DRAW_CONTEXT*        pDC,
                         uint32_t             workerId,
                         uint32_t             x,
                         uint32_t             y,
                         SWR_TRIANGLE_DESC&   work,
                         RenderOutputBuffers& renderBuffers)
{
    RDTSC_BEGIN(BESingleSampleBackend, pDC->drawId);
    RDTSC_BEGIN(BESetup, pDC->drawId);

    void* pWorkerData = pDC->pContext->threadPool.pThreadData[workerId].pWorkerPrivateData;

    const API_STATE& state = GetApiState(pDC);

    BarycentricCoeffs coeffs;
    SetupBarycentricCoeffs(&coeffs, work);

    SWR_PS_CONTEXT             psContext;
    const SWR_MULTISAMPLE_POS& samplePos = state.rastState.samplePositions;
    SetupPixelShaderContext<T>(&psContext, samplePos, work);

    uint8_t *pDepthBuffer, *pStencilBuffer;
    SetupRenderBuffers(psContext.pColorBuffer,
                       &pDepthBuffer,
                       &pStencilBuffer,
                       state.colorHottileEnable,
                       renderBuffers);

    RDTSC_END(BESetup, 1);

    psContext.vY.UL     = _simd_add_ps(vULOffsetsY, _simd_set1_ps(static_cast<float>(y)));
    psContext.vY.center = _simd_add_ps(vCenterOffsetsY, _simd_set1_ps(static_cast<float>(y)));

    const simdscalar dy = _simd_set1_ps(static_cast<float>(SIMD_TILE_Y_DIM));

    for (uint32_t yy = y; yy < y + KNOB_TILE_Y_DIM; yy += SIMD_TILE_Y_DIM)
    {
        psContext.vX.UL     = _simd_add_ps(vULOffsetsX, _simd_set1_ps(static_cast<float>(x)));
        psContext.vX.center = _simd_add_ps(vCenterOffsetsX, _simd_set1_ps(static_cast<float>(x)));

        const simdscalar dx = _simd_set1_ps(static_cast<float>(SIMD_TILE_X_DIM));

        for (uint32_t xx = x; xx < x + KNOB_TILE_X_DIM; xx += SIMD_TILE_X_DIM)
        {
#if USE_8x2_TILE_BACKEND
            const bool useAlternateOffset = ((xx & SIMD_TILE_X_DIM) != 0);
#endif
            simdmask coverageMask = work.coverageMask[0] & MASK;

            if (coverageMask)
            {
                if (state.depthHottileEnable && state.depthBoundsState.depthBoundsTestEnable)
                {
                    static_assert(KNOB_DEPTH_HOT_TILE_FORMAT == R32_FLOAT,
                                  "Unsupported depth hot tile format");

                    const simdscalar z =
                        _simd_load_ps(reinterpret_cast<const float*>(pDepthBuffer));

                    const float minz = state.depthBoundsState.depthBoundsTestMinValue;
                    const float maxz = state.depthBoundsState.depthBoundsTestMaxValue;

                    coverageMask &= CalcDepthBoundsAcceptMask(z, minz, maxz);
                }

                if (T::InputCoverage != SWR_INPUT_COVERAGE_NONE)
                {
                    const uint64_t* pCoverageMask =
                        (T::InputCoverage == SWR_INPUT_COVERAGE_INNER_CONSERVATIVE)
                            ? &work.innerCoverageMask
                            : &work.coverageMask[0];

                    generateInputCoverage<T, T::InputCoverage>(
                        pCoverageMask, psContext.inputMask, state.blendState.sampleMask);
                }

                RDTSC_BEGIN(BEBarycentric, pDC->drawId);

                CalcPixelBarycentrics(coeffs, psContext);

                CalcCentroid<T, true>(
                    &psContext, samplePos, coeffs, work.coverageMask, state.blendState.sampleMask);

                // interpolate and quantize z
                psContext.vZ = vplaneps(
                    coeffs.vZa, coeffs.vZb, coeffs.vZc, psContext.vI.center, psContext.vJ.center);
                psContext.vZ = state.pfnQuantizeDepth(psContext.vZ);

                RDTSC_END(BEBarycentric, 1);

                // interpolate user clip distance if available
                if (state.backendState.clipDistanceMask)
                {
                    coverageMask &= ~ComputeUserClipMask(state.backendState.clipDistanceMask,
                                                         work.pUserClipBuffer,
                                                         psContext.vI.center,
                                                         psContext.vJ.center);
                }

                simdscalar vCoverageMask   = _simd_vmask_ps(coverageMask);
                simdscalar depthPassMask   = vCoverageMask;
                simdscalar stencilPassMask = vCoverageMask;

                // Early-Z?
                if (T::bCanEarlyZ)
                {
                    RDTSC_BEGIN(BEEarlyDepthTest, pDC->drawId);
                    depthPassMask = DepthStencilTest(&state,
                                                     work.triFlags.frontFacing,
                                                     work.triFlags.viewportIndex,
                                                     psContext.vZ,
                                                     pDepthBuffer,
                                                     vCoverageMask,
                                                     pStencilBuffer,
                                                     &stencilPassMask);
                    AR_EVENT(EarlyDepthStencilInfoSingleSample(_simd_movemask_ps(depthPassMask),
                                                               _simd_movemask_ps(stencilPassMask),
                                                               _simd_movemask_ps(vCoverageMask)));
                    RDTSC_END(BEEarlyDepthTest, 0);

                    // early-exit if no pixels passed depth or earlyZ is forced on
                    if (state.psState.forceEarlyZ || !_simd_movemask_ps(depthPassMask))
                    {
                        DepthStencilWrite(&state.vp[work.triFlags.viewportIndex],
                                          &state.depthStencilState,
                                          work.triFlags.frontFacing,
                                          psContext.vZ,
                                          pDepthBuffer,
                                          depthPassMask,
                                          vCoverageMask,
                                          pStencilBuffer,
                                          stencilPassMask);

                        if (!_simd_movemask_ps(depthPassMask))
                        {
                            goto Endtile;
                        }
                    }
                }

                psContext.sampleIndex = 0;
                psContext.activeMask  = _simd_castps_si(vCoverageMask);

                // execute pixel shader
                RDTSC_BEGIN(BEPixelShader, pDC->drawId);
                state.psState.pfnPixelShader(GetPrivateState(pDC), pWorkerData, &psContext);
                RDTSC_END(BEPixelShader, 0);

                // update stats
                UPDATE_STAT_BE(PsInvocations, _mm_popcnt_u32(_simd_movemask_ps(vCoverageMask)));
                AR_EVENT(PSStats(psContext.stats.numInstExecuted));

                vCoverageMask = _simd_castsi_ps(psContext.activeMask);

                // late-Z
                if (!T::bCanEarlyZ)
                {
                    RDTSC_BEGIN(BELateDepthTest, pDC->drawId);
                    depthPassMask = DepthStencilTest(&state,
                                                     work.triFlags.frontFacing,
                                                     work.triFlags.viewportIndex,
                                                     psContext.vZ,
                                                     pDepthBuffer,
                                                     vCoverageMask,
                                                     pStencilBuffer,
                                                     &stencilPassMask);
                    AR_EVENT(LateDepthStencilInfoSingleSample(_simd_movemask_ps(depthPassMask),
                                                              _simd_movemask_ps(stencilPassMask),
                                                              _simd_movemask_ps(vCoverageMask)));
                    RDTSC_END(BELateDepthTest, 0);

                    if (!_simd_movemask_ps(depthPassMask))
                    {
                        // need to call depth/stencil write for stencil write
                        DepthStencilWrite(&state.vp[work.triFlags.viewportIndex],
                                          &state.depthStencilState,
                                          work.triFlags.frontFacing,
                                          psContext.vZ,
                                          pDepthBuffer,
                                          depthPassMask,
                                          vCoverageMask,
                                          pStencilBuffer,
                                          stencilPassMask);
                        goto Endtile;
                    }
                }
                else
                {
                    // for early z, consolidate discards from shader
                    // into depthPassMask
                    depthPassMask = _simd_and_ps(depthPassMask, vCoverageMask);
                }

                uint32_t statMask  = _simd_movemask_ps(depthPassMask);
                uint32_t statCount = _mm_popcnt_u32(statMask);
                UPDATE_STAT_BE(DepthPassCount, statCount);

                // output merger
                RDTSC_BEGIN(BEOutputMerger, pDC->drawId);
#if USE_8x2_TILE_BACKEND
                OutputMerger8x2(pDC,
                                psContext,
                                psContext.pColorBuffer,
                                0,
                                &state.blendState,
                                state.pfnBlendFunc,
                                vCoverageMask,
                                depthPassMask,
                                state.psState.renderTargetMask,
                                useAlternateOffset,
                                workerId);
#else
                OutputMerger4x2(pDC,
                                psContext,
                                psContext.pColorBuffer,
                                0,
                                &state.blendState,
                                state.pfnBlendFunc,
                                vCoverageMask,
                                depthPassMask,
                                state.psState.renderTargetMask,
                                workerId,
                                workerId);
#endif

                // do final depth write after all pixel kills
                if (!state.psState.forceEarlyZ)
                {
                    DepthStencilWrite(&state.vp[work.triFlags.viewportIndex],
                                      &state.depthStencilState,
                                      work.triFlags.frontFacing,
                                      psContext.vZ,
                                      pDepthBuffer,
                                      depthPassMask,
                                      vCoverageMask,
                                      pStencilBuffer,
                                      stencilPassMask);
                }
                RDTSC_END(BEOutputMerger, 0);
            }

        Endtile:
            RDTSC_BEGIN(BEEndTile, pDC->drawId);

            work.coverageMask[0] >>= (SIMD_TILE_Y_DIM * SIMD_TILE_X_DIM);
            if (T::InputCoverage == SWR_INPUT_COVERAGE_INNER_CONSERVATIVE)
            {
                work.innerCoverageMask >>= (SIMD_TILE_Y_DIM * SIMD_TILE_X_DIM);
            }

#if USE_8x2_TILE_BACKEND
            if (useAlternateOffset)
            {
                DWORD    rt;
                uint32_t rtMask = state.colorHottileEnable;
                while (_BitScanForward(&rt, rtMask))
                {
                    rtMask &= ~(1 << rt);
                    psContext.pColorBuffer[rt] +=
                        (2 * KNOB_SIMD_WIDTH * FormatTraits<KNOB_COLOR_HOT_TILE_FORMAT>::bpp) / 8;
                }
            }
#else
            DWORD rt;
            uint32_t rtMask = state.colorHottileEnable;
            while (_BitScanForward(&rt, rtMask))
            {
                rtMask &= ~(1 << rt);
                psContext.pColorBuffer[rt] +=
                    (KNOB_SIMD_WIDTH * FormatTraits<KNOB_COLOR_HOT_TILE_FORMAT>::bpp) / 8;
            }
#endif
            pDepthBuffer += (KNOB_SIMD_WIDTH * FormatTraits<KNOB_DEPTH_HOT_TILE_FORMAT>::bpp) / 8;
            pStencilBuffer +=
                (KNOB_SIMD_WIDTH * FormatTraits<KNOB_STENCIL_HOT_TILE_FORMAT>::bpp) / 8;

            RDTSC_END(BEEndTile, 0);

            psContext.vX.UL     = _simd_add_ps(psContext.vX.UL, dx);
            psContext.vX.center = _simd_add_ps(psContext.vX.center, dx);
        }

        psContext.vY.UL     = _simd_add_ps(psContext.vY.UL, dy);
        psContext.vY.center = _simd_add_ps(psContext.vY.center, dy);
    }