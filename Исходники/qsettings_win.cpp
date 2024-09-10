void QWinSettingsPrivate::set(const QString &uKey, const QVariant &value)
{
    if (writeHandle() == 0) {
        setStatus(QSettings::AccessError);
        return;
    }

    QString rKey = escapedKey(uKey);

    HKEY handle = createOrOpenKey(writeHandle(), registryPermissions, keyPath(rKey));
    if (handle == 0) {
        setStatus(QSettings::AccessError);
        return;
    }

    DWORD type;
    QByteArray regValueBuff;

    // Determine the type
    switch (value.type()) {
        case QVariant::List:
        case QVariant::StringList: {
            // If none of the elements contains '\0', we can use REG_MULTI_SZ, the
            // native registry string list type. Otherwise we use REG_BINARY.
            type = REG_MULTI_SZ;
            QStringList l = variantListToStringList(value.toList());
            QStringList::const_iterator it = l.constBegin();
            for (; it != l.constEnd(); ++it) {
                if ((*it).length() == 0 || stringContainsNullChar(*it)) {
                    type = REG_BINARY;
                    break;
                }
            }

            if (type == REG_BINARY) {
                QString s = variantToString(value);
                regValueBuff = QByteArray((const char*)s.utf16(), s.length() * 2);
            } else {
                QStringList::const_iterator it = l.constBegin();
                for (; it != l.constEnd(); ++it) {
                    const QString &s = *it;
                    regValueBuff += QByteArray((const char*)s.utf16(), (s.length() + 1) * 2);
                }
                regValueBuff.append((char)0);
                regValueBuff.append((char)0);
            }
            break;
        }

        case QVariant::Int:
        case QVariant::UInt: {
            type = REG_DWORD;
            qint32 i = value.toInt();
            regValueBuff = QByteArray((const char*)&i, sizeof(qint32));
            break;
        }

        case QVariant::LongLong:
        case QVariant::ULongLong: {
            type = REG_QWORD;
            qint64 i = value.toLongLong();
            regValueBuff = QByteArray((const char*)&i, sizeof(qint64));
            break;
        }

        case QVariant::ByteArray:
            // fallthrough intended

        default: {
            // If the string does not contain '\0', we can use REG_SZ, the native registry
            // string type. Otherwise we use REG_BINARY.
            QString s = variantToString(value);
            type = stringContainsNullChar(s) ? REG_BINARY : REG_SZ;
            if (type == REG_BINARY) {
                regValueBuff = QByteArray((const char*)s.utf16(), s.length() * 2);
            } else {
                regValueBuff = QByteArray((const char*)s.utf16(), (s.length() + 1) * 2);
            }
            break;
        }
    }

    // set the value
    LONG res = RegSetValueEx(handle, reinterpret_cast<const wchar_t *>(keyName(rKey).utf16()), 0, type,
                             reinterpret_cast<const unsigned char*>(regValueBuff.constData()),
                             regValueBuff.size());

    if (res == ERROR_SUCCESS) {
        deleteWriteHandleOnExit = false;
    } else {
        qWarning("QSettings: failed to set subkey \"%s\": %s",
                rKey.toLatin1().data(), errorCodeToString(res).toLatin1().data());
        setStatus(QSettings::AccessError);
    }

    RegCloseKey(handle);
}