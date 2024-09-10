// (Un)Register the ActiveX server in the registry.
// The QAxFactory implementation provides the information.
HRESULT UpdateRegistry(BOOL bRegister)
{
    qAxIsServer = false;
    const QChar dot(QLatin1Char('.'));
    const QChar slash(QLatin1Char('/'));
    QString file = QString::fromWCharArray(qAxModuleFilename);
    const QString module = QFileInfo(file).baseName();

    const QString appId = qAxFactory()->appID().toString().toUpper();
    const QString libId = qAxFactory()->typeLibID().toString().toUpper();

    const QString libFile = qAxInit();

    TLIBATTR *libAttr = 0;
    if (qAxTypeLibrary)
        qAxTypeLibrary->GetLibAttr(&libAttr);
    if (!libAttr)
        return SELFREG_E_TYPELIB;
    bool userFallback = false;
    if (bRegister) {
        if (RegisterTypeLib(qAxTypeLibrary,
                            reinterpret_cast<wchar_t *>(const_cast<ushort *>(libFile.utf16())), 0) == TYPE_E_REGISTRYACCESS) {
#ifndef Q_CC_MINGW
            // MinGW does not have RegisterTypeLibForUser() implemented so we cannot fallback in this case
            RegisterTypeLibForUser(qAxTypeLibrary, reinterpret_cast<wchar_t *>(const_cast<ushort *>(libFile.utf16())), 0);
            userFallback = true;
#endif
        }
    } else {
        if (UnRegisterTypeLib(libAttr->guid, libAttr->wMajorVerNum, libAttr->wMinorVerNum, libAttr->lcid,
                              libAttr->syskind) == TYPE_E_REGISTRYACCESS) {
#ifndef Q_CC_MINGW
            // MinGW does not have RegisterTypeLibForUser() implemented so we cannot fallback in this case
            UnRegisterTypeLibForUser(libAttr->guid, libAttr->wMajorVerNum, libAttr->wMinorVerNum, libAttr->lcid, libAttr->syskind);
            userFallback = true;
#endif
        }
    }
    if (userFallback)
        qWarning("QAxServer: Falling back to registering as user for %s due to insufficient permission.", qPrintable(module));
    qAxTypeLibrary->ReleaseTLibAttr(libAttr);

    // check whether the user has permission to write to HKLM\Software\Classes
    // if not, use HKCU\Software\Classes
    QString keyPath(QLatin1String("HKEY_LOCAL_MACHINE\\Software\\Classes"));
    QScopedPointer<QSettings> settings(new QSettings(keyPath, QSettings::NativeFormat));
    if (userFallback || !settings->isWritable()) {
        keyPath = QLatin1String("HKEY_CURRENT_USER\\Software\\Classes");
        settings.reset(new QSettings(keyPath, QSettings::NativeFormat));
    }

    // we try to create the ActiveX widgets later on...
    bool delete_qApp = false;
    if (!qApp) {
        static int argc = 0; // static lifetime, since it's passed as reference to QApplication, which has a lifetime exceeding the stack frame
        (void)new QApplication(argc, 0);
        delete_qApp = true;
    }

    if (bRegister) {
        if (qAxOutProcServer) {
            settings->setValue(QLatin1String("/AppID/") + appId + QLatin1String("/."), module);
            settings->setValue(QLatin1String("/AppID/") + module + QLatin1String(".EXE/AppID"), appId);
        }

        const QStringList keys = qAxFactory()->featureList();
        for (const QString &classNameIn : keys) {
            QObject *object = qAxFactory()->createObject(classNameIn);
            const QMetaObject *mo = qAxFactory()->metaObject(classNameIn);
            const QString classId = qAxFactory()->classID(classNameIn).toString().toUpper();

            const QString className = qax_clean_type(classNameIn, mo);

            if (object) { // don't register subobject classes
                QString classVersion = mo ? QString::fromLatin1(mo->classInfo(mo->indexOfClassInfo("Version")).value()) : QString();
                if (classVersion.isNull())
                    classVersion = QLatin1String("1.0");
                bool insertable = mo && !qstricmp(mo->classInfo(mo->indexOfClassInfo("Insertable")).value(), "yes");
                bool control = object->isWidgetType();
                QString classMajorVersion = classVersion.left(classVersion.indexOf(dot));
                uint olemisc = OLEMISC_SETCLIENTSITEFIRST
                    |OLEMISC_ACTIVATEWHENVISIBLE
                    |OLEMISC_INSIDEOUT
                    |OLEMISC_CANTLINKINSIDE
                    |OLEMISC_RECOMPOSEONRESIZE;
                if (!control)
                    olemisc |= OLEMISC_INVISIBLEATRUNTIME;
                else if (object->findChild<QMenuBar*>() && !qax_disable_inplaceframe)
                    olemisc |= OLEMISC_WANTSTOMENUMERGE;

                const QString versionLessProgId = module + dot + className;
                const QString progId = versionLessProgId + dot + classMajorVersion;
                QString key = slash + progId;
                settings->setValue(key + QLatin1String("/."), className + QLatin1String(" Class"));
                settings->setValue(key + QLatin1String("/CLSID/."), classId);
                if (insertable)
                    settings->setValue(key + QLatin1String("/Insertable/."), QVariant(QLatin1String("")));

                key = slash + module + dot + className;
                settings->setValue(key + QLatin1String("/."), className + QLatin1String(" Class"));
                settings->setValue(key + QLatin1String("/CLSID/."), classId);
                settings->setValue(key + QLatin1String("/CurVer/."), progId);

                key = QLatin1String("/CLSID/") + classId;
                settings->setValue(key + QLatin1String("/."), className + QLatin1String(" Class"));
                if (file.endsWith(QLatin1String("exe"), Qt::CaseInsensitive))
                    settings->setValue(key + QLatin1String("/AppID"), appId);
                if (control)
                    settings->setValue(key + QLatin1String("/Control/."), QVariant(QLatin1String("")));
                if (insertable)
                    settings->setValue(key + QLatin1String("/Insertable/."), QVariant(QLatin1String("")));
                if (file.endsWith(QLatin1String("dll"), Qt::CaseInsensitive))
                    settings->setValue(key + QLatin1String("/InProcServer32/."), file);
                else
                    settings->setValue(key + QLatin1String("/LocalServer32/."),
                                      QLatin1Char('\"') + file + QLatin1String("\" -activex"));
                settings->setValue(key + QLatin1String("/MiscStatus/."), control ? QLatin1String("1") : QLatin1String("0"));
                settings->setValue(key + QLatin1String("/MiscStatus/1/."), QString::number(olemisc));
                settings->setValue(key + QLatin1String("/Programmable/."), QVariant(QLatin1String("")));
                settings->setValue(key + QLatin1String("/ToolboxBitmap32/."), QLatin1Char('\"') +
                                  file + QLatin1String("\", 101"));
                settings->setValue(key + QLatin1String("/TypeLib/."), libId);
                settings->setValue(key + QLatin1String("/Version/."), classVersion);
                settings->setValue(key + QLatin1String("/VersionIndependentProgID/."), versionLessProgId);
                settings->setValue(key + QLatin1String("/ProgID/."), progId);

                QString mime = QLatin1String(mo->classInfo(mo->indexOfClassInfo("MIME")).value());
                if (!mime.isEmpty()) {
                    QStringList mimeTypes = mime.split(QLatin1Char(';'));
                    for (int m = 0; m < mimeTypes.count(); ++m) {
                        mime = mimeTypes.at(m);
                        if (mime.isEmpty())
                            continue;
                        QString extension;
                        while (mime.contains(QLatin1Char(':'))) {
                            extension = mime.mid(mime.lastIndexOf(QLatin1Char(':')) + 1);
                            mime.chop(extension.length() + 1);
                            // Prepend '.' before extension, if required.
                            extension = extension.trimmed();
                            if (!extension.startsWith(dot))
                                extension.prepend(dot);
                        }

                        if (!extension.isEmpty()) {
                            key = slash + extension;
                            settings->setValue(key + QLatin1String("/."), module + dot + className);
                            settings->setValue(key + QLatin1String("/Content Type"), mime);

                            mime.replace(slash, QLatin1Char('\\'));
                            key = QLatin1String("/MIME/Database/Content Type/") + mime;
                            settings->setValue(key + QLatin1String("/CLSID"), classId);
                            settings->setValue(key + QLatin1String("/Extension"), extension);
                        }
                    }
                }

                delete object;
                qCDebug(lcAxRegistration).nospace().noquote() << "Registered \"" << progId
                    << "\"/" << classId << ", \"" << file << "\" at \"" << keyPath
                    << "\", insertable=" << insertable << ", control=" << control
                    << ", olemisc=" << hex << showbase << olemisc
                    << ", mime=" << mime;
            }

            qAxFactory()->registerClass(classNameIn, settings.data());
        }
    } else {
        if (qAxOutProcServer) {
            settings->remove(QLatin1String("/AppID/") + appId + QLatin1String("/."));
            settings->remove(QLatin1String("/AppID/") + module + QLatin1String(".EXE"));
        }
        const QStringList keys = qAxFactory()->featureList();
        for (const QString &classNameIn : keys) {
            const QMetaObject *mo = qAxFactory()->metaObject(classNameIn);
            const QString classId = qAxFactory()->classID(classNameIn).toString().toUpper();
            const QString className = qax_clean_type(classNameIn, mo);

            QString classVersion = mo ? QString::fromLatin1(mo->classInfo(mo->indexOfClassInfo("Version")).value()) : QString();
            if (classVersion.isNull())
                classVersion = QLatin1String("1.0");
            const QString classMajorVersion = classVersion.left(classVersion.indexOf(dot));

            qAxFactory()->unregisterClass(classNameIn, settings.data());
            const QString progId = module + dot + className + dot + classMajorVersion;
            QString key = slash + progId;
            settings->remove(key + QLatin1String("/CLSID/."));
            settings->remove(key + QLatin1String("/Insertable/."));
            settings->remove(key + QLatin1String("/."));
            settings->remove(key);

            key = slash + module + dot + className;
            settings->remove(key + QLatin1String("/CLSID/."));
            settings->remove(key + QLatin1String("/CurVer/."));
            settings->remove(key + QLatin1String("/."));
            settings->remove(key);

            key = QLatin1String("/CLSID/") + classId;
            settings->remove(key + QLatin1String("/AppID"));
            settings->remove(key + QLatin1String("/Control/."));
            settings->remove(key + QLatin1String("/Insertable/."));
            settings->remove(key + QLatin1String("/InProcServer32/."));
            settings->remove(key + QLatin1String("/LocalServer32/."));
            settings->remove(key + QLatin1String("/MiscStatus/1/."));
            settings->remove(key + QLatin1String("/MiscStatus/."));
            settings->remove(key + QLatin1String("/Programmable/."));
            settings->remove(key + QLatin1String("/ToolboxBitmap32/."));
            settings->remove(key + QLatin1String("/TypeLib/."));
            settings->remove(key + QLatin1String("/Version/."));
            settings->remove(key + QLatin1String("/VersionIndependentProgID/."));
            settings->remove(key + QLatin1String("/ProgID/."));
            settings->remove(key + QLatin1String("/."));
            settings->remove(key);

            QString mime = QLatin1String(mo->classInfo(mo->indexOfClassInfo("MIME")).value());
            if (!mime.isEmpty()) {
                QStringList mimeTypes = mime.split(QLatin1Char(';'));
                for (int m = 0; m < mimeTypes.count(); ++m) {
                    mime = mimeTypes.at(m);
                    if (mime.isEmpty())
                        continue;
                    QString extension;
                    while (mime.contains(QLatin1Char(':'))) {
                        extension = mime.mid(mime.lastIndexOf(QLatin1Char(':')) + 1);
                        mime.chop(extension.length() + 1);
                        // Prepend '.' before extension, if required.
                        extension = extension.trimmed();
                        if (extension[0] != dot)
                            extension.prepend(dot);
                    }
                    if (!extension.isEmpty()) {
                        key = slash + extension;
                        settings->remove(key + QLatin1String("/Content Type"));
                        settings->remove(key + QLatin1String("/."));
                        settings->remove(key);
                        mime.replace(slash, QLatin1Char('\\'));
                        key = QLatin1String("/MIME/Database/Content Type/") + mime;
                        settings->remove(key + QLatin1String("/Extension"));
                        settings->remove(key + QLatin1String("/CLSID"));
                        settings->remove(key + QLatin1String("/."));
                        settings->remove(key);
                    }
                }
            }
            qCDebug(lcAxRegistration).nospace().noquote() << "Unregistered \""
                << progId << "\"/" << classId << ", \"" << file << "\" from \""
                << keyPath << '"';
        }
    }

    if (delete_qApp)
        delete qApp;

    qAxCleanup();
    if (settings->status() == QSettings::NoError)
        return S_OK;
    qWarning() << module << ": Error writing to " << keyPath;
    return SELFREG_E_CLASS;
}