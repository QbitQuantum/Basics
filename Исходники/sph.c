/* rotation of a sphere */
void SPHERE_Rotate (SPHERE *sph, double *point, double *vector, double angle)
{
  double R [9], omega [3];
  double (*ref_pnt) [3] = sph->ref_point,
	 (*cur_pnt) [3] = sph->cur_point;

  angle *=  ALG_PI / 180.0;
  COPY (vector, omega); 
  NORMALIZE (omega); 
  SCALE (omega, angle);
  EXPMAP (omega, R);
  SUB (sph->cur_center, point, omega);
  NVADDMUL (point, R, omega, sph->cur_center);
  COPY (sph->cur_center, sph->ref_center);

  for (int i = 0; i < 3; i ++)
  {
    SUB (cur_pnt [i], point, omega);
    NVADDMUL (point, R, omega, cur_pnt [i]);
    COPY (cur_pnt [i], ref_pnt [i]);
  }
}