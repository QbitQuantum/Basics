void Label3D::SetText(const std::string &text)
{
	//regenerate geometry
	m_geometry->Clear();
	if (!text.empty()) {
		m_font->GetGeometry(*m_geometry, text, vector2f(0.f));

		// Happens if none of the characters in the string have glyphs in the SDF font.
		// Most noticeably, this means text consisting of entirely Cyrillic
		// or Chinese characters will vanish when rendered on a Label3D.
		if (m_geometry->IsEmpty()) { return; }
		
		//create buffer and upload data
		Graphics::VertexBufferDesc vbd;
		vbd.attrib[0].semantic = Graphics::ATTRIB_POSITION;
		vbd.attrib[0].format   = Graphics::ATTRIB_FORMAT_FLOAT3;
		vbd.attrib[1].semantic = Graphics::ATTRIB_NORMAL;
		vbd.attrib[1].format   = Graphics::ATTRIB_FORMAT_FLOAT3;
		vbd.attrib[2].semantic = Graphics::ATTRIB_UV0;
		vbd.attrib[2].format   = Graphics::ATTRIB_FORMAT_FLOAT2;
		vbd.numVertices = m_geometry->GetNumVerts();
		vbd.usage = Graphics::BUFFER_USAGE_STATIC;

		m_vbuffer.reset( m_renderer->CreateVertexBuffer(vbd) );
		m_vbuffer->Populate(*m_geometry);
	}
}