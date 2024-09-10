TemporaryRef<Path>
SVGLineElement::BuildPath()
{
  RefPtr<PathBuilder> pathBuilder = CreatePathBuilder();

  float x1, y1, x2, y2;
  GetAnimatedLengthValues(&x1, &y1, &x2, &y2, nullptr);

  pathBuilder->MoveTo(Point(x1, y1));
  pathBuilder->LineTo(Point(x2, y2));

  return pathBuilder->Finish();
}