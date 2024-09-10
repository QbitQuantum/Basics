static float CalculateMidPercent(const SplineControlNode& start,
                                 const SplineControlNode& end) {
  // The mid value we called 'k' in the dual cubic documentation.
  // It's between 0~1 and determines where the start and end cubics are joined
  // along the x-axis.
  const Range valid_range = CalculateValidMidRange(start, end);

  // Return the part of the range closest to the half-way mark. This seems to
  // generate the smoothest looking curves.
  const float mid_unclamped = valid_range.Clamp(0.5f);

  // Clamp away from 0 and 1. The math requires the mid node to be strictly
  // between 0 and 1. If we get to close to 0 or 1, some divisions are going to
  // explode and we'll lose numerical precision.
  const float mid =
      mathfu::Clamp(mid_unclamped, kMinMidPercent, kMaxMidPercent);
  return mid;
}