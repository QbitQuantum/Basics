QSGNode *EmulatorItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData)
{
	QSGSimpleTextureNode *n = static_cast<QSGSimpleTextureNode *>(oldNode);
	if (!n) {
		m_gl = window()->openglContext()->functions();
		connect(window(), SIGNAL(frameFinished()), this, SLOT(onFrameFinished()));
		n = new QSGSimpleTextureNode();
		QImage img(GFX_WIDTH, GFX_HEIGHT, QImage::Format_RGBA8888);
		m_screen = new GLuint[GFX_WIDTH * GFX_HEIGHT];
		img.fill(Qt::green);
		m_texture = window()->createTextureFromImage(img);
		m_texture->setFiltering(QSGTexture::Linear);
		n->setTexture(m_texture);
		n->setRect(boundingRect());
	}

	m_texture->bind();
	m_gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GFX_WIDTH - 16, GFX_HEIGHT - 32, 0, GL_RGB, GL_UNSIGNED_BYTE, m_screen);

	return n;
}