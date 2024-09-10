void FboRenderContext::createFramebuffer (const RenderConfig& config)
{
	DE_ASSERT(m_framebuffer == 0 && m_colorBuffer == 0 && m_depthStencilBuffer == 0);

	const glw::Functions&	gl					= m_context->getFunctions();
	const deUint32			colorFormat			= chooseColorFormat(config);
	const deUint32			depthStencilFormat	= chooseDepthStencilFormat(config);
	int						width				= config.width;
	int						height				= config.height;
	tcu::PixelFormat		pixelFormat;
	int						depthBits			= 0;
	int						stencilBits			= 0;

	if (config.numSamples > 0 && !gl.renderbufferStorageMultisample)
		throw tcu::NotSupportedError("Multisample FBO is not supported");

	if (colorFormat == 0)
		throw tcu::NotSupportedError("Unsupported color attachment format");

	if (width == glu::RenderConfig::DONT_CARE || height == glu::RenderConfig::DONT_CARE)
	{
		int maxSize = 0;
		gl.getIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxSize);

		width	= (width	== glu::RenderConfig::DONT_CARE) ? maxSize : width;
		height	= (height	== glu::RenderConfig::DONT_CARE) ? maxSize : height;
	}

	{
		pixelFormat = getPixelFormat(colorFormat);

		gl.genRenderbuffers(1, &m_colorBuffer);
		gl.bindRenderbuffer(GL_RENDERBUFFER, m_colorBuffer);

		if (config.numSamples > 0)
			gl.renderbufferStorageMultisample(GL_RENDERBUFFER, config.numSamples, colorFormat, width, height);
		else
			gl.renderbufferStorage(GL_RENDERBUFFER, colorFormat, width, height);

		gl.bindRenderbuffer(GL_RENDERBUFFER, 0);
		GLU_EXPECT_NO_ERROR(gl.getError(), "Creating color renderbuffer");
	}

	if (depthStencilFormat != GL_NONE)
	{
		getDepthStencilBits(depthStencilFormat, &depthBits, &stencilBits);

		gl.genRenderbuffers(1, &m_depthStencilBuffer);
		gl.bindRenderbuffer(GL_RENDERBUFFER, m_depthStencilBuffer);

		if (config.numSamples > 0)
			gl.renderbufferStorageMultisample(GL_RENDERBUFFER, config.numSamples, depthStencilFormat, width, height);
		else
			gl.renderbufferStorage(GL_RENDERBUFFER, depthStencilFormat, width, height);

		gl.bindRenderbuffer(GL_RENDERBUFFER, 0);
		GLU_EXPECT_NO_ERROR(gl.getError(), "Creating depth / stencil renderbuffer");
	}

	gl.genFramebuffers(1, &m_framebuffer);
	gl.bindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	if (m_colorBuffer)
		gl.framebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorBuffer);

	if (m_depthStencilBuffer)
	{
		if (depthBits > 0)
			gl.framebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBuffer);

		if (stencilBits > 0)
			gl.framebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBuffer);
	}

	GLU_EXPECT_NO_ERROR(gl.getError(), "Creating framebuffer");

	if (gl.checkFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw tcu::NotSupportedError("Framebuffer is not complete");

	// Set up correct viewport for first test case.
	gl.viewport(0, 0, width, height);

	m_renderTarget = tcu::RenderTarget(width, height, pixelFormat, depthBits, stencilBits, config.numSamples);
}