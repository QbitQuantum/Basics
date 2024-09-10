void Frustum_Filter::init_z_near_z_far_depth
(
  const SfM_Data & sfm_data,
  const double zNear,
  const double zFar
)
{
  // If z_near & z_far are -1 and structure if not empty,
  //  compute the values for each camera and the structure
  const bool bComputed_Z = (zNear == -1. && zFar == -1.) && !sfm_data.structure.empty();
  if (bComputed_Z)  // Compute the near & far planes from the structure and view observations
  {
    for (Landmarks::const_iterator itL = sfm_data.GetLandmarks().begin();
      itL != sfm_data.GetLandmarks().end(); ++itL)
    {
      const Landmark & landmark = itL->second;
      const Vec3 & X = landmark.X;
      for (Observations::const_iterator iterO = landmark.obs.begin();
        iterO != landmark.obs.end(); ++iterO)
      {
        const IndexT id_view = iterO->first;
        const View * view = sfm_data.GetViews().at(id_view).get();
        if (!sfm_data.IsPoseAndIntrinsicDefined(view))
          continue;

        const Pose3 pose = sfm_data.GetPoseOrDie(view);
        const double z = Depth(pose.rotation(), pose.translation(), X);
        NearFarPlanesT::iterator itZ = z_near_z_far_perView.find(id_view);
        if (itZ != z_near_z_far_perView.end())
        {
          if ( z < itZ->second.first)
            itZ->second.first = z;
          else
          if ( z > itZ->second.second)
            itZ->second.second = z;
        }
        else
          z_near_z_far_perView[id_view] = {z,z};
      }
    }
  }
  else
  {
    // Init the same near & far limit for all the valid views
    for (Views::const_iterator it = sfm_data.GetViews().begin();
    it != sfm_data.GetViews().end(); ++it)
    {
      const View * view = it->second.get();
      if (!sfm_data.IsPoseAndIntrinsicDefined(view))
        continue;
      if (z_near_z_far_perView.find(view->id_view) == z_near_z_far_perView.end())
        z_near_z_far_perView[view->id_view] = {zNear, zFar};
    }
  }
}