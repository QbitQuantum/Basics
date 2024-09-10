TemporaryRef<Path>
SVGImageElement::BuildPath(PathBuilder* aBuilder)
{
  // We get called in order to get bounds for this element, and for
  // hit-testing against it. For that we just pretend to be a rectangle.

  float x, y, width, height;
  GetAnimatedLengthValues(&x, &y, &width, &height, nullptr);

  if (width <= 0 || height <= 0) {
    return nullptr;
  }

  RefPtr<PathBuilder> pathBuilder = aBuilder ? aBuilder : CreatePathBuilder();

  Rect r(x, y, width, height);
  pathBuilder->MoveTo(r.TopLeft());
  pathBuilder->LineTo(r.TopRight());
  pathBuilder->LineTo(r.BottomRight());
  pathBuilder->LineTo(r.BottomLeft());
  pathBuilder->Close();

  return pathBuilder->Finish();
}