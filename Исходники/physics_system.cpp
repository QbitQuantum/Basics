void PhysicsSystemImpl::destroy()
{
	m_controller_manager->release();
	m_cooking->release();
	m_physics->release();
	m_foundation->release();
	m_allocator.deleteObject(m_physx_allocator);
	m_allocator.deleteObject(m_error_callback);
}