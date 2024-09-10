double RadiusSum::getMaxDistance(const V3D &centre,
                                 const std::vector<double> &boundary_limits) {

  std::array<double, 2> Xs = {{boundary_limits[0], boundary_limits[1]}};
  std::array<double, 2> Ys = {{boundary_limits[2], boundary_limits[3]}};
  std::array<double, 2> Zs = {{0., 0.}};

  if (boundary_limits.size() == 6) {
    Zs[0] = boundary_limits[4];
    Zs[1] = boundary_limits[5];
  }

  double max_distance = 0;
  for (auto &x : Xs)
    for (auto &y : Ys)
      for (auto &z : Zs) {
        // define all the possible combinations for the limits

        double curr_distance = centre.distance(V3D(x, y, z));

        if (curr_distance > max_distance)
          max_distance = curr_distance; // keep the maximum distance.
      }
  return max_distance;
}