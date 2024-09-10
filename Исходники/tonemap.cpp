sp_image LinearToneMapper::tonemap(const sp_image& input) const
{
  spectrum M = accumulate(input.begin(), input.end(), spectrum::one, spectrum::max);
  scalar cM = max(max(M.x, M.y), M.z);

  sp_image output(input.width(), input.height());
  transform(input.begin(), input.end(), output.begin(),
            [&](const spectrum& s) { return s / cM; });

  return output;
}