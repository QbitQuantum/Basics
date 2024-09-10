void QGLBlitter::SubWidget::paintGL() {
    clear = 2;

    if (reinterpret_cast<const QGLBlitter*>(parentWidget())->isPaused()) {
// 	if (swapInterval)
// 		blitFront();
// 	else {
        if (!blitted)
            blit();

        swapBuffers();
        blitted = false;
// 	}
    }
}