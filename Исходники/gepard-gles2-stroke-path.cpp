void GepardGLES2::strokePath()
{
    PathData* pathData = _context.path.pathData();
    GepardState& state = _context.currentState();

    GD_LOG3("Path: " << pathData->firstElement());
    if (!pathData || pathData->isEmpty())
        return;

    Float miterLimit = state.miterLimit ? state.miterLimit : 10;

    StrokePathBuilder sPath(state.lineWitdh, miterLimit, state.lineJoinMode, state.lineCapMode);
    sPath.convertStrokeToFill(pathData);

    Color tempColor = state.fillColor;
    state.fillColor = state.strokeColor;
    fillPath(sPath.pathData(), state);
    state.fillColor = tempColor;
}