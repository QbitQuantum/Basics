/**************************************************************************
|
|     Method: FindNearestPointOfParallelLineSegments
|
|    Purpose: Given two lines (segments) that are known to be parallel, find
|             a representative point on each that is nearest to the other. If
|             the lines are considered to be finite then it is possible that there
|             is one true point on each line that is nearest to the other. This
|             code properly handles this case.
|
|             This is the most difficult line intersection case to handle, since
|             there is potentially a family, or locus of points on each line/segment
|             that are nearest to the other.
| Parameters: Input:
|             ------
|             A1x, A1y, A1z   - Coordinates of first defining point of line/segment A
|             A2x, A2y, A2z   - Coordinates of second defining point of line/segment A
|             Lax, Lay, Laz   - Vector from (A1x, A1y, A1z) to the (A2x, A2y, A2z).
|             B1x, B1y, B1z   - Coordinates of first defining point of line/segment B
|             B2x, B2y, B2z   - Coordinates of second defining point of line/segment B
|             Lbx, Lby, Lbz   - Vector from (B1x, B1y, B1z) to the (B2x, B2y, B2z).
|             infinite_lines  - set to true if lines are to be treated as infinite
|             epsilon_squared - tolerance value to be used to check for degenerate
|                               and parallel lines, and to check for true intersection.
|
|             Output:
|             -------
|             PointOnSegAx,   - Coordinates of the point on segment A that are nearest
|             PointOnSegAy,     to segment B. This corresponds to point C in the text.
|             PointOnSegAz
|             PointOnSegBx,   - Coordinates of the point on segment B that are nearest
|             PointOnSegBy,     to segment A. This corresponds to point D in the text.
|             PointOnSegBz

**************************************************************************/
void FindNearestPointOfParallelLineSegments(number A1x, number A1y, number A1z,
                                            number A2x, number A2y, number A2z,
                                            number Lax, number Lay, number Laz,
                                            number B1x, number B1y, number B1z,
                                            number B2x, number B2y, number B2z,
                                            number Lbx, number Lby, number Lbz,
                                            bool infinite_lines, number epsilon_squared,
                                            number &PointOnSegAx, number &PointOnSegAy, number &PointOnSegAz,
                                            number &PointOnSegBx, number &PointOnSegBy, number &PointOnSegBz)
{
  number s[2] = {0, 0};
  number temp;
  FindNearestPointOnLineSegment(A1x, A1y, A1z, Lax, Lay, Laz, B1x, B1y, B1z,
                                true, epsilon_squared, PointOnSegAx, PointOnSegAy, PointOnSegAz, s[0]);
  if (true == infinite_lines)
  {
    PointOnSegBx = B1x;
    PointOnSegBy = B1y;
    PointOnSegBz = B1z;
  }
  else
  {
    number tp[3];
    FindNearestPointOnLineSegment(A1x, A1y, A1z, Lax, Lay, Laz, B2x, B2y, B2z,
                                  true, epsilon_squared, tp[0], tp[1], tp[2], s[1]);
    if (s[0] < 0.f && s[1] < 0.f)
    {
      PointOnSegAx = A1x;
      PointOnSegAy = A1y;
      PointOnSegAz = A1z;
      if (s[0] < s[1])
      {
        PointOnSegBx = B2x;
        PointOnSegBy = B2y;
        PointOnSegBz = B2z;
      }
      else
      {
        PointOnSegBx = B1x;
        PointOnSegBy = B1y;
        PointOnSegBz = B1z;
      }
    }
    else if (s[0] > 1.f && s[1] > 1.f)
    {
      PointOnSegAx = A2x;
      PointOnSegAy = A2y;
      PointOnSegAz = A2z;
      if (s[0] < s[1])
      {
        PointOnSegBx = B1x;
        PointOnSegBy = B1y;
        PointOnSegBz = B1z;
      }
      else
      {
        PointOnSegBx = B2x;
        PointOnSegBy = B2y;
        PointOnSegBz = B2z;
      }
    }
    else
    {
      temp = 0.5f*(FMAX(0.0f, FMIN(1.0f, s[0])) + FMAX(0.0f, FMIN(1.0f, s[1])));
      PointOnSegAx = (A1x + temp * Lax);
      PointOnSegAy = (A1y + temp * Lay);
      PointOnSegAz = (A1z + temp * Laz);
      FindNearestPointOnLineSegment(B1x, B1y, B1z, Lbx, Lby, Lbz,
                                    PointOnSegAx, PointOnSegAy, PointOnSegAz, true,
                                    epsilon_squared, PointOnSegBx, PointOnSegBy, PointOnSegBz, temp);
    }
  }
}