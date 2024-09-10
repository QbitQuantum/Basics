void LayerBase::validateVisibility(const Transform& planeTransform)
{
    const Layer::State& s(drawingState());
    const Transform tr(planeTransform * s.transform);
    const bool transformed = tr.transformed();
   
    uint32_t w = s.w;
    uint32_t h = s.h;    
    tr.transform(mVertices[0], 0, 0);
    tr.transform(mVertices[1], 0, h);
    tr.transform(mVertices[2], w, h);
    tr.transform(mVertices[3], w, 0);
    if (UNLIKELY(transformed)) {
        // NOTE: here we could also punt if we have too many rectangles
        // in the transparent region
        if (tr.preserveRects()) {
            // transform the transparent region
            transparentRegionScreen = tr.transform(s.transparentRegion);
        } else {
            // transformation too complex, can't do the transparent region
            // optimization.
            transparentRegionScreen.clear();
        }
    } else {
        transparentRegionScreen = s.transparentRegion;
    }

    // cache a few things...
    mOrientation = tr.getOrientation();
    mTransformedBounds = tr.makeBounds(w, h);
#ifdef AVOID_DRAW_TEXTURE
    mTransformed = transformed;
#endif
    mLeft = tr.tx();
    mTop  = tr.ty();
}