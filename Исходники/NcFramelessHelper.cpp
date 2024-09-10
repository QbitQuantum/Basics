void NcWidgetData::updateCursorShape( const QPoint& globalMousePos )
{
  if ( mWidget->isFullScreen() || mWidget->isMaximized() )
  {
    if ( mCursorShapeChanged )
      mWidget->unsetCursor();

    return;
  }

  mMoveMousePos.recalculate( globalMousePos, mWidget->frameGeometry() );

  if( mMoveMousePos.onTopLeftEdge || mMoveMousePos.onBottomRightEdge )
  {
    mWidget->setCursor( Qt::SizeFDiagCursor );
    mCursorShapeChanged = true;
  }
  else if( mMoveMousePos.onTopRightEdge || mMoveMousePos.onBottomLeftEdge )
  {
    mWidget->setCursor( Qt::SizeBDiagCursor );
    mCursorShapeChanged = true;
  }
  else if( mMoveMousePos.onLeftEdge || mMoveMousePos.onRightEdge )
  {
    mWidget->setCursor( Qt::SizeHorCursor );
    mCursorShapeChanged = true;
  }
  else if( mMoveMousePos.onTopEdge || mMoveMousePos.onBottomEdge )
  {
    mWidget->setCursor( Qt::SizeVerCursor );
    mCursorShapeChanged = true;
  }
  else
  {
    if ( mCursorShapeChanged )
    {
      mWidget->unsetCursor();
      mCursorShapeChanged = false;
    }
  }
}