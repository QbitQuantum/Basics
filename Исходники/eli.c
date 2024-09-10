/* update ellipsoid according to the given motion */
void ELLIP_Update (ELLIP *eli, void *body, void *shp, MOTION motion)
{
  SGP sgp = {shp, eli, GOBJ_ELLIP, NULL};
  double *ref = eli->ref_center,
	 (*ref_pnt) [3] = eli->ref_point,
	 *cur = eli->cur_center,
	 (*cur_pnt) [3] = eli->cur_point;

  if (motion)
  { 
    motion (body, &sgp, ref, cur);
    motion (body, &sgp, ref_pnt [0], cur_pnt [0]);
    motion (body, &sgp, ref_pnt [1], cur_pnt [1]);
    motion (body, &sgp, ref_pnt [2], cur_pnt [2]);

    BODY *bod = body;

    switch (bod->kind)
    {
    case OBS:
    case RIG:
    {
      double *R1 = bod->conf, *R0 = eli->ref_rot, *rot = eli->cur_rot;

      NNMUL (R1, R0, rot);
    }
    break;
    case PRB:
    {
      double *F = bod->conf, *sca0 = eli->ref_sca, *rot0 = eli->ref_rot, *sca1 = eli->cur_sca, *rot1 = eli->cur_rot;
      double U[9] = {1.0/(sca0[0]*sca0[0]), 0.0, 0.0, 0.0, 1.0/(sca0[1]*sca0[1]), 0.0, 0.0, 0.0, 1.0/(sca0[2]*sca0[2])};
      double A0[9], iF[9], det, X[3], Y[9], A[9];

      NTMUL (U, rot0, Y);
      NNMUL (rot0, Y, A0);

      TNCOPY (F, Y); /* T --> since deformation gradient is stored row-wise */

      INVERT (Y, iF, det);
      ASSERT_TEXT (det > 0.0, "det(F) <= 0.0 during ellipsoid update");

      NNMUL (A0, iF, Y);
      TNMUL (iF, Y, A);

      ASSERT_TEXT (lapack_dsyev ('V', 'U', 3, A, 3, X, Y, 9) == 0, "Eigen decomposition failed during ellipsoid update");

      if (DET(A) < 0.0) /* det(A) is 1.0 or -1.0 */
      {
	SCALE9 (A, -1.0); /* keep positive space orientation */
      }

      NNCOPY (A, rot1);

      sca1[0] = 1.0/sqrt(X[0]);
      sca1[1] = 1.0/sqrt(X[1]);
      sca1[2] = 1.0/sqrt(X[2]);
    }
    break;
    default:
    {
      ASSERT_TEXT (0, "Invalid body kind during ellipsoid update");
    }
    break;
    }
  }
  else
  {
    COPY (ref, cur);
    COPY (ref_pnt [0], cur_pnt [0]);
    COPY (ref_pnt [1], cur_pnt [1]);
    COPY (ref_pnt [2], cur_pnt [2]);

    sca_rot (eli->ref_center, eli->ref_point, eli->ref_sca, eli->ref_rot);

    COPY (eli->ref_sca, eli->cur_sca);
    NNCOPY (eli->ref_rot, eli->cur_rot);
  }
}