Real
CylindricalRankTwoAux::computeValue()
{
  Point loc_from_center = _q_point[_qp] - _center_point;

  Real theta = std::atan2(loc_from_center(1), loc_from_center(0));
  RankTwoTensor R;
  R(0, 0) = std::cos(theta);
  R(0, 1) = std::sin(theta);
  R(1, 0) = -std::sin(theta);
  R(1, 1) = std::cos(theta);

  RankTwoTensor rotated_tensor = R * _tensor[_qp] * R.transpose();

  return rotated_tensor(_i, _j);
}