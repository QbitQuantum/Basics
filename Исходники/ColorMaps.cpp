/**
 * Get an intensity lookup table to adjust the apparent brightness of a
 * displayed image.  The lookup table makes an adjustment to the image
 * intensity similar to a gamma correction, but over a wide range.  The
 * table will be created with the specified number of entries and the
 * entries will increase monotonically (but non-linearly) from 0 to 1.
 *
 * @param control_s        Control parameter between 0 and 100.  When
 *                         the parameter is at 0, the look up table is
 *                         linear.  As the parameter increases, low
 *                         intensity values will increasingly get larger
 *                         scale factors.
 * @param n_entries        The number of entries to create in the table.
 *                         This controls the resolution of the mapping and
 *                         should be quite large (10,000-100,000) to preserve
 *                         smooth color transitions even a lower intensity
 *                         values, when the control parameter is large.
 * @returns :: intensity lookup table
 */
std::vector<double> ColorMaps::GetIntensityMap(double control_s,
                                               size_t n_entries) {

  std::vector<double> intensity_table;
  intensity_table.resize(n_entries);
  // restrict control range to [0,100]
  double MAX_CONTROL = 100.0;
  if (control_s > MAX_CONTROL) {
    control_s = MAX_CONTROL;
  } else if (control_s < 0.0) {
    control_s = 0.0;
  }

  if (control_s == 0.0) // just use linear scale, 0 -> 1
  {
    for (size_t i = 0; i < n_entries; i++) {
      intensity_table[i] = (double)i / (double)(n_entries - 1);
    }
  } else // build log-shaped correction scale
  {
    // first map control value
    // exponentially to make the control
    // parameter act more linearly
    double s = exp(20.0 * control_s / MAX_CONTROL) + 0.1;
    double scale = 1.0 / log(s);
    for (size_t i = 0; i < n_entries - 1; i++) {
      intensity_table[i] = scale * log1p((s - 1.0) * static_cast<double>(i) /
                                         static_cast<double>(n_entries - 1));
    }
    intensity_table[n_entries - 1] = 1.0; // this could have been calculated
                                          // by running the loop one step
                                          // further, but due to rounding
                                          // errors, it might exceed 1.
  }
  return intensity_table;
}