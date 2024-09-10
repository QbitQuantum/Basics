static inline float
to_float (hb_position_t v)
{
  return scalblnf (v, -8);
}