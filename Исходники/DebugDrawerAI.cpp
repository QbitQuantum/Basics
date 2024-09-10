void DebugDrawerAI::TexSet::Draw() {
	if (!textures.empty()) {
		glEnable(GL_TEXTURE_2D);
		font->Begin();
		font->SetTextColor(0.0f, 0.0f, 0.0f, 1.0f);

		CVertexArray* va = GetVertexArray();

		for (std::map<int, TexSet::Texture*>::iterator it = textures.begin(); it != textures.end(); ++it) {
			const TexSet::Texture* tex = it->second;
			const float3& pos = tex->GetPos();
			const float3& size = tex->GetSize();

			glBindTexture(GL_TEXTURE_2D, tex->GetID());
			va->Initialize();
			va->AddVertexT(pos,                                0.0f, 1.0f);
			va->AddVertexT(pos + float3(size.x,   0.0f, 0.0f), 1.0f, 1.0f);
			va->AddVertexT(pos + float3(size.x, size.y, 0.0f), 1.0f, 0.0f);
			va->AddVertexT(pos + float3(  0.0f, size.y, 0.0f), 0.0f, 0.0f);
			va->DrawArrayT(GL_QUADS);
			glBindTexture(GL_TEXTURE_2D, 0);

			const float tx = pos.x + size.x * 0.5f - ((tex->GetLabelWidth() * 0.5f) / globalRendering->viewSizeX) * size.x;
			const float ty = pos.y + size.y        + ((tex->GetLabelHeight() * 0.5f) / globalRendering->viewSizeY) * size.y;

			font->glFormat(tx, ty, 1.0f, FONT_SCALE | FONT_NORM, "%s", tex->GetLabel().c_str());
		}

		font->End();
		glDisable(GL_TEXTURE_2D);
	}
}