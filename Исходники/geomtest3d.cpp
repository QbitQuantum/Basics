int CalcSphereCenter (const Point<3> ** pts, Point<3> & c)
{
  Vec3d row1 (*pts[0], *pts[1]);
  Vec3d row2 (*pts[0], *pts[2]);
  Vec3d row3 (*pts[0], *pts[3]);

  Vec3d rhs(0.5 * (row1*row1),
	    0.5 * (row2*row2),
	    0.5 * (row3*row3));
  Transpose (row1, row2, row3);
  
  Vec3d sol;
  if (SolveLinearSystem (row1, row2, row3, rhs, sol))
    {
      (*testout) << "CalcSphereCenter: degenerated" << endl;
      return 1;
    }

  c = *pts[0] + sol;
  return 0;
}