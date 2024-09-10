Eigen::Isometry3f LDrawPartReference::getTransform()
{
	Eigen::Isometry3f tf = Eigen::Isometry3f::Identity();
	for (int i = 0; i < 3; ++i)
	{
		tf.translation()[i] = position[i] * LDRAW_UNITS_TO_M;
	}
	Eigen::Matrix3f rot;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			rot(i,j) = rotation[i][j];
		}
	}
	tf.rotate(rot);

	return tf;
}