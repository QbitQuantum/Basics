void StelAppGraphicsWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	// Don't even try to draw if we don't have a core yet (fix a bug during splash screen)
	if (!stelApp || !stelApp->getCore() || !doPaint)
		return;
	
	StelPainter::setQPainter(painter);

	if (useBuffers)
	{
		StelPainter::makeMainGLContextCurrent();
		initBuffers();
		backgroundBuffer->bind();
		QPainter* pa = new QPainter(backgroundBuffer);
		StelPainter::setQPainter(pa);

		// If we are using the gui, then we try to have the best reactivity, even if we need to lower the fps for that.
		int minFps = StelApp::getInstance().getGui()->isCurrentlyUsed() ? 16 : 2;
		while (true)
		{
			bool keep = paintPartial();
			if (!keep) // The paint is done
			{
				delete pa;
				backgroundBuffer->release();
				swapBuffers();
				break;
			}
			double spentTime = StelApp::getTotalRunTime() - previousPaintFrameTime;
			if (1. / spentTime <= minFps) // we spent too much time
			{
				// We stop the painting operation for now
				delete pa;
				backgroundBuffer->release();
				break;
			}
		}
		Q_ASSERT(!backgroundBuffer->isBound());
		Q_ASSERT(!foregroundBuffer->isBound());
		// Paint the last completed painted buffer
		StelPainter::setQPainter(painter);
		viewportEffect->paintViewportBuffer(foregroundBuffer);
	}
	else
	{
		while (paintPartial()) {;}
	}
	StelPainter::setQPainter(NULL);
	previousPaintFrameTime = StelApp::getTotalRunTime();
}