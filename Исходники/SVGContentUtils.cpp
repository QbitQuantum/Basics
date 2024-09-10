void
SVGContentUtils::RectilinearGetStrokeBounds(const Rect& aRect,
                                            const Matrix& aToBoundsSpace,
                                            const Matrix& aToNonScalingStrokeSpace,
                                            float aStrokeWidth,
                                            Rect* aBounds)
{
  MOZ_ASSERT(aToBoundsSpace.IsRectilinear(),
             "aToBoundsSpace must be rectilinear");
  MOZ_ASSERT(aToNonScalingStrokeSpace.IsRectilinear(),
             "aToNonScalingStrokeSpace must be rectilinear");

  Matrix nonScalingToSource = aToNonScalingStrokeSpace.Inverse();
  Matrix nonScalingToBounds = nonScalingToSource * aToBoundsSpace;

  *aBounds = aToBoundsSpace.TransformBounds(aRect);

  // Compute the amounts dx and dy that nonScalingToBounds scales a half-width
  // stroke in the x and y directions, and then inflate aBounds by those amounts
  // so that when aBounds is transformed back to non-scaling-stroke space
  // it will map onto the correct stroked bounds.

  Float dx = 0.0f;
  Float dy = 0.0f;
  // nonScalingToBounds is rectilinear, so either _12 and _21 are zero or _11
  // and _22 are zero, and in each case the non-zero entries (from among _11,
  // _12, _21, _22) simply scale the stroke width in the x and y directions.
  if (FuzzyEqual(nonScalingToBounds._12, 0) &&
      FuzzyEqual(nonScalingToBounds._21, 0)) {
    dx = (aStrokeWidth / 2.0f) * std::abs(nonScalingToBounds._11);
    dy = (aStrokeWidth / 2.0f) * std::abs(nonScalingToBounds._22);
  } else {
    dx = (aStrokeWidth / 2.0f) * std::abs(nonScalingToBounds._21);
    dy = (aStrokeWidth / 2.0f) * std::abs(nonScalingToBounds._12);
  }

  aBounds->Inflate(dx, dy);
}