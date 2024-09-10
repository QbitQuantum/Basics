MultiLineStringGraphics::MultiLineStringGraphics(OGRMultiLineString* OGRMultiLine, const QPen& Pen):
  LinearGraphics(Pen.color())
{
  QPainterPath Path;

  for (int i=0; i<OGRMultiLine->getNumGeometries();i++)
  {
    QPainterPath LinePath;

    OGRLineString* OGRLine = dynamic_cast<OGRLineString*>(OGRMultiLine->getGeometryRef(i));

    LinePath.moveTo(OGRLine->getX(0),OGRLine->getY(0));

    for (int i=1; i < OGRLine->getNumPoints(); i++)
    {
      LinePath.lineTo(OGRLine->getX(i),OGRLine->getY(i));
    }

    Path.addPath(LinePath);
  }

  setPen(Pen);
  setPath(Path);
}