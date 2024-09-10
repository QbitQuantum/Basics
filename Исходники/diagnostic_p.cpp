QString openGlContext()
{
    QString result;
    QTextStream str(&result);

    QOpenGLContext context;
    if (context.create()) {
#  ifdef QT_OPENGL_DYNAMIC
        str << "Dynamic GL ";
#  endif
        switch (context.openGLModuleType()) {
        case QOpenGLContext::LibGL:
            str << "LibGL";
            break;
        case QOpenGLContext::LibGLES:
            str << "LibGLES";
            break;
        }

        QWindow window;
        if (QGuiApplication::platformName() == QLatin1String("greenisland"))
            window.setFlags(Qt::Desktop);
        window.setSurfaceType(QSurface::OpenGLSurface);
        //window.setScreen(QGuiApplication::primaryScreen());
        window.create();
        if (context.makeCurrent(&window)) {
            QOpenGLFunctions functions(&context);

            str << " Vendor: " << reinterpret_cast<const char *>(functions.glGetString(GL_VENDOR))
                << "\nRenderer: " << reinterpret_cast<const char *>(functions.glGetString(GL_RENDERER))
                << "\nVersion: " << reinterpret_cast<const char *>(functions.glGetString(GL_VERSION))
                << "\nGLSL version: " << reinterpret_cast<const char *>(functions.glGetString(GL_SHADING_LANGUAGE_VERSION))
                << "\nFormat: " << context.format();

            QList<QByteArray> extensionList = context.extensions().toList();
            std::sort(extensionList.begin(), extensionList.end());
            QByteArray extensions = extensionList.join(' ');
            str << " \nFound " << extensionList.size() << " extensions:\n";
            str << wordWrap(extensions, 78);

            context.doneCurrent();
        }
        window.destroy();
    } else {
        str << "Unable to create an Open GL context.\n";
    }

    return result;
}