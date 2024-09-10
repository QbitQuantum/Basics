  /// \brief Get the intersection of this interval with another interval.
  ///
  Interval<ValueT> intersection(Interval const &Other) const {
    // If there is no intersection, return an empty Interval.
    if (!intersects(Other))
      return Interval<ValueT>::withStartEnd(Start, Start);

    auto IntersectStart = std::max(Start, Other.Start);
    auto IntersectEnd = std::min(End, Other.End);

    return Interval<ValueT>::withStartEnd(IntersectStart, IntersectEnd);
  }