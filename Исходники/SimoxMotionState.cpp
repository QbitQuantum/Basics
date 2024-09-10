void SimoxMotionState::updateTransform()
{
	//Eigen::Matrix4f m = Eigen::Matrix4f::Identity();
	//m.block(0,3,3,1) = com;
    setWorldTransform(m_startWorldTrans);
}