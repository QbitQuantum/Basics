void BackendSampleRate(DRAW_CONTEXT *pDC, uint32_t workerId, uint32_t x, uint32_t y, SWR_TRIANGLE_DESC &work, RenderOutputBuffers &renderBuffers)
{
    SWR_CONTEXT *pContext = pDC->pContext;

    AR_BEGIN(BESampleRateBackend, pDC->drawId);
    AR_BEGIN(BESetup, pDC->drawId);

    const API_STATE &state = GetApiState(pDC);

    BarycentricCoeffs coeffs;
    SetupBarycentricCoeffs(&coeffs, work);

    SWR_PS_CONTEXT psContext;
    const SWR_MULTISAMPLE_POS& samplePos = state.rastState.samplePositions;
    SetupPixelShaderContext<T>(&psContext, samplePos, work);

    uint8_t *pDepthBuffer, *pStencilBuffer;
    SetupRenderBuffers(psContext.pColorBuffer, &pDepthBuffer, &pStencilBuffer, state.colorHottileEnable, renderBuffers);

    AR_END(BESetup, 0);

    psContext.vY.UL = _simd_add_ps(vULOffsetsY, _simd_set1_ps(static_cast<float>(y)));
    psContext.vY.center = _simd_add_ps(vCenterOffsetsY, _simd_set1_ps(static_cast<float>(y)));

    const simdscalar dy = _simd_set1_ps(static_cast<float>(SIMD_TILE_Y_DIM));

    for (uint32_t yy = y; yy < y + KNOB_TILE_Y_DIM; yy += SIMD_TILE_Y_DIM)
    {
        psContext.vX.UL = _simd_add_ps(vULOffsetsX, _simd_set1_ps(static_cast<float>(x)));
        psContext.vX.center = _simd_add_ps(vCenterOffsetsX, _simd_set1_ps(static_cast<float>(x)));

        const simdscalar dx = _simd_set1_ps(static_cast<float>(SIMD_TILE_X_DIM));

        for (uint32_t xx = x; xx < x + KNOB_TILE_X_DIM; xx += SIMD_TILE_X_DIM)
        {
#if USE_8x2_TILE_BACKEND
            const bool useAlternateOffset = ((xx & SIMD_TILE_X_DIM) != 0);
#endif
            if (T::InputCoverage != SWR_INPUT_COVERAGE_NONE)
            {
                const uint64_t* pCoverageMask = (T::InputCoverage == SWR_INPUT_COVERAGE_INNER_CONSERVATIVE) ? &work.innerCoverageMask : &work.coverageMask[0];

                generateInputCoverage<T, T::InputCoverage>(pCoverageMask, psContext.inputMask, state.blendState.sampleMask);
            }

            AR_BEGIN(BEBarycentric, pDC->drawId);

            CalcPixelBarycentrics(coeffs, psContext);

            CalcCentroid<T, false>(&psContext, samplePos, coeffs, work.coverageMask, state.blendState.sampleMask);

            AR_END(BEBarycentric, 0);

            for (uint32_t sample = 0; sample < T::MultisampleT::numSamples; sample++)
            {
                simdmask coverageMask = work.coverageMask[sample] & MASK;

                if (coverageMask)
                {
                    // offset depth/stencil buffers current sample
                    uint8_t *pDepthSample = pDepthBuffer + RasterTileDepthOffset(sample);
                    uint8_t *pStencilSample = pStencilBuffer + RasterTileStencilOffset(sample);

                    if (state.depthHottileEnable && state.depthBoundsState.depthBoundsTestEnable)
                    {
                        static_assert(KNOB_DEPTH_HOT_TILE_FORMAT == R32_FLOAT, "Unsupported depth hot tile format");

                        const simdscalar z = _simd_load_ps(reinterpret_cast<const float *>(pDepthSample));

                        const float minz = state.depthBoundsState.depthBoundsTestMinValue;
                        const float maxz = state.depthBoundsState.depthBoundsTestMaxValue;

                        coverageMask &= CalcDepthBoundsAcceptMask(z, minz, maxz);
                    }

                    AR_BEGIN(BEBarycentric, pDC->drawId);

                    // calculate per sample positions
                    psContext.vX.sample = _simd_add_ps(psContext.vX.UL, samplePos.vX(sample));
                    psContext.vY.sample = _simd_add_ps(psContext.vY.UL, samplePos.vY(sample));

                    CalcSampleBarycentrics(coeffs, psContext);

                    // interpolate and quantize z
                    psContext.vZ = vplaneps(coeffs.vZa, coeffs.vZb, coeffs.vZc, psContext.vI.sample, psContext.vJ.sample);
                    psContext.vZ = state.pfnQuantizeDepth(psContext.vZ);

                    AR_END(BEBarycentric, 0);

                    // interpolate user clip distance if available
                    if (state.backendState.clipDistanceMask)
                    {
                        coverageMask &= ~ComputeUserClipMask(state.backendState.clipDistanceMask, work.pUserClipBuffer, psContext.vI.sample, psContext.vJ.sample);
                    }

                    simdscalar vCoverageMask = _simd_vmask_ps(coverageMask);
                    simdscalar depthPassMask = vCoverageMask;
                    simdscalar stencilPassMask = vCoverageMask;

                    // Early-Z?
                    if (T::bCanEarlyZ)
                    {
                        AR_BEGIN(BEEarlyDepthTest, pDC->drawId);
                        depthPassMask = DepthStencilTest(&state, work.triFlags.frontFacing, work.triFlags.viewportIndex,
                            psContext.vZ, pDepthSample, vCoverageMask, pStencilSample, &stencilPassMask);
                        AR_EVENT(EarlyDepthStencilInfoSampleRate(_simd_movemask_ps(depthPassMask), _simd_movemask_ps(stencilPassMask), _simd_movemask_ps(vCoverageMask)));
                        AR_END(BEEarlyDepthTest, 0);

                        // early-exit if no samples passed depth or earlyZ is forced on.
                        if (state.psState.forceEarlyZ || !_simd_movemask_ps(depthPassMask))
                        {
                            DepthStencilWrite(&state.vp[work.triFlags.viewportIndex], &state.depthStencilState, work.triFlags.frontFacing, psContext.vZ,
                                pDepthSample, depthPassMask, vCoverageMask, pStencilSample, stencilPassMask);

                            if (!_simd_movemask_ps(depthPassMask))
                            {
                                work.coverageMask[sample] >>= (SIMD_TILE_Y_DIM * SIMD_TILE_X_DIM);
                                continue;
                            }
                        }
                    }

                    psContext.sampleIndex = sample;
                    psContext.activeMask = _simd_castps_si(vCoverageMask);

                    // execute pixel shader
                    AR_BEGIN(BEPixelShader, pDC->drawId);
                    UPDATE_STAT_BE(PsInvocations, _mm_popcnt_u32(_simd_movemask_ps(vCoverageMask)));
                    state.psState.pfnPixelShader(GetPrivateState(pDC), &psContext);
                    AR_END(BEPixelShader, 0);

                    vCoverageMask = _simd_castsi_ps(psContext.activeMask);

                    // late-Z
                    if (!T::bCanEarlyZ)
                    {
                        AR_BEGIN(BELateDepthTest, pDC->drawId);
                        depthPassMask = DepthStencilTest(&state, work.triFlags.frontFacing, work.triFlags.viewportIndex,
                            psContext.vZ, pDepthSample, vCoverageMask, pStencilSample, &stencilPassMask);
                        AR_EVENT(LateDepthStencilInfoSampleRate(_simd_movemask_ps(depthPassMask), _simd_movemask_ps(stencilPassMask), _simd_movemask_ps(vCoverageMask)));
                        AR_END(BELateDepthTest, 0);

                        if (!_simd_movemask_ps(depthPassMask))
                        {
                            // need to call depth/stencil write for stencil write
                            DepthStencilWrite(&state.vp[work.triFlags.viewportIndex], &state.depthStencilState, work.triFlags.frontFacing, psContext.vZ,
                                pDepthSample, depthPassMask, vCoverageMask, pStencilSample, stencilPassMask);

                            work.coverageMask[sample] >>= (SIMD_TILE_Y_DIM * SIMD_TILE_X_DIM);
                            continue;
                        }
                    }

                    uint32_t statMask = _simd_movemask_ps(depthPassMask);
                    uint32_t statCount = _mm_popcnt_u32(statMask);
                    UPDATE_STAT_BE(DepthPassCount, statCount);

                    // output merger
                    AR_BEGIN(BEOutputMerger, pDC->drawId);
#if USE_8x2_TILE_BACKEND
                    OutputMerger8x2(psContext, psContext.pColorBuffer, sample, &state.blendState, state.pfnBlendFunc, vCoverageMask, depthPassMask, state.psState.renderTargetMask, useAlternateOffset);
#else
                    OutputMerger4x2(psContext, psContext.pColorBuffer, sample, &state.blendState, state.pfnBlendFunc, vCoverageMask, depthPassMask, state.psState.renderTargetMask);
#endif

                    // do final depth write after all pixel kills
                    if (!state.psState.forceEarlyZ)
                    {
                        DepthStencilWrite(&state.vp[work.triFlags.viewportIndex], &state.depthStencilState, work.triFlags.frontFacing, psContext.vZ,
                            pDepthSample, depthPassMask, vCoverageMask, pStencilSample, stencilPassMask);
                    }
                    AR_END(BEOutputMerger, 0);
                }