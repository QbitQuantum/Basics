/*! This uses a slightly different similarity metric, more in tune with what we use for clustering
  but different from the one used during actual grasp planning, which will lead to inconsistencies
  in the sampling. This *should* not create real problems though.

  The angular threshold does not really play any role here as compliant copies *should* not have
  any angular differences.
*/
bool CompliantGraspCopyTask::similarity(const transf &t1, const transf &t2)
{
  //7.5mm distance threshold
  double DISTANCE_THRESHOLD = 7.5;
  //15 degrees angular threshold
  double ANGULAR_THRESHOLD = 0.26;

  vec3 dvec = t1.translation() - t2.translation();
  double d = dvec.len();
  if (d > DISTANCE_THRESHOLD) { return false; }

  Quaternion qvec = t1.rotation() * t2.rotation().inverse();
  vec3 axis; double angle;
  qvec.ToAngleAxis(angle, axis);
  if (angle >  M_PI) { angle -= 2 * M_PI; }
  if (angle < -M_PI) { angle += 2 * M_PI; }
  if (fabs(angle) > ANGULAR_THRESHOLD) { return false; }

  return true;
}