void LayerRendererChromium::drawLayer(CCLayerImpl* layer, RenderSurfaceChromium* targetSurface)
{
    if (layer->renderSurface() && layer->renderSurface() != targetSurface) {
        layer->renderSurface()->draw(layer->getDrawRect());
        return;
    }

    if (!layer->drawsContent())
        return;

    if (layer->bounds().isEmpty()) {
        layer->unreserveContentsTexture();
        return;
    }

    setScissorToRect(layer->scissorRect());

    IntRect targetSurfaceRect = m_currentRenderSurface ? m_currentRenderSurface->contentRect() : m_defaultRenderSurface->contentRect();
    IntRect scissorRect = layer->scissorRect();
    if (!scissorRect.isEmpty())
        targetSurfaceRect.intersect(scissorRect);

    // Check if the layer falls within the visible bounds of the page.
    IntRect layerRect = layer->getDrawRect();
    bool isLayerVisible = targetSurfaceRect.intersects(layerRect);
    if (!isLayerVisible) {
        layer->unreserveContentsTexture();
        return;
    }

    // FIXME: Need to take into account the commulative render surface transforms all the way from
    //        the default render surface in order to determine visibility.
    TransformationMatrix combinedDrawMatrix = (layer->targetRenderSurface() ? layer->targetRenderSurface()->drawTransform().multiply(layer->drawTransform()) : layer->drawTransform());
    
    if (!layer->doubleSided()) {
        FloatRect layerRect(FloatPoint(0, 0), FloatSize(layer->bounds()));
        FloatQuad mappedLayer = combinedDrawMatrix.mapQuad(FloatQuad(layerRect));
        FloatSize horizontalDir = mappedLayer.p2() - mappedLayer.p1();
        FloatSize verticalDir = mappedLayer.p4() - mappedLayer.p1();
        FloatPoint3D xAxis(horizontalDir.width(), horizontalDir.height(), 0);
        FloatPoint3D yAxis(verticalDir.width(), verticalDir.height(), 0);
        FloatPoint3D zAxis = xAxis.cross(yAxis);
        if (zAxis.z() < 0) {
            layer->unreserveContentsTexture();
            return;
        }
    }

    layer->draw(targetSurfaceRect);

    // Draw the debug border if there is one.
    layer->drawDebugBorder();
}