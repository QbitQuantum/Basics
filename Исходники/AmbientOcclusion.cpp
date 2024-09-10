void AmbientOcclusion::computeRawAO
   (RenderDevice*                   rd,
    const AmbientOcclusionSettings& settings,
    const shared_ptr<Texture>&      depthBuffer,
    const Vector3&                  clipConstant,
    const Vector4&                  projConstant,
    const float                     projScale,
    const shared_ptr<Texture>&      csZBuffer,
    const shared_ptr<Texture>&      peeledCSZBuffer,
    const shared_ptr<Texture>&      normalBuffer) {

    debugAssert(projScale > 0);
    m_rawAOFramebuffer->set(Framebuffer::DEPTH, depthBuffer);
    rd->push2D(m_rawAOFramebuffer); {

        // For quick early-out testing vs. skybox 
        rd->setDepthTest(RenderDevice::DEPTH_GREATER);

        // Values that are never touched due to the depth test will be white
        rd->setColorClearValue(Color3::white());
        rd->clear(true, false, false);
        Args args;

        args.setMacro(SYMBOL_NUM_SAMPLES,    settings.numSamples);
        args.setMacro(SYMBOL_NUM_SPIRAL_TURNS, settings.numSpiralTurns());
        args.setUniform(SYMBOL_radius,       settings.radius);
        args.setUniform(SYMBOL_bias,         settings.bias);
        args.setUniform(SYMBOL_clipInfo,     clipConstant);
        args.setUniform(SYMBOL_projInfo,     projConstant);
        args.setUniform(SYMBOL_projScale,    projScale);
        args.setUniform(SYMBOL_CS_Z_buffer,  csZBuffer, cszSamplerSettings());
        args.setUniform(SYMBOL_intensityDivR6, (float)(settings.intensity / powf(settings.radius, 6.0f)));
        args.setUniform(SYMBOL_intensity, settings.intensity);
        args.setUniform(SYMBOL_radius2, square(settings.radius));
        args.setUniform(SYMBOL_invRadius2, 1.0f / square(settings.radius));
        args.setMacro("TEMPORALLY_VARY_SAMPLES", settings.temporallyVarySamples);
        
        const bool useDepthPeel = settings.useDepthPeelBuffer;
        args.setMacro(SYMBOL_USE_DEPTH_PEEL, useDepthPeel ? 1 : 0);
        if ( useDepthPeel ) {
            bool cszPackedTogether = csZBuffer == peeledCSZBuffer;
            args.setMacro(SYMBOL_CS_Z_PACKED_TOGETHER, cszPackedTogether ? 1 : 0);
            if ( !cszPackedTogether ) {
                args.setUniform(SYMBOL_peeled_CS_Z_buffer, peeledCSZBuffer, cszSamplerSettings());
                const Vector2& peeledExtent     = peeledCSZBuffer->rect2DBounds().extent();
                const Vector2& unpeeledExtent   = csZBuffer->rect2DBounds().extent();
                bool differingDepthExtents = peeledExtent != unpeeledExtent;
                args.setMacro(SYMBOL_DIFFERENT_DEPTH_RESOLUTIONS, differingDepthExtents ? 1 : 0);
                if (differingDepthExtents) {
                    //TODO: only calculate one dimension in the first place
                    args.setUniform(SYMBOL_peeledToUnpeeledScale, (peeledExtent / unpeeledExtent).x);
                }
            } else {
                args.setMacro(SYMBOL_DIFFERENT_DEPTH_RESOLUTIONS, 0);
            }
        } else {
            args.setMacro(SYMBOL_CS_Z_PACKED_TOGETHER, 0);
            args.setMacro(SYMBOL_DIFFERENT_DEPTH_RESOLUTIONS, 0);
        }
        
        if (settings.useNormalBuffer && notNull(normalBuffer)) {
            debugAssertM(normalBuffer->encoding().frame == FrameName::CAMERA, "AmbientOcclusion expects camera-space normals");
            normalBuffer->setShaderArgs(args, "normal_", Sampler::buffer());
        }

        rd->setClip2D(Rect2D::xyxy((float)m_guardBandSize, (float)m_guardBandSize, rd->viewport().width() - m_guardBandSize, rd->viewport().height() - m_guardBandSize));
        args.setRect(rd->viewport());
        LAUNCH_SHADER("AmbientOcclusion_AO.*", args);
    } rd->pop2D();
}