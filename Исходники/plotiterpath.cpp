double PlotIterPath::pointDistToLine_(const QPoint &p, const QLine &l)
{
  // Project the point on the line.
  double lx = l.x2() - l.x1();
  double ly = l.y2() - l.y1();
  double ll = sqrt(lx*lx + ly*ly);
  
  double vx = p.x() - l.x1();
  double vy = p.y() - l.y1();
  
  double prPar = (vx*lx + vy*ly) / ll;
  double prPerp = (vx*ly - vy*lx) / ll;
  
  // The point is on the "left" side of the line.
  if(prPar < 0)
    return sqrt(vx*vx + vy*vy);
  // The point is on the "right" side of the line.
  else if(prPar > ll)
    return sqrt(vx*vx + vy*vy);
  else
    return fabs(prPerp);
}