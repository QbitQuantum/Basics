TemporaryRef<Path>
nsSVGPolyElement::BuildPath(PathBuilder* aBuilder)
{
  const SVGPointList &points = mPoints.GetAnimValue();

  if (points.IsEmpty()) {
    return nullptr;
  }

  RefPtr<PathBuilder> pathBuilder = aBuilder ? aBuilder : CreatePathBuilder();

  pathBuilder->MoveTo(points[0]);
  for (uint32_t i = 1; i < points.Length(); ++i) {
    pathBuilder->LineTo(points[i]);
  }

  return pathBuilder->Finish();
}