static bool evalLocalAxes (const Vec3& dX, const Vec3& ddX,
                           Vec3& B, Vec3& N, double& B_len, double& N_len)
{
  B.cross(dX,ddX); // {B} = d{X} x dd{X}
  B_len = B.length();
  if (B_len < 1.0e-12)
  {
    // The cable is straigth, need to modify vector ddX

    Vec3 G1(dX);
    double normG1 = dX.length();
    G1 *= 1.0/(normG1*normG1); // Contra-variant basis vector

    B.cross(dX, ddX - (ddX*G1) * G1);
    B_len = B.length();
    if (B_len < 1.0e-10)
    {
      B.cross(dX, Vec3(-dX.y,dX.x,0.0));
      B_len = B.length();
      if (B_len < 1.0e-10)
      {
        // Last resort: Use algorithm from Tensor(const Vec3&) constructor
        if (fabs(dX.y) < fabs(dX.z))
        {
          // Define the normal vector, N, by projecting the global Y-axis
          // onto the normal plane of the tangent direction, dX
          N.x = -dX.y*dX.x;
          N.y =  dX.x*dX.x + dX.z*dX.z;
          N.z = -dX.y*dX.z;
          // Define the binormal vector B as the cross product of dX and N
          B.cross(dX,N);
        }
        else
        {
          // Define the binormal vector by projecting the global Z-axis
          // onto the normal plane of the tangent direction, dX
          B.x = -dX.z*dX.x;
          B.y = -dX.z*dX.y;
          B.z =  dX.x*dX.x + dX.y*dX.y;
        }
        B_len = B.length();
        if (B_len < 1.0e-10)
        {
          std::cerr <<" *** ElasticCable: Degenerated element, dX="<< dX
                    << std::endl;
          return false;
        }
      }
    }
  }

  B *= 1.0/B_len; // Unit binormal vector: {B}
  N.cross(B,dX);  // {N} = {B} x d{X}
  N_len = N.normalize(); // Unit normal vector: {N}

  return true;
}