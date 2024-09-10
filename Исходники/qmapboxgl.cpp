void QMapboxGLPrivate::invalidate()
{
    // Map thread
    if (!q_ptr->isExposed()) {
        return;
    }

    if (!context) {
        context.reset(new QOpenGLContext());
        context->setFormat(q_ptr->requestedFormat());
        context->create();
        context->makeCurrent(q_ptr);

        mbgl::gl::InitializeExtensions([](const char *name) {
            QOpenGLContext *thisContext = QOpenGLContext::currentContext();
            return thisContext->getProcAddress(name);
        });
    }

    emit viewInvalidated();
}