bool	btClampNormal(const btVector3& edge,const btVector3& tri_normal_org,const btVector3& localContactNormalOnB, btScalar correctedEdgeAngle, btVector3 & clampedLocalNormal)
{
	btVector3 tri_normal = tri_normal_org;
	//we only have a local triangle normal, not a local contact normal -> only normal in world space...
	//either compute the current angle all in local space, or all in world space

	btVector3 edgeCross = edge.cross(tri_normal).normalize();
	btScalar curAngle = btGetAngle(edgeCross,tri_normal,localContactNormalOnB);

	if (correctedEdgeAngle<0)
	{
		if (curAngle < correctedEdgeAngle)
		{
			btScalar diffAngle = correctedEdgeAngle-curAngle;
			btQuaternion rotation(edge,diffAngle );
			clampedLocalNormal = btMatrix3x3(rotation)*localContactNormalOnB;
			return true;
		}
	}

	if (correctedEdgeAngle>=0)
	{
		if (curAngle > correctedEdgeAngle)
		{
			btScalar diffAngle = correctedEdgeAngle-curAngle;
			btQuaternion rotation(edge,diffAngle );
			clampedLocalNormal = btMatrix3x3(rotation)*localContactNormalOnB;
			return true;
		}
	}
	return false;
}