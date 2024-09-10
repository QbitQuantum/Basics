void RangeScanner::construct_laser_stripe(Vector3 _startPt, double _shift, double _laserFOV, LaserStripe& stripe)  {
	Vector3 laser_start = _startPt-laser_pos;
	laser_start.normalize();
	Vector3 baseline = sensor.camera_pos() - laser_pos;
	baseline.normalize();

	Vector3 rotation_axis = laser_start.cross(baseline);
	rotation_axis.normalize();

	// rotate laser start about rotation axis, by _shift amount and width _laserFOV
	RotationMatrix rotation(rotation_axis, _shift);
	Vector3 rotated_laser_centered = rotation.rotate(laser_start);
	RotationMatrix minus_rotation(rotation_axis, _shift-0.5*_laserFOV);
	Vector3 rotated_laser_minus = minus_rotation.rotate(laser_start);
	RotationMatrix plus_rotation(rotation_axis, _shift+0.5*_laserFOV);
	Vector3 rotated_laser_plus = plus_rotation.rotate(laser_start);

	//cout << "laser stripe: " << rotated_laser_minus << " : " << rotated_laser_centered << " : " << rotated_laser_plus << endl;

	// obtain laser stripe planes
	//Vector3 minus_n = rotated_laser_minus.cross(rotation_axis);
	Vector3 minus_n = rotation_axis.cross(rotated_laser_minus);
	minus_n.normalize();
	double minus_d = -(minus_n.dotProduct(laser_pos));

	//Vector3 plus_n = rotation_axis.cross(rotated_laser_plus);
	Vector3 plus_n = rotated_laser_plus.cross(rotation_axis);
	plus_n.normalize();
	double plus_d = -(plus_n.dotProduct(laser_pos));

	Vector3 centered_n = rotated_laser_centered.cross(rotation_axis);
	centered_n.normalize();
	double centered_d = -(centered_n.dotProduct(laser_pos));

	stripe = LaserStripe(minus_n, minus_d, centered_n, centered_d, plus_n, plus_d);
}