void rayPickerManager::SetPickedBody (dNewtonBody* const body, const Vec4& handle)
{
	dNewton::ScopeLock scopelock (&m_lock);

	m_pickedBody = body;
	if (m_pickedBody) {
		Matrix matrix;
		if (m_pickedBody->GetType() == dNewtonBody::m_dynamic) {
			matrix.invert(((newtonDynamicBody*) body)->GetMatrix());
		} else {
			dAssert (0);
		}
		m_localpHandlePoint = handle * matrix;
		m_globalTarget = handle;
	}
}