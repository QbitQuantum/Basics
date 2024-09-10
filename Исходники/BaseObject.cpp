//-----------------------------------------------------------------------------------------------------------------------------------
const float BaseObject::GetWorldRotation() const
{
	if (!m_parent)
	{
		return m_localRotation;
	}

	return XMScalarModAngle(m_parent->GetWorldRotation() + m_localRotation);
}