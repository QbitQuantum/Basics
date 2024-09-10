sp_image ReinhardLocal::tonemap(const sp_image& input) const
{
  const auto w = input.width(), h = input.height();
  vector<scalar> luminances(w*h);
  scalar mean_log_luminance;
  reinhard_tonemap_aux(input, luminances, mean_log_luminance);
  scalar l_mult = opt.key_value / mean_log_luminance;

  // Explicitly compute L(x, y) as specified in equation 2.
  transform(luminances.begin(), luminances.end(), luminances.begin(),
            [=](scalar L) { return L * l_mult; });

  auto center_surround = center_surround_functions(w, h, luminances, opt);

  vector<scalar> display_lum(input.size());
  for (auto i = 0u; i < luminances.size(); ++i)
  {
    int scale = 0;
    for ( ; scale < opt.num_scales - 1; ++scale)
    {
      if (fabs(center_surround[scale][i].first) > opt.scale_selection_threshhold)
        break;
    }
    display_lum[i] = luminances[i] / (1 + center_surround[scale][i].second);
  }

  sp_image output(w, h);
  transform(display_lum.begin(), display_lum.end(), input.begin(), output.begin(),
            [](scalar lum, const spectrum& s) { return s.rescale_luminance(lum).clamp(); });

  return CutoffToneMapper().tonemap(output);
}