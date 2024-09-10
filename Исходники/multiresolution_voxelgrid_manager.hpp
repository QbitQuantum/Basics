 inline void compare_xy(DistanceField2D& partial_field, sdf_cell& cell, int64_t x, int64_t y, int64_t x_offset, int64_t y_offset)
 {
     sdf_cell other = get_xy(partial_field, x + x_offset, y + y_offset);
     other.d1 += x_offset;
     other.d2 += y_offset;
     if (distance_squared(other) < distance_squared(cell))
     {
         cell = other;
     }
 }