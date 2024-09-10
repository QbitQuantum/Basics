bool DitheringCase::drawAndCheckGradient (const bool isVerticallyIncreasing, const Vec4& highColor) const
{
	TestLog&					log					= m_testCtx.getLog();
	Random						rnd					(deStringHash(getName()));
	const int					maxViewportWid		= 256;
	const int					maxViewportHei		= 256;
	const int					viewportWid			= de::min(m_renderCtx.getRenderTarget().getWidth(), maxViewportWid);
	const int					viewportHei			= de::min(m_renderCtx.getRenderTarget().getHeight(), maxViewportHei);
	const int					viewportX			= rnd.getInt(0, m_renderCtx.getRenderTarget().getWidth() - viewportWid);
	const int					viewportY			= rnd.getInt(0, m_renderCtx.getRenderTarget().getHeight() - viewportHei);
	const Vec4					quadClr0			(0.0f, 0.0f, 0.0f, 0.0f);
	const Vec4&					quadClr1			= highColor;
	Quad						quad;
	Surface						renderedImg			(viewportWid, viewportHei);

	GLU_CHECK_CALL(glViewport(viewportX, viewportY, viewportWid, viewportHei));

	log << TestLog::Message << "Dithering is " << (m_ditheringEnabled ? "enabled" : "disabled") << TestLog::EndMessage;

	if (m_ditheringEnabled)
		GLU_CHECK_CALL(glEnable(GL_DITHER));
	else
		GLU_CHECK_CALL(glDisable(GL_DITHER));

	log << TestLog::Message << "Drawing a " << (isVerticallyIncreasing ? "vertically" : "horizontally") << " increasing gradient" << TestLog::EndMessage;

	quad.color[0] = quadClr0;
	quad.color[1] = isVerticallyIncreasing ? quadClr1 : quadClr0;
	quad.color[2] = isVerticallyIncreasing ? quadClr0 : quadClr1;
	quad.color[3] = quadClr1;

	m_renderer->render(quad);

	glu::readPixels(m_renderCtx, viewportX, viewportY, renderedImg.getAccess());
	GLU_CHECK_MSG("glReadPixels()");

	log << TestLog::Image(isVerticallyIncreasing ? "VerGradient"		: "HorGradient",
						  isVerticallyIncreasing ? "Vertical gradient"	: "Horizontal gradient",
						  renderedImg);

	// Validate, at each pixel, that each color channel is one of its two allowed values.

	{
		Surface		errorMask		(viewportWid, viewportHei);
		bool		colorChoicesOk	= true;

		for (int y = 0; y < renderedImg.getHeight(); y++)
		{
			for (int x = 0; x < renderedImg.getWidth(); x++)
			{
				const float		inputF		= ((float)(isVerticallyIncreasing ? y : x) + 0.5f) / (float)(isVerticallyIncreasing ? renderedImg.getHeight() : renderedImg.getWidth());
				const Vec4		inputClr	= (1.0f-inputF)*quadClr0 + inputF*quadClr1;

				if (!checkColor(inputClr, renderedImg.getPixel(x, y), colorChoicesOk))
				{
					errorMask.setPixel(x, y, tcu::RGBA::red);

					if (colorChoicesOk)
					{
						log << TestLog::Message << "First failure at pixel (" << x << ", " << y << ") (not printing further errors)" << TestLog::EndMessage;
						colorChoicesOk = false;
					}
				}
				else
					errorMask.setPixel(x, y, tcu::RGBA::green);
			}
		}

		if (!colorChoicesOk)
		{
			log << TestLog::Image("ColorChoiceErrorMask", "Error mask for color choices", errorMask);
			return false;
		}
	}

	// When dithering is disabled, the color selection must be coordinate-independent - i.e. the colors must be constant in the gradient's constant direction.

	if (!m_ditheringEnabled)
	{
		const int increasingDirectionSize	= isVerticallyIncreasing ? renderedImg.getHeight() : renderedImg.getWidth();
		const int constantDirectionSize		= isVerticallyIncreasing ? renderedImg.getWidth() : renderedImg.getHeight();

		for (int incrPos = 0; incrPos < increasingDirectionSize; incrPos++)
		{
			tcu::RGBA prevConstantDirectionPix;
			for (int constPos = 0; constPos < constantDirectionSize; constPos++)
			{
				const int			x		= isVerticallyIncreasing ? constPos : incrPos;
				const int			y		= isVerticallyIncreasing ? incrPos : constPos;
				const tcu::RGBA		clr		= renderedImg.getPixel(x, y);

				if (constPos > 0 && clr != prevConstantDirectionPix)
				{
					log << TestLog::Message
						<< "Failure: colors should be constant per " << (isVerticallyIncreasing ? "row" : "column")
						<< " (since dithering is disabled), but the color at position (" << x << ", " << y << ") is " << clr
						<< " and does not equal the color at (" << (isVerticallyIncreasing ? x-1 : x) << ", " << (isVerticallyIncreasing ? y : y-1) << "), which is " << prevConstantDirectionPix
						<< TestLog::EndMessage;

					return false;
				}

				prevConstantDirectionPix = clr;
			}
		}
	}

	return true;
}