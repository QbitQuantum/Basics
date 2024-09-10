static void
_cogl_texture_iter_update (CoglTextureIter *iter)
{
  float t_2;
  float frac_part;

  frac_part = modff (iter->pos, &iter->next_pos);

  /* modff rounds the int part towards zero so we need to add one if
     we're meant to be heading away from zero */
  if (iter->pos >= 0.0f || frac_part == 0.0f)
    iter->next_pos += 1.0f;

  if (iter->next_pos > iter->end)
    t_2 = iter->end;
  else
    t_2 = iter->next_pos;

  if (iter->flipped)
    {
      iter->t_1 = t_2;
      iter->t_2 = iter->pos;
    }
  else
    {
      iter->t_1 = iter->pos;
      iter->t_2 = t_2;
    }
}