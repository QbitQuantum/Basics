/*!
 * Evaluates curvature at (x,y,z) through discrete finite difference scheme.
 */
float Implicit::GetCurvature(float x, float y, float z) const
{
  const float& d = mDelta;
  float r2d = 1.0f/(2.0f*d);

  Vector3<float> gradient = -GetGradient(x,y,z);
  Vector4<float> ex_gradient(gradient[0],gradient[1],gradient[2],1.0f);
  Vector3<float> gradientsP[3] = {	-GetGradient(x + d, y, z) , -GetGradient(x, y + d, z) , -GetGradient(x, y, z + d) };
  Vector3<float> gradientsN[3] = {	-GetGradient(x - d, y, z) , -GetGradient(x, y - d, z) , -GetGradient(x, y, z - d) };

  float hessian[4][4] = {
	  {	( gradientsP[0][0] - gradientsN[0][0] )*r2d,	( gradientsP[1][0] - gradientsN[1][0] )*r2d,	( gradientsP[2][0] - gradientsN[2][0] )*r2d ,	0.0f},
	  {	( gradientsP[0][1] - gradientsN[0][1] )*r2d,	( gradientsP[1][1] - gradientsN[1][1] )*r2d,	( gradientsP[2][1] - gradientsN[2][1] )*r2d ,	0.0f},
	  {	( gradientsP[0][2] - gradientsN[0][2] )*r2d,	( gradientsP[1][2] - gradientsN[1][2] )*r2d,	( gradientsP[2][2] - gradientsN[2][2] )*r2d ,	0.0f},
	  {	0.0f,											0.0f,											0.0f,											1.0f}
  };

  float hTrace = hessian[0][0] + hessian[1][1] + hessian[2][2];
  //the - 1 is just because we have a 4d vector so the dot product has a 1 at the end we need to get rid of
  //3x3 matrix is all we need here really
  float hMult = ex_gradient*(Matrix4x4<float>(hessian)*ex_gradient) - 1.0f;
  float gradLength = gradient.Length();

  float gradLengthSq = gradient*gradient;

  float curv = (hMult - gradLengthSq*hTrace)/(2.0f* gradLengthSq*gradLength);
  return curv;
}