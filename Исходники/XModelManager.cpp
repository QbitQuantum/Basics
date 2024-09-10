void _XModelManager::DestroyData()
{
	std::for_each(m_svAnimMeshAbstractclassr.begin(), m_svAnimMeshAbstractclassr.end(), DELETEOBJECT());
	m_svAnimMeshAbstractclassr.clear();	

	SAFE_DELETE(m_pDefaultAnimMeshAbstractClass);
}