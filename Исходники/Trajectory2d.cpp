void Trajectory2d::shortcut()
{
  if (m_trajectory.empty())
  {
    return;
  }

  /* Transform each 'following' pose into the cs
   * of the 'current' pose. A violation to the desired
   * driving direction is found if
   *    x-value <= 0 and driving forward
   *    x-value >= 0 and driving backward
   */
  Pose2d temp;
  for (ContainerType::iterator current=m_trajectory.begin(),
       next=current+1;
       (current!=m_trajectory.end() && next!=m_trajectory.end());
       ++current, ++next)
  {
    temp = current->pose().inverse() * next->pose();
    if (((m_is_forward_trajectory && (temp.translation().x() <=0.)))
        || ((!m_is_forward_trajectory) && (temp.translation().x() >=0.)))
    {
      erase(next);
      --current; // step back to check the same place again
      next = current+1;
    }
  }

  // recalculate curvature.
  if (curvatureAvailable())
  {
    calculateCurvature();
  }
}