void QgsComposerUtils::relativeResizeRect( QRectF& rectToResize, const QRectF& boundsBefore, const QRectF& boundsAfter )
{
  //linearly scale rectToResize relative to the scaling from boundsBefore to boundsAfter
  double left = relativePosition( rectToResize.left(), boundsBefore.left(), boundsBefore.right(), boundsAfter.left(), boundsAfter.right() );
  double right = relativePosition( rectToResize.right(), boundsBefore.left(), boundsBefore.right(), boundsAfter.left(), boundsAfter.right() );
  double top = relativePosition( rectToResize.top(), boundsBefore.top(), boundsBefore.bottom(), boundsAfter.top(), boundsAfter.bottom() );
  double bottom = relativePosition( rectToResize.bottom(), boundsBefore.top(), boundsBefore.bottom(), boundsAfter.top(), boundsAfter.bottom() );

  rectToResize.setRect( left, top, right - left, bottom - top );
}