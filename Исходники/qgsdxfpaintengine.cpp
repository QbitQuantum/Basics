void QgsDxfPaintEngine::updateState( const QPaintEngineState& state )
{
  if ( state.state() & QPaintEngine::DirtyTransform )
  {
    mTransform = state.transform();
  }
  if ( state.state() & QPaintEngine::DirtyPen )
  {
    mPen = state.pen();
  }
  if ( state.state() & QPaintEngine::DirtyBrush )
  {
    mBrush = state.brush();
  }
}