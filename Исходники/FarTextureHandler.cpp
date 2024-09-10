void CFarTextureHandler::Draw()
{
	if (queuedForRender.empty()) {
		return;
	}

	//! create new faricons
	for (GML_VECTOR<const CSolidObject*>::iterator it = queuedForRender.begin(); it != queuedForRender.end(); ++it) {
		const CSolidObject& obj = **it;
		if (cache.size()<=obj.team || cache[obj.team].size()<=obj.model->id || !cache[obj.team][obj.model->id]) {
			CreateFarTexture(*it);
		}
	}

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, farTexture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3fv((const GLfloat*) &unitDrawer->camNorm.x);

	if (globalRendering->drawFog) {
		glFogfv(GL_FOG_COLOR, mapInfo->atmosphere.fogColor);
		glEnable(GL_FOG);
	}

	CVertexArray* va = GetVertexArray();
	va->Initialize();
	va->EnlargeArrays(queuedForRender.size() * 4, 0, VA_SIZE_T);
	for (GML_VECTOR<const CSolidObject*>::iterator it = queuedForRender.begin(); it != queuedForRender.end(); ++it) {
		DrawFarTexture(*it, va);
	}

	va->DrawArrayT(GL_QUADS);
	glDisable(GL_ALPHA_TEST);

	queuedForRender.clear();
}