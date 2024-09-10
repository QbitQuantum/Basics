// get consistent clipping on different platforms by making line
// edges meet clipping box if close
void _Clipper::fixPt(QPointF& pt) const
{
  if( fabs(pt.x() - clip.left()) < 1e-4 )
    pt.setX(clip.left());
  if( fabs(pt.x() - clip.right()) < 1e-4 )
    pt.setX(clip.right());
  if( fabs(pt.y() - clip.top()) < 1e-4 )
    pt.setY(clip.top());
  if( fabs(pt.y() - clip.bottom()) < 1e-4 )
    pt.setY(clip.bottom());
}