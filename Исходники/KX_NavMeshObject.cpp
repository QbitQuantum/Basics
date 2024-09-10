MT_Point3 KX_NavMeshObject::TransformToLocalCoords(const MT_Point3& wpos)
{
	MT_Matrix3x3 orientation = NodeGetWorldOrientation();
	const MT_Vector3& scaling = NodeGetWorldScaling();
	orientation.scale(scaling[0], scaling[1], scaling[2]);
	MT_Transform worldtr(NodeGetWorldPosition(), orientation); 
	MT_Transform invworldtr;
	invworldtr.invert(worldtr);
	MT_Point3 lpos = invworldtr(wpos);
	return lpos;
}