Eigen::Vector3f RobotNodeSet::getCoM()
{
	Eigen::Vector3f res;
	res.setZero();

	float m = getMass();
	if (m<=0)
		return res;

	for (size_t i=0;i<this->robotNodes.size();i++)
		res += robotNodes[i]->getCoMGlobal() * robotNodes[i]->getMass() / m;

	return res;
}