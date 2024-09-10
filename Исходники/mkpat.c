static void
compute_grids(void)
{
#ifdef GRID_OPT
  /*                       element : .  X  O  x  o  h  a  ! */
  static const uint32 and_mask[] = { 3, 3, 3, 1, 2, 1, 3, 1 };
  static const uint32 val_mask[] = { 0, 2, 1, 0, 0, 0, 0, 0 };

  int ll;  /* iterate over rotations */
  int k;   /* iterate over elements */

  for (ll=0; ll < 8; ++ll) {
    for (k=0; k<el; ++k) {
      int di, dj;

      TRANSFORM(elements[k].x - ci, elements[k].y - cj, &di, &dj, ll);
      ++di;
      ++dj;
      if (di >= 0 && di < 4 && dj >= 0 && dj < 4) {
	pattern[patno].and_mask[ll]
	  |= and_mask[elements[k].att] << (30 - di * 8 - dj * 2);
	pattern[patno].val_mask[ll]
	  |= val_mask[elements[k].att] << (30 - di * 8 - dj * 2);
      }
    }
  }
#endif
}