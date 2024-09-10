static void
DrawLandableBase(Canvas &canvas, const RasterPoint& pt, bool airport,
                 const fixed radius)
{
  int iradius = iround(radius);
  if (airport)
    canvas.circle(pt.x, pt.y, iradius);
  else {
    RasterPoint diamond[4];
    diamond[0].x = pt.x + 0;
    diamond[0].y = pt.y - iradius;
    diamond[1].x = pt.x + iradius;
    diamond[1].y = pt.y + 0;
    diamond[2].x = pt.x + 0;
    diamond[2].y = pt.y + iradius;
    diamond[3].x = pt.x - iradius;
    diamond[3].y = pt.y - 0;
    canvas.polygon(diamond, sizeof(diamond)/sizeof(diamond[0]));
  }
}