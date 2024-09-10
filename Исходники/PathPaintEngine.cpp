void PathPaintEngine::updateState(const QPaintEngineState& state)
{
	if (state.state() & DirtyTransform)
		transform = state.transform();
	dashPattern = state.pen().dashPattern();
	isCosmetic  = state.pen().isCosmetic(); 
}