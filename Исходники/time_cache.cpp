void
TimeCache::interpolate(const TransformStorage& one,
                       const TransformStorage& two,
                       fawkes::Time time, TransformStorage& output)
{
  // Check for zero distance case
  if( two.stamp == one.stamp ) {
    output = two;
    return;
  }
  //Calculate the ratio
  btScalar ratio =
    (time.in_sec() - one.stamp.in_sec()) /
    (two.stamp.in_sec() - one.stamp.in_sec());

  //Interpolate translation
  output.translation.setInterpolate3(one.translation, two.translation, ratio);

  //Interpolate rotation
  output.rotation = slerp( one.rotation, two.rotation, ratio);

  output.stamp = one.stamp;
  output.frame_id = one.frame_id;
  output.child_frame_id = one.child_frame_id;
}