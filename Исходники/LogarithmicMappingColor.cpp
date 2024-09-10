RGBA LogarithmicMappingColor::getColor(const double &value, const unsigned int idColor) const {
  return LinearMappingColor::getColor(log1p(value), idColor);
}