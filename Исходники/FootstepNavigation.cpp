bool
FootstepNavigation::getFootstep(const tf::Pose& from,
                                const State& from_planned,
		                            const State& to,
		                            humanoid_nav_msgs::StepTarget* footstep)
{
  // get footstep to reach 'to' from 'from'
  tf::Transform step = from.inverse() *
                       tf::Pose(tf::createQuaternionFromYaw(to.getTheta()),
                                tf::Point(to.getX(), to.getY(), 0.0));

  // set the footstep
  footstep->pose.x = step.getOrigin().x();
  footstep->pose.y = step.getOrigin().y();
  footstep->pose.theta = tf::getYaw(step.getRotation());
  if (to.getLeg() == LEFT)
    footstep->leg = humanoid_nav_msgs::StepTarget::left;
  else // to.leg == RIGHT
    footstep->leg = humanoid_nav_msgs::StepTarget::right;


  /* check if the footstep can be performed by the NAO robot ******************/

  // check if the step lies within the executable range
  if (performable(*footstep))
  {
    return true;
  }
  else
  {
    // check if there is only a minor divergence between the current support
	// foot and the foot placement used during the plannig task: in such a case
	// perform the step that has been used during the planning
    float step_diff_x = fabs(from.getOrigin().x() - from_planned.getX());
    float step_diff_y = fabs(from.getOrigin().y() - from_planned.getY());
    float step_diff_theta = fabs(
        angles::shortest_angular_distance(
            tf::getYaw(from.getRotation()), from_planned.getTheta()));
    if (step_diff_x < ivAccuracyX && step_diff_y < ivAccuracyY &&
        step_diff_theta < ivAccuracyTheta)
    {
	  step = tf::Pose(tf::createQuaternionFromYaw(from_planned.getTheta()),
	                  tf::Point(from_planned.getX(), from_planned.getY(), 0.0)
	                  ).inverse() *
		     tf::Pose(tf::createQuaternionFromYaw(to.getTheta()),
				      tf::Point(to.getX(), to.getY(), 0.0));

	  footstep->pose.x = step.getOrigin().x();
	  footstep->pose.y = step.getOrigin().y();
	  footstep->pose.theta = tf::getYaw(step.getRotation());

	  return true;
    }

    return false;
  }

//  // ALTERNATIVE: clip the footstep into the executable range; if nothing was
//  // clipped: perform; if too much was clipped: do not perform
//  humanoid_nav_msgs::ClipFootstep footstep_clip;
//  footstep_clip.request.step = footstep;
//  ivClipFootstepSrv.call(footstep_clip);
//
//  if (performanceValid(footstep_clip))
//  {
//  	footstep.pose.x = footstep_clip.response.step.pose.x;
//  	footstep.pose.y = footstep_clip.response.step.pose.y;
//  	footstep.pose.theta = footstep_clip.response.step.pose.theta;
//  	return true;
//  }
//  else
//  {
//    return false;
//  }
}