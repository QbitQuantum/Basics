void DisplayTree::GetShapeBounds(
    const Shape& shape,
    const Matrix& transform,
    double* x_min_out,
    double* x_max_out,
    double* y_min_out,
    double* y_max_out) {
  const Rect& r = shape.shape_bounds;
  double x_min = r.x_min;
  double x_max = r.x_max;
  double y_min = r.y_min;
  double y_max = r.y_max;
  if (shape.edge_bounds.is_valid()) {
    x_min = std::min(x_min, (double)shape.edge_bounds.x_min);
    y_min = std::min(y_min, (double)shape.edge_bounds.y_min);
    x_max = std::max(x_max, (double)shape.edge_bounds.x_max);
    y_max = std::max(y_max, (double)shape.edge_bounds.y_max);
  }
  transform.transform(&x_min, &y_min);
  transform.transform(&x_max, &y_max);
  if (*x_min_out == 0 && *x_max_out == 0 &&
      *y_min_out == 0 && *y_max_out == 0) {
    *x_min_out = x_min;
    *x_max_out = x_max;
    *y_min_out = y_min;
    *y_max_out = y_max;
  } else {
    *x_min_out = std::min(x_max, std::min(x_min, *x_min_out));
    *x_max_out = std::max(x_min, std::max(x_max, *x_max_out));
    *y_min_out = std::min(y_max, std::min(y_min, *y_min_out));
    *y_max_out = std::max(y_min, std::max(y_max, *y_max_out));
  }
}