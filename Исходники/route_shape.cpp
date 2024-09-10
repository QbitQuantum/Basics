glsl::vec2 GetUV(m2::RectF const & texRect, float normU, float normV)
{
  return glsl::vec2(texRect.minX() * (1.0f - normU) + texRect.maxX() * normU,
                    texRect.minY() * (1.0f - normV) + texRect.maxY() * normV);
}