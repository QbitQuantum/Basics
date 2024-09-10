smpl_t
aubio_db_spl (fvec_t * o)
{
  return 10. * LOG10 (aubio_level_lin (o));
}