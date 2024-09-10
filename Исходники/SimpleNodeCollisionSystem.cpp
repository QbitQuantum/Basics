// checks for collision with the real meshes
bool SimpleNodeCollisionSystem::IntersectsMesh(const int lodLevel, const Ray& ray)
{
	// make sure the LOD level exists for this node
	assert(lodLevel < mNode->GetNumMeshes());

	// get the direct pointer to the mesh, from the smartpointer
	Mesh* mesh = mNode->GetMesh(lodLevel).GetPointer();

	// if there is no mesh, there cannot be an intersection
	if (mesh == NULL)
		return false;

	// check intersection with the mesh
	if (mesh->Intersects(ray, mNode))
		return true;

	// no intersection occured or the node isn't vaid
	return false;
}