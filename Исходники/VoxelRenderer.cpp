void VoxelRenderer::Flush(RenderContext& renderContext,
                          const SceneConstants& sceneConstants)
{
    //  Set up global shader constants
    m_constants.projectionViewMatrix = sceneConstants.viewMatrix *
                                       sceneConstants.projectionMatrix;
    m_constants.clipPlane = sceneConstants.clipPlane;

    //  Calculate camera distances for all queued render ops
    float3 cameraPos = sceneConstants.cameraPos;
    for (size_t i = 0; i < m_renderOps.size(); ++i)
    {
        float3 diff = m_renderOps[i].position - cameraPos;
        m_renderOps[i].distance2 = Dot(diff, diff);
    }
    for (size_t i = 0; i < m_gapFillerRenderOps.size(); ++i)
    {
        float3 diff = m_gapFillerRenderOps[i].position - cameraPos;
        m_gapFillerRenderOps[i].distance2 = Dot(diff, diff);
    }
    for (size_t i = 0; i < m_transparentRenderOps.size(); ++i)
    {
        float3 diff = m_transparentRenderOps[i].position - cameraPos;
        m_transparentRenderOps[i].distance2 = Dot(diff, diff);
    }
    
    //  Sort by camera distance (front to back for opaque render ops,
    //  back to front for transparent)
    auto transparentSorter = [](const RenderOp& lhs, const RenderOp& rhs)
    {
        return lhs.distance2 > rhs.distance2;
    };
    auto opaqueSorter = [](const RenderOp& lhs, const RenderOp& rhs)
    {
        return lhs.distance2 < rhs.distance2;
    };
    std::sort(m_renderOps.begin(), m_renderOps.end(), opaqueSorter);
    std::sort(m_gapFillerRenderOps.begin(), m_gapFillerRenderOps.end(), opaqueSorter);
    std::sort(m_transparentRenderOps.begin(), m_transparentRenderOps.end(), transparentSorter);

    //  Finally time to draw them
    renderContext.PushDepthStencilState(m_shared->depthStencilState);
    for (size_t i = 0; i < m_renderOps.size(); i++)
    {
        Draw(m_renderOps[i]);
    }
    m_renderOps.clear();
    renderContext.PopDepthStencilState();

    renderContext.PushDepthStencilState(m_shared->fillGapsDepthStencilState);
    for (size_t i = 0; i < m_gapFillerRenderOps.size(); ++i)
    {
        Draw(m_gapFillerRenderOps[i]);
    }
    m_gapFillerRenderOps.clear();
    renderContext.PopDepthStencilState();

    renderContext.PushDepthStencilState(m_shared->transparentDepthStencilState);
    renderContext.PushBlendState(m_shared->blendState);
    for (size_t i = 0; i < m_transparentRenderOps.size(); i++)
    {
        Draw(m_transparentRenderOps[i]);
    }
    m_transparentRenderOps.clear();
    renderContext.PopBlendState();
    renderContext.PopDepthStencilState();
}