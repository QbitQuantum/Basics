/*! A helper function that gives the change between two transforms, but
  disregards any change along the approach direction of the hand. I'm not
  really sure this is needed anymore, might be replaced in the future.
*/
double
OnLinePlanner::distanceOutsideApproach(const transf &solTran, const transf &handTran)
{
  double max_angle = M_PI / 4.0;
  double max_dist = 50.0;
  double f;
  //relative transform between the two
  transf changeTran = handTran.inverse() % solTran;

  //DBGP("T1: " << solTran.translation());
  //DBGP("T2: " << handTran.translation());
  //DBGP("Change: " << changeTran.translation() );

  //get change in terms of approach direction
  changeTran = mHand->getApproachTran().inverse() % changeTran % mHand->getApproachTran();

  //get angular change
  double angle; vec3 axis;
  Eigen::AngleAxisd aa(changeTran.rotation());
  axis = aa.axis();
  angle = aa.angle();

  //get translation change
  vec3 approach = changeTran.translation();
  //change along approach direction does not count as distance
  //DBGP("Approach: " << approach);
  if (approach.z() < 0) {
    f = -1.0;
  } else {
    f = 1.0;
  }
  approach.z() = 0;
  double dist = approach.norm();

  //compute final value
  if (angle > M_PI) { angle -= 2 * M_PI; }
  if (angle < -M_PI) { angle += 2 * M_PI; }
  angle = fabs(angle) / max_angle ;
  dist = dist / max_dist;
  //DBGP("Angle " << angle << "; dist " << dist << std::endl);
  return f * std::max(angle, dist);
}