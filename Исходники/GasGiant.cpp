	void UpdateVBOs() {
		PROFILE_SCOPED()
		//create buffer and upload data
		Graphics::VertexBufferDesc vbd;
		vbd.attrib[0].semantic = Graphics::ATTRIB_POSITION;
		vbd.attrib[0].format   = Graphics::ATTRIB_FORMAT_FLOAT3;
		vbd.attrib[1].semantic = Graphics::ATTRIB_NORMAL;
		vbd.attrib[1].format   = Graphics::ATTRIB_FORMAT_FLOAT3;
		vbd.numVertices = ctx->NUMVERTICES();
		vbd.usage = Graphics::BUFFER_USAGE_STATIC;
		m_vertexBuffer.reset(Pi::renderer->CreateVertexBuffer(vbd));

		GasPatchContext::VBOVertex* vtxPtr = m_vertexBuffer->Map<GasPatchContext::VBOVertex>(Graphics::BUFFER_MAP_WRITE);
		assert(m_vertexBuffer->GetDesc().stride == sizeof(GasPatchContext::VBOVertex));
		
		const Sint32 edgeLen = ctx->edgeLen;
		const double frac = ctx->frac;
		for (Sint32 y=0; y<edgeLen; y++) {
			for (Sint32 x=0; x<edgeLen; x++) {
				const vector3d p = GetSpherePoint(x*frac, y*frac);
				const vector3d pSubCentroid = p - clipCentroid;
				clipRadius = std::max(clipRadius, p.Length());
				vtxPtr->pos = vector3f(pSubCentroid);
				vtxPtr->norm = vector3f(p);

				++vtxPtr; // next vertex
			}
		}
		m_vertexBuffer->Unmap();
	}