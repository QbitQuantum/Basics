Eigen::Quaterniond UAS::transform_frame(const Eigen::Quaterniond &q)
{
	return FRAME_ROTATE_Q * q * FRAME_ROTATE_Q.inverse();
}