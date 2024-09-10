inline BOOL checkOctreeInCamSphere(const Engine::Octree *octree, const Engine::PerspCamera *cam)
{
	const XMVECTOR octree_position = XMLoadFloat3(&octree->position);
	const FLOAT distance = XMVectorGetX(XMVector3Length(octree_position - cam->getFrusSpherePosition()));

	if (distance < octree->radius + cam->getFrusSphereRadius())
		return TRUE;
	return FALSE;
}