//--------------------------------------------------------------------------------
Vector3 CObjectSelectTool::GetGizmoIntersect( Ray &pickRay, Plane &planetouse )
{
	std::pair<bool,Real> result;

	result = pickRay.intersects(planetouse);

	if (result.first)
	{
		Vector3 AxisX = Vector3::ZERO;
		Vector3 AxisY = Vector3::ZERO;
		Vector3 AxisZ = Vector3::ZERO;

		Quaternion qOrient = GetEditor()->GetSceneManager()->getRootSceneNode()->getOrientation();

		if(mLockedAxis)
		{
			if(mLockedAxis & AXIS_X) 
				AxisX = qOrient.xAxis();
			if(mLockedAxis & AXIS_Y) 
				AxisY = qOrient.yAxis();
			if(mLockedAxis & AXIS_Z) 
				AxisZ = qOrient.zAxis();
		}
		else
		{
			AxisX = qOrient.xAxis();
			AxisY = qOrient.yAxis();
			AxisZ = qOrient.zAxis();
		}

		Vector3 Proj = pickRay.getPoint(result.second) - mSelcetEntityPos;
		Vector3 vPos1 = (AxisX.dotProduct(Proj) * AxisX);
		Vector3 vPos2 = (AxisY.dotProduct(Proj) * AxisY);
		Vector3 vPos3 = (AxisZ.dotProduct(Proj) * AxisZ);
		Vector3 vPos = vPos1 + vPos2 + vPos3;

		mLastTranslationDelta = vPos;
		return vPos;
	}
	return mLastTranslationDelta;
}