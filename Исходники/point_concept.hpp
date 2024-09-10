typename enable_if<
  typename gtl_and_3<
    y_pt_ed2,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_distance_type<PointType1>::type>::type
euclidean_distance(const PointType1& point1, const PointType2& point2) {
  return (std::sqrt)(
      static_cast<double>(distance_squared(point1, point2)));
}