lean::com_ptr<const beCore::ReflectedComponent, lean::critical_ref> MeshCompound<Material>::GetReflectedComponent(uint4 idx) const
{
	LEAN_ASSERT(idx < m_meshes.size());
	return Reflect(m_materials[idx]);
}