void CCRenderSurface::copyDeviceToBackgroundTexture(LayerRendererChromium* layerRenderer, int deviceBackgroundTextureId, const IntRect& deviceTextureRect, const TransformationMatrix& deviceTransform) const
{
    ASSERT(!m_backgroundFilters.isEmpty());

    TransformationMatrix deviceToSurfaceTransform;
    deviceToSurfaceTransform.translate(m_contentRect.width() / 2.0, m_contentRect.height() / 2.0);
    deviceToSurfaceTransform.scale3d(m_contentRect.width(), m_contentRect.height(), 1);
    deviceToSurfaceTransform *= deviceTransform.inverse();
    deviceToSurfaceTransform.translate(deviceTextureRect.width() / 2.0, deviceTextureRect.height() / 2.0);
    deviceToSurfaceTransform.translate(deviceTextureRect.x(), deviceTextureRect.y());

    copyTextureToFramebuffer(layerRenderer, deviceBackgroundTextureId, deviceTextureRect.size(), deviceToSurfaceTransform);
}