int calc_radial_damage(const R_3DPoint &r1, float radius, int damage,
		       const bounding_cube &bcube, int &dmg)
{
  R_3DPoint cp;
  float d;
  int result = 0;
  bounding_cube bc = bcube;
  float rad_sq = radius * radius * hit_scaler;
  
  cp = bc.centerPoint();
  d = distance_squared(cp,r1);
  if (d <= rad_sq)
    {
      /* woops! */
      // dmg = (int) (((float)damage) * d / rad_sq);
      dmg = (int) (((float)damage) * (1.0 - (d / rad_sq)));
      result = 1;
    }
  return (result);
}