Path const ConnectedEdges::createConnectedFace (
  Rectangle <int> const& bounds,
  float frameThickness,
  float cornerRadius)
{
  Path path;
  Rectangle <float> const r = bounds.toFloat().reduced (frameThickness/2, frameThickness/2);

  float const x = r.getX();
  float const y = r.getY();
  float const w = r.getWidth();
  float const h = r.getHeight();
  float const csx = jmin (cornerRadius, w * 0.5f);
  float const csy = jmin (cornerRadius, h * 0.5f);
  float const cs45x = csx * 0.45f;
  float const cs45y = csy * 0.45f;
  float const x2 = x + w;
  float const y2 = y + h;

  // start

  if (isConnectedOnLeft () || isConnectedOnTop())
    path.startNewSubPath (x, y);
  else
    path.startNewSubPath (x + csx, y);

  // top

  if (isConnectedOnTop () || isConnectedOnRight ())
  {
    path.lineTo( x2, y );
  }
  else
  {
    path.lineTo (x2 - csx, y);
    path.cubicTo (x2 - cs45x, y, x2, y + cs45y, x2, y + csy);
  }

  // right

  if (isConnectedOnRight () || isConnectedOnBottom ())
  {
    path.lineTo( x2, y2 );
  }
  else
  {
    path.lineTo (x2, y2 - csy);
    path.cubicTo (x2, y2 - cs45y, x2 - cs45x, y2, x2 - csx, y2);
  }
    
  // bottom
    
  if (isConnectedOnBottom () || isConnectedOnLeft ())
  {
    path.lineTo( x, y2 );
  }
  else
  {
    path.lineTo (x + csx, y2);
    path.cubicTo (x + cs45x, y2, x, y2 - cs45y, x, y2 - csy);
  }

  // left

  if (!isConnectedOnLeft () && !isConnectedOnTop ())
  {
    path.lineTo (x, y + csy);
    path.cubicTo (x, y + cs45y, x + cs45x, y, x + csx, y);
  }

  path.closeSubPath();

  return path;
}