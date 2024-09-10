bool Phantom::execute()
{
    if (m_terminated)
        return false;

#ifndef QT_NO_DEBUG_OUTPUT
    qDebug() << "Phantom - execute: Configuration";
    const QMetaObject* configMetaObj = m_config.metaObject();
    for (int i = 0, ilen = configMetaObj->propertyCount(); i < ilen; ++i) {
        qDebug() << "    " << i << configMetaObj->property(i).name() << ":" << m_config.property(configMetaObj->property(i).name()).toString();
    }

    qDebug() << "Phantom - execute: Script & Arguments";
    qDebug() << "    " << "script:" << m_config.scriptFile();
    QStringList args = m_config.scriptArgs();
    for (int i = 0, ilen = args.length(); i < ilen; ++i) {
        qDebug() << "    " << i << "arg:" << args.at(i);
    }
#endif

    if (m_config.isWebdriverMode()) {                                   // Remote WebDriver mode requested
        qDebug() << "Phantom - execute: Starting Remote WebDriver mode";

        Terminal::instance()->cout("PhantomJS is launching GhostDriver...");
        if (!Utils::injectJsInFrame(":/ghostdriver/main.js", QString(), m_scriptFileEnc, QDir::currentPath(), m_page->mainFrame(), true)) {
            m_returnValue = -1;
            return false;
        }
    } else if (m_config.scriptFile().isEmpty()) {                       // REPL mode requested
        qDebug() << "Phantom - execute: Starting REPL mode";

        // REPL is only valid for javascript
        const QString &scriptLanguage = m_config.scriptLanguage();
        if (scriptLanguage != "javascript" && !scriptLanguage.isNull()) {
            QString errMessage = QString("Unsupported language: %1").arg(scriptLanguage);
            Terminal::instance()->cerr(errMessage);
            qWarning("%s", qPrintable(errMessage));
            return false;
        }

        // Create the REPL: it will launch itself, no need to store this variable.
        REPL::getInstance(m_page->mainFrame(), this);
    } else {                                                            // Load the User Script
        qDebug() << "Phantom - execute: Starting normal mode";

        if (m_config.debug()) {
            // Debug enabled
            if (!Utils::loadJSForDebug(m_config.scriptFile(), m_config.scriptLanguage(), m_scriptFileEnc, QDir::currentPath(), m_page->mainFrame(), m_config.remoteDebugAutorun())) {
                m_returnValue = -1;
                return false;
            }
            m_page->showInspector(m_config.remoteDebugPort());
        } else {
            if (!Utils::injectJsInFrame(m_config.scriptFile(), m_config.scriptLanguage(), m_scriptFileEnc, QDir::currentPath(), m_page->mainFrame(), true)) {
                m_returnValue = -1;
                return false;
            }
        }
    }

    return !m_terminated;
}