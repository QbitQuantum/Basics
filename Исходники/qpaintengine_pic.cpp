void QPicturePaintEngine::updateState(const QPaintEngineState &state)
{
    QPaintEngine::DirtyFlags flags = state.state();
    if (flags & DirtyPen) updatePen(state.pen());
    if (flags & DirtyBrush) updateBrush(state.brush());
    if (flags & DirtyBrushOrigin) updateBrushOrigin(state.brushOrigin());
    if (flags & DirtyFont) updateFont(state.font());
    if (flags & DirtyBackground) updateBackground(state.backgroundMode(), state.backgroundBrush());
    if (flags & DirtyTransform) updateMatrix(state.transform());
    if (flags & DirtyClipEnabled) updateClipEnabled(state.isClipEnabled());
    if (flags & DirtyClipRegion) updateClipRegion(state.clipRegion(), state.clipOperation());
    if (flags & DirtyClipPath) updateClipPath(state.clipPath(), state.clipOperation());
    if (flags & DirtyHints) updateRenderHints(state.renderHints());
    if (flags & DirtyCompositionMode) updateCompositionMode(state.compositionMode());
    if (flags & DirtyOpacity) updateOpacity(state.opacity());
}