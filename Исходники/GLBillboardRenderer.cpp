	void GLBillboardRenderer::Process(LibCommon::Entity* ent) {
		auto model = ent->GetOptional<Model>();
		auto transform = ent->Get<Transform3D>();
		auto& buffer = m_bufmap.at(ent);
		auto& tex = m_texmap.at(ent);
		auto& program = m_progmap.at(ent);
		if (render->ActiveProgram != program.ProgramID()) {
			render->ActiveProgram = program.ProgramID();
			gl::UseProgram(render->ActiveProgram);
		}
		tex.Bind();
		Matrix4f invView = trans.view;
		invView.rightCols<1>() = Vector4f{ 0, 0, 0, 1 };
		trans.model = transform->GenMatrix() * invView.inverse();
		BindMVP(render->ActiveProgram, trans, "mvp");
		CheckError();
		gl::BindVertexArray(buffer.vao.name());
		gl::EnableVertexAttribArray(0);
		gl::EnableVertexAttribArray(1);
		gl::EnableVertexAttribArray(2);
		GLint posLoc = gl::GetAttribLocation(render->ActiveProgram, "pos");
		GLint uvloc = gl::GetAttribLocation(render->ActiveProgram, "uv");
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffer.Index.GetBuffer());
		gl::BindBuffer(gl::ARRAY_BUFFER, buffer.Vertex.GetBuffer());
		gl::VertexAttribPointer(posLoc, 4, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), 0);
		gl::VertexAttribPointer(uvloc, 3, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), (GLvoid*)(offsetof(LibCommon::Vertex, uv)));
		gl::DrawElements(gl::TRIANGLES, static_cast<GLsizei>(model->indices.size()), gl::UNSIGNED_INT, 0);
	}