bool MoleculeCisTrans::sameline (const Vec3f &beg, const Vec3f &end, const Vec3f &nei_beg)
{
   Vec3f norm_diff, norm_beg;

   norm_diff.diff(beg, end);
   if (!norm_diff.normalize())
      return true;
   norm_beg.diff(nei_beg, beg);
   if (!norm_beg.normalize())
      return true;

   Vec3f cross;
   cross.cross(norm_diff, norm_beg);
   float sin_angle = cross.lengthSqr();
   if (fabs(sin_angle) < 0.01)
      return true;

   return false;
}