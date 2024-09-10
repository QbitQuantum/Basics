void CUmbralMap::GetMeshes(Palleon::MeshArray& meshes, const Palleon::CCamera* camera)
{
	auto cameraFrustum = camera->GetFrustum();
	for(const auto& instance : m_instances)
	{
		auto boundingSphere = instance->GetWorldBoundingSphere();
		if(cameraFrustum.Intersects(boundingSphere))
		{
			meshes.push_back(instance.get());
		}
	}
}