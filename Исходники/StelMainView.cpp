void NightModeGraphicsEffect::draw(QPainter* painter)
{
	int pixelRatio = painter->device()->devicePixelRatio();
	QSize size(painter->device()->width() * pixelRatio, painter->device()->height() * pixelRatio);
	if (fbo && fbo->size() != size)
	{
		delete fbo;
		fbo = NULL;
	}
	if (!fbo)
	{
		QGLFramebufferObjectFormat format;
		format.setAttachment(QGLFramebufferObject::CombinedDepthStencil);
		format.setInternalTextureFormat(GL_RGBA);
		fbo = new NightModeGraphicsEffectFbo(size, format, pixelRatio);
	}
	QPainter fboPainter(fbo);
	drawSource(&fboPainter);

	painter->save();
	painter->beginNativePainting();
	program->bind();
	const GLfloat pos[] = {-1, -1, +1, -1, -1, +1, +1, +1};
	const GLfloat texCoord[] = {0, 0, 1, 0, 0, 1, 1, 1};
	program->setUniformValue(vars.source, 0);
	program->setAttributeArray(vars.pos, pos, 2);
	program->setAttributeArray(vars.texCoord, texCoord, 2);
	program->enableAttributeArray(vars.pos);
	program->enableAttributeArray(vars.texCoord);
	glBindTexture(GL_TEXTURE_2D, fbo->texture());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	program->release();
	painter->endNativePainting();
	painter->restore();
}