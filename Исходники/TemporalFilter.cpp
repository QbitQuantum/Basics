shared_ptr<Texture> TemporalFilter::apply
   (RenderDevice* rd, 
    const Vector3&                  clipConstant,
    const Vector4&                  projConstant,
    const CFrame&                   currentCameraFrame,
    const CFrame&                   prevCameraFrame, 
    const shared_ptr<Texture>&      unfilteredValue, 
    const shared_ptr<Texture>&      depth, 
    const shared_ptr<Texture>&      ssVelocity, 
    const Vector2&                  guardBandSize,
    int                             numFilterComponents, 
    const Settings&                 settings) {

    if (settings.hysteresis == 0.0f) {
        return unfilteredValue;
    }

    alwaysAssertM((settings.hysteresis >= 0.0f) && (settings.hysteresis <= 1.0f), "TemporalFilter::Settings::hysteresis must be in [0.0, 1.0]");
    alwaysAssertM(notNull(unfilteredValue) && notNull(depth) && notNull(ssVelocity), "Sent null buffer to TemporalFilter::apply");
    alwaysAssertM((numFilterComponents >= 1) && (numFilterComponents <= 4), "numFilterComponents must be between 1 and 4");

    if (isNull(m_previousDepthBuffer) || 
        isNull(m_previousTexture) ||
        (m_previousDepthBuffer->vector2Bounds() != depth->vector2Bounds()) ||
        (m_previousTexture->vector2Bounds() != unfilteredValue->vector2Bounds())) {

        unfilteredValue->copyInto(m_previousTexture);
        depth->copyInto(m_previousDepthBuffer);
        m_resultFramebuffer = Framebuffer::create(Texture::createEmpty("TemporalFilter::m_resultFramebuffer", m_previousTexture->width(), m_previousTexture->height(), m_previousTexture->format()));
        Texture::copy(m_previousTexture, m_resultFramebuffer->texture(0));
        return m_resultFramebuffer->texture(0);
    }

    rd->push2D(m_resultFramebuffer); {
        Args args;
        args.setMacro("FILTER_COMPONENT_COUNT", numFilterComponents);
        ssVelocity->setShaderArgs(args, "ssVelocity_", Sampler::buffer());
        unfilteredValue->setShaderArgs(args, "unfilteredValue_", Sampler::buffer());
        depth->setShaderArgs(args, "depth_", Sampler::buffer());
        m_previousDepthBuffer->setShaderArgs(args, "previousDepth_", Sampler::video());
        m_previousTexture->setShaderArgs(args, "previousValue_", Sampler::video());

        args.setUniform("guardBandSize", guardBandSize);

        args.setUniform("cameraToWorld", currentCameraFrame);    
        args.setUniform("cameraToWorldPrevious", prevCameraFrame);
        
        args.setUniform("clipInfo", clipConstant);
        args.setUniform("projInfo", projConstant);

        settings.setArgs(args);
        args.setRect(rd->viewport());

        LAUNCH_SHADER("TemporalFilter_apply.*", args);
        m_resultFramebuffer->texture(0)->copyInto(m_previousTexture);

        depth->copyInto(m_previousDepthBuffer);
    } rd->pop2D();
     return m_resultFramebuffer->texture(0);
}