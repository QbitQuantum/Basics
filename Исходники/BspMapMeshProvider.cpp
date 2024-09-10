unsigned int CBspMapMeshProvider::FindLeaf(const CVector3& searchPosition) const
{
	int32 index = 0;
	const Bsp::NodeArray& nodes(m_bspFile->GetNodes());
	const Bsp::PlaneArray& planes(m_bspFile->GetPlanes());

	while(index >= 0)
	{
		const Bsp::NODE& node = nodes[index];
		const Bsp::PLANE& plane = planes[node.plane];

		CVector3 planeNormal = Bsp::ConvertToAthenaCoord(plane.normal);
		float distance = planeNormal.Dot(searchPosition) - plane.distance;

		if(distance >= 0)
		{
			index = node.children[0];
		}
		else
		{
			index = node.children[1];
		}
	}
	return -index - 1;
}