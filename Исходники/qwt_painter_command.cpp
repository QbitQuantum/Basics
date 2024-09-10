/*!
  Constructor for State paint operation
  \param state Paint engine state
 */
QwtPainterCommand::QwtPainterCommand( const QPaintEngineState &state ):
    d_type( State )
{
    d_stateData = new StateData();

    d_stateData->flags = state.state();

    if ( d_stateData->flags & QPaintEngine::DirtyPen )
        d_stateData->pen = state.pen();

    if ( d_stateData->flags & QPaintEngine::DirtyBrush )
        d_stateData->brush = state.brush();

    if ( d_stateData->flags & QPaintEngine::DirtyBrushOrigin )
        d_stateData->brushOrigin = state.brushOrigin();

    if ( d_stateData->flags & QPaintEngine::DirtyFont )
        d_stateData->font = state.font();

    if ( d_stateData->flags & QPaintEngine::DirtyBackground )
    {
        d_stateData->backgroundMode = state.backgroundMode();
        d_stateData->backgroundBrush = state.backgroundBrush();
    }

    if ( d_stateData->flags & QPaintEngine::DirtyTransform )
        d_stateData->transform = state.transform();

    if ( d_stateData->flags & QPaintEngine::DirtyClipEnabled )
        d_stateData->isClipEnabled = state.isClipEnabled();

    if ( d_stateData->flags & QPaintEngine::DirtyClipRegion )
    {
        d_stateData->clipRegion = state.clipRegion();
        d_stateData->clipOperation = state.clipOperation();
    }

    if ( d_stateData->flags & QPaintEngine::DirtyClipPath )
    {
        d_stateData->clipPath = state.clipPath();
        d_stateData->clipOperation = state.clipOperation();
    }

    if ( d_stateData->flags & QPaintEngine::DirtyHints )
        d_stateData->renderHints = state.renderHints();

    if ( d_stateData->flags & QPaintEngine::DirtyCompositionMode )
        d_stateData->compositionMode = state.compositionMode();

    if ( d_stateData->flags & QPaintEngine::DirtyOpacity )
        d_stateData->opacity = state.opacity();
}