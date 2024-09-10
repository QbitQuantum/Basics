// --------------------------------------------------------
void TouchWidgetRenderer::drawMagnifyingGlass(
	GLResourceContainer * container,
	const MagnifyingGlass * mg,
	float alpha ) const
{
	// draw contents to fbo
	QGLFramebufferObject * fbo = container->framebufferObject("mg_fbo");
	drawSceneToFbo(fbo,	mg->srcCenter(), mg->srcSize(), mg->angle());

	//qDebug() << "drawing mg " << mg << mg->dstCenter() << mg->dstSize();

	// draw magnifying glass including contents
	QGLShaderProgram * shader = container->shaderProgram("mglass");
	shader->bind();
	shader->setUniformValue("mglass_tex", 0);
	shader->setUniformValue("content_tex", 1);
	shader->setUniformValue("alpha", this->alpha()*alpha);
	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, container->texture("mglass"));
	glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, fbo->texture());
	drawQuad(mg->dstCenter(), mg->dstSize(), -mg->angle(), this->alpha()*alpha);
	shader->release();
}