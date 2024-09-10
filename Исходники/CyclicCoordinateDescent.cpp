bool Animation::CyclicCoordinateDescent::solve(Math::Vector3f target, float maxAngle)
{
	Math::Vector3f constraint;
	Math::Vector3f lastPosition(0.0f);
	Math::Vector3f lastNodePosition(0.0f);

	do
	{
		lastNodePosition[0] = m_lastNode->getGlobalTransformation()(0, 3);
		lastNodePosition[1] = m_lastNode->getGlobalTransformation()(1, 3);
		lastNodePosition[2] = m_lastNode->getGlobalTransformation()(2, 3);
	
		if ((lastPosition-lastNodePosition).norm() < 0.001f)
			return false;

		lastPosition = lastNodePosition;
		constraint = target - lastNodePosition;

		ccd(constraint, maxAngle);
	} while(constraint.norm() > 0.1f);

	return true;
}