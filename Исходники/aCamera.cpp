void ACamera::set(const vec3& eyepos, const vec3& look, const vec3& up)
{
   mEye = eyepos;
   mN = eyepos - look;
   mV = up.Cross(mN);
   mU = mN.Cross(mV);
   mRadius = mN.Length(); // cache this distance

   mU.Normalize();
   mV.Normalize();
   mN.Normalize();
}