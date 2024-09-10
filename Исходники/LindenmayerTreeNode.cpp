void LindenmayerTreeNode::Render(OGLRenderer& r, bool render_children) {
	if (r.GetCurrentShader() != shader) r.SetCurrentShader(shader);
	r.UpdateShaderMatrices();
	Matrix4 transform = GetWorldTransform() * Matrix4::Scale(GetModelScale());
	glUniformMatrix4fv(glGetUniformLocation(GetShader()->GetProgram(), "modelMatrix"), 1, false, (float*)&transform);
	glUniformMatrix4fv(glGetUniformLocation(GetShader()->GetProgram(), "textureMatrix"), 1, false, (float*)&GetTextureMatrix());
	glUniform4fv(glGetUniformLocation(GetShader()->GetProgram(), "nodeColour"), 1, (float*)&GetColour());

	/*Draw the branches first to reduce expensive BindTexture calls*/
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0].id);
	for (auto it = children.begin(); it != children.end(); ++it) {
		mem_usage += sizeof(LBranchNode);
		(*it)->Render(r, false);
	}
	/*Then draw the "leaves", turning off alpha blending to do so*/
	glBindTexture(GL_TEXTURE_2D, textures[1].id);
	glDisable(GL_BLEND);
	for (auto it = children.begin(); it != children.end(); ++it) {
		for (auto it2 = (*it)->GetChildIteratorStart(); it2 != (*it)->GetChildIteratorEnd(); ++it2) {
			mem_usage += sizeof(LLeafNode) + sizeof(ParticleEmitter);
			(*it2)->Render(r, false);
		}
	}
	glEnable(GL_BLEND);
}