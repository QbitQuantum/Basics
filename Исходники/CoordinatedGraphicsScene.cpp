void CoordinatedGraphicsScene::paintToCurrentGLContext(const TransformationMatrix& matrix, float opacity, const FloatRect& clipRect, const Color& backgroundColor, bool drawsBackground, const FloatPoint& contentPosition, TextureMapper::PaintFlags PaintFlags)
{
    if (!m_textureMapper) {
        m_textureMapper = TextureMapper::create();
        static_cast<TextureMapperGL*>(m_textureMapper.get())->setEnableEdgeDistanceAntialiasing(true);
    }

    syncRemoteContent();

    adjustPositionForFixedLayers(contentPosition);
    TextureMapperLayer* currentRootLayer = rootLayer();
    if (!currentRootLayer)
        return;

#if USE(COORDINATED_GRAPHICS_THREADED)
    for (auto& proxy : m_platformLayerProxies.values())
        proxy->swapBuffer();
#endif

    currentRootLayer->setTextureMapper(m_textureMapper.get());
    currentRootLayer->applyAnimationsRecursively();
    m_textureMapper->beginPainting(PaintFlags);
    m_textureMapper->beginClip(TransformationMatrix(), clipRect);

    if (drawsBackground) {
        RGBA32 rgba = makeRGBA32FromFloats(backgroundColor.red(),
                                           backgroundColor.green(), backgroundColor.blue(),
                                           backgroundColor.alpha() * opacity);
        m_textureMapper->drawSolidColor(clipRect, TransformationMatrix(), Color(rgba));
    } else {
        GraphicsContext3D* context = static_cast<TextureMapperGL*>(m_textureMapper.get())->graphicsContext3D();
        context->clearColor(m_viewBackgroundColor.red() / 255.0f, m_viewBackgroundColor.green() / 255.0f, m_viewBackgroundColor.blue() / 255.0f, m_viewBackgroundColor.alpha() / 255.0f);
        context->clear(GraphicsContext3D::COLOR_BUFFER_BIT);
    }

    if (currentRootLayer->opacity() != opacity || currentRootLayer->transform() != matrix) {
        currentRootLayer->setOpacity(opacity);
        currentRootLayer->setTransform(matrix);
    }

    currentRootLayer->paint();
    m_fpsCounter.updateFPSAndDisplay(*m_textureMapper, clipRect.location(), matrix);
    m_textureMapper->endClip();
    m_textureMapper->endPainting();

    if (currentRootLayer->descendantsOrSelfHaveRunningAnimations()) {
        RefPtr<CoordinatedGraphicsScene> protector(this);
        dispatchOnClientRunLoop([=] {
            protector->updateViewport();
        });
    }
}