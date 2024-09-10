void AmbientOcclusion::run(const render::SceneContextPointer& sceneContext, const render::RenderContextPointer& renderContext) {
    assert(renderContext->getArgs());
    assert(renderContext->getArgs()->_viewFrustum);

    RenderArgs* args = renderContext->getArgs();
    gpu::doInBatch(args->_context, [=](gpu::Batch& batch) {
        auto framebufferCache = DependencyManager::get<FramebufferCache>();
        QSize framebufferSize = framebufferCache->getFrameBufferSize();
        float fbWidth = framebufferSize.width();
        float fbHeight = framebufferSize.height();
        float sMin = args->_viewport.x / fbWidth;
        float sWidth = args->_viewport.z / fbWidth;
        float tMin = args->_viewport.y / fbHeight;
        float tHeight = args->_viewport.w / fbHeight;


        glm::mat4 projMat;
        Transform viewMat;
        args->_viewFrustum->evalProjectionMatrix(projMat);
        args->_viewFrustum->evalViewTransform(viewMat);
        batch.setProjectionTransform(projMat);
        batch.setViewTransform(viewMat);
        batch.setModelTransform(Transform());

        // Occlusion step
        getOcclusionPipeline();
        batch.setResourceTexture(0, framebufferCache->getPrimaryDepthTexture());
        batch.setResourceTexture(1, framebufferCache->getDeferredNormalTexture());
        _occlusionBuffer->setRenderBuffer(0, _occlusionTexture);
        batch.setFramebuffer(_occlusionBuffer);

        // Occlusion uniforms
        g_scale = 1.0f;
        g_bias = 1.0f;
        g_sample_rad = 1.0f;
        g_intensity = 1.0f;

        // Bind the first gpu::Pipeline we need - for calculating occlusion buffer
        batch.setPipeline(getOcclusionPipeline());
        batch._glUniform1f(_gScaleLoc, g_scale);
        batch._glUniform1f(_gBiasLoc, g_bias);
        batch._glUniform1f(_gSampleRadiusLoc, g_sample_rad);
        batch._glUniform1f(_gIntensityLoc, g_intensity);

        // setup uniforms for unpacking a view-space position from the depth buffer
        // This is code taken from DeferredLightEffect.render() method in DeferredLightingEffect.cpp.
        // DeferredBuffer.slh shows how the unpacking is done and what variables are needed.

        // initialize the view-space unpacking uniforms using frustum data
        float left, right, bottom, top, nearVal, farVal;
        glm::vec4 nearClipPlane, farClipPlane;

        args->_viewFrustum->computeOffAxisFrustum(left, right, bottom, top, nearVal, farVal, nearClipPlane, farClipPlane);

        float depthScale = (farVal - nearVal) / farVal;
        float nearScale = -1.0f / nearVal;
        float depthTexCoordScaleS = (right - left) * nearScale / sWidth;
        float depthTexCoordScaleT = (top - bottom) * nearScale / tHeight;
        float depthTexCoordOffsetS = left * nearScale - sMin * depthTexCoordScaleS;
        float depthTexCoordOffsetT = bottom * nearScale - tMin * depthTexCoordScaleT;

        // now set the position-unpacking unforms
        batch._glUniform1f(_nearLoc, nearVal);
        batch._glUniform1f(_depthScaleLoc, depthScale);
        batch._glUniform2f(_depthTexCoordOffsetLoc, depthTexCoordOffsetS, depthTexCoordOffsetT);
        batch._glUniform2f(_depthTexCoordScaleLoc, depthTexCoordScaleS, depthTexCoordScaleT);

        batch._glUniform2f(_renderTargetResLoc, fbWidth, fbHeight);
        batch._glUniform2f(_renderTargetResInvLoc, 1.0f / fbWidth, 1.0f / fbHeight);

        glm::vec4 color(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec2 bottomLeft(-1.0f, -1.0f);
        glm::vec2 topRight(1.0f, 1.0f);
        glm::vec2 texCoordTopLeft(0.0f, 0.0f);
        glm::vec2 texCoordBottomRight(1.0f, 1.0f);
        DependencyManager::get<GeometryCache>()->renderQuad(batch, bottomLeft, topRight, texCoordTopLeft, texCoordBottomRight, color);

        // Vertical blur step
        getVBlurPipeline();
        batch.setResourceTexture(0, _occlusionTexture);
        _vBlurBuffer->setRenderBuffer(0, _vBlurTexture);
        batch.setFramebuffer(_vBlurBuffer);

        // Bind the second gpu::Pipeline we need - for calculating blur buffer
        batch.setPipeline(getVBlurPipeline());

        DependencyManager::get<GeometryCache>()->renderQuad(batch, bottomLeft, topRight, texCoordTopLeft, texCoordBottomRight, color);

        // Horizontal blur step
        getHBlurPipeline();
        batch.setResourceTexture(0, _vBlurTexture);
        _hBlurBuffer->setRenderBuffer(0, _hBlurTexture);
        batch.setFramebuffer(_hBlurBuffer);

        // Bind the third gpu::Pipeline we need - for calculating blur buffer
        batch.setPipeline(getHBlurPipeline());

        DependencyManager::get<GeometryCache>()->renderQuad(batch, bottomLeft, topRight, texCoordTopLeft, texCoordBottomRight, color);

        // Blend step
        getBlendPipeline();
        batch.setResourceTexture(0, _hBlurTexture);
        batch.setFramebuffer(framebufferCache->getDeferredFramebuffer());

        // Bind the fourth gpu::Pipeline we need - for blending the primary color buffer with blurred occlusion texture
        batch.setPipeline(getBlendPipeline());

        DependencyManager::get<GeometryCache>()->renderQuad(batch, bottomLeft, topRight, texCoordTopLeft, texCoordBottomRight, color);
    });
}