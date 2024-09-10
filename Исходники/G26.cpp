mesh_index_pair find_closest_circle_to_print(const float &X, const float &Y) {
  float closest = 99999.99;
  mesh_index_pair return_val;

  return_val.x_index = return_val.y_index = -1;

  for (uint8_t i = 0; i < GRID_MAX_POINTS_X; i++) {
    for (uint8_t j = 0; j < GRID_MAX_POINTS_Y; j++) {
      if (!is_bitmap_set(circle_flags, i, j)) {
        const float mx = _GET_MESH_X(i),  // We found a circle that needs to be printed
                    my = _GET_MESH_Y(j);

        // Get the distance to this intersection
        float f = HYPOT(X - mx, Y - my);

        // It is possible that we are being called with the values
        // to let us find the closest circle to the start position.
        // But if this is not the case, add a small weighting to the
        // distance calculation to help it choose a better place to continue.
        f += HYPOT(g26_x_pos - mx, g26_y_pos - my) / 15.0;

        // Add in the specified amount of Random Noise to our search
        if (random_deviation > 1.0)
          f += random(0.0, random_deviation);

        if (f < closest) {
          closest = f;              // We found a closer location that is still
          return_val.x_index = i;   // un-printed  --- save the data for it
          return_val.y_index = j;
          return_val.distance = closest;
        }
      }
    }
  }
  bitmap_set(circle_flags, return_val.x_index, return_val.y_index);   // Mark this location as done.
  return return_val;
}