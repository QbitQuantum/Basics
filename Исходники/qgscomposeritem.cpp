double QgsComposerItem::horizontalViewScaleFactor() const
{
  double result = -1;
  if ( scene() )
  {
    QList<QGraphicsView *> viewList = scene()->views();
    if ( !viewList.isEmpty() ) //if not, probably this function was called from non-gui code
    {
      QGraphicsView *currentView = viewList.at( 0 );
      if ( currentView->isVisible() )
      {
        result = currentView->transform().m11();
        mLastValidViewScaleFactor = result;
      }
    }
  }
  return result;
}