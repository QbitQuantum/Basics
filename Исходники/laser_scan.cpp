inline tf::Transform interpolateTF(tf::Transform start, tf::Transform end, double ratio)
{
	tf::Vector3 lerp_pos = start.getOrigin().lerp(end.getOrigin(), ratio);
	tf::Quaternion lerp_rot = start.getRotation().slerp(end.getRotation(), ratio);
	
	return tf::Transform(lerp_rot, lerp_pos);
}