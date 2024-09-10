void
tgPose::RotateAxis (vec3 r)
{
  // 	tgQuaternion q2;
  // 	q2.fromEuler(rot.x,rot.y,rot.z);
  // 	q = q2 * q;
  // 	q.normalise();
  tgQuaternion q2;
  float a = r.length ();
  r.normalize ();
  q2.fromAxis (r, a);
  q = q2 * q;
  q.normalise ();
}