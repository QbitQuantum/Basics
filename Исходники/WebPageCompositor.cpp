void WebPageCompositorPrivate::findFixedElementRect(LayerCompositingThread* layer, WebCore::IntRect& fixedElementRect)
{
    if ((layer->hasFixedContainer() || layer->isFixedPosition() || layer->hasFixedAncestorInDOMTree()) && layer->layerRenderer()) {
        IntRect fixedRect = layer->layerRenderer()->toPixelViewportCoordinates(layer->boundingBox());
        // FIXME: It's possible that the rects don't intersect now, but will be connected by a fixed rect found later.
        // We need to handle it as well.
        if (fixedElementRect.isEmpty() || fixedElementRect.intersects(fixedRect)) // Unite rects if they intersect each other.
            fixedElementRect.unite(fixedRect);
        else if (fixedRect.y() < fixedElementRect.y()) // Replace the fixedElementRect with fixedRect if fixedRect is above it (closer to top).
            fixedElementRect = fixedRect;
    }

    const Vector<RefPtr<LayerCompositingThread> >& sublayers = layer->sublayers();
    for (size_t i = 0; i < sublayers.size(); i++)
        findFixedElementRect(sublayers[i].get(), fixedElementRect);
}