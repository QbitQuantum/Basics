Line3D::Line3D() : m_refreshVertexBuffer(true), m_width(2.0f), m_va( new Graphics::VertexArray(Graphics::ATTRIB_POSITION | Graphics::ATTRIB_DIFFUSE, 2) )
{
	PROFILE_SCOPED()
	assert(m_va.get());
	// XXX bug in Radeon drivers will cause crash in glLineWidth if width >= 3
	m_va->Add(vector3f(0.f), Color(0));
	m_va->Add(vector3f(0.f), Color(255));
}