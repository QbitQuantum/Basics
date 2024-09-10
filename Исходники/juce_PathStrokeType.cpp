 static void addArrowhead (Path& destPath,
                           const float x1, const float y1,
                           const float x2, const float y2,
                           const float tipX, const float tipY,
                           const float width,
                           const float arrowheadWidth)
 {
     Line<float> line (x1, y1, x2, y2);
     destPath.lineTo (line.getPointAlongLine (-(arrowheadWidth / 2.0f - width), 0));
     destPath.lineTo (tipX, tipY);
     destPath.lineTo (line.getPointAlongLine (arrowheadWidth - (arrowheadWidth / 2.0f - width), 0));
     destPath.lineTo (x2, y2);
 }