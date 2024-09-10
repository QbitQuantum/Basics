/*!
    \internal

    Generates a unique file path and returns a native handle to the open file.
    \a path is used as a template when generating unique paths, \a pos
    identifies the position of the first character that will be replaced in the
    template and \a length the number of characters that may be substituted.

    Returns an open handle to the newly created file if successful, an invalid
    handle otherwise. In both cases, the string in \a path will be changed and
    contain the generated path name.
*/
static bool createFileFromTemplate(NativeFileHandle &file,
        QFileSystemEntry::NativePath &path, size_t pos, size_t length,
        QSystemError &error)
{
    Q_ASSERT(length != 0);
    Q_ASSERT(pos < size_t(path.length()));
    Q_ASSERT(length <= size_t(path.length()) - pos);

    Char *const placeholderStart = (Char *)path.data() + pos;
    Char *const placeholderEnd = placeholderStart + length;

    // Initialize placeholder with random chars + PID.
    {
        Char *rIter = placeholderEnd;

#if defined(QT_BUILD_CORE_LIB)
        quint64 pid = quint64(QCoreApplication::applicationPid());
        do {
            *--rIter = Latin1Char((pid % 10) + '0');
            pid /= 10;
        } while (rIter != placeholderStart && pid != 0);
#endif

        while (rIter != placeholderStart) {
            char ch = char((qrand() & 0xffff) % (26 + 26));
            if (ch < 26)
                *--rIter = Latin1Char(ch + 'A');
            else
                *--rIter = Latin1Char(ch - 26 + 'a');
        }
    }

    for (;;) {
        // Atomically create file and obtain handle
#if defined(Q_OS_WIN)
#  ifndef Q_OS_WINRT
        file = CreateFile((const wchar_t *)path.constData(),
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW,
                FILE_ATTRIBUTE_NORMAL, NULL);
#  else // !Q_OS_WINRT
        file = CreateFile2((const wchar_t *)path.constData(),
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE, CREATE_NEW,
                NULL);
#  endif // Q_OS_WINRT

        if (file != INVALID_HANDLE_VALUE)
            return true;

        DWORD err = GetLastError();
        if (err == ERROR_ACCESS_DENIED) {
            WIN32_FILE_ATTRIBUTE_DATA attributes;
            if (!GetFileAttributesEx((const wchar_t *)path.constData(),
                                     GetFileExInfoStandard, &attributes)
                    || attributes.dwFileAttributes == INVALID_FILE_ATTRIBUTES) {
                // Potential write error (read-only parent directory, etc.).
                error = QSystemError(err, QSystemError::NativeError);
                return false;
            } // else file already exists as a directory.
        } else if (err != ERROR_FILE_EXISTS) {
            error = QSystemError(err, QSystemError::NativeError);
            return false;
        }
#else // POSIX
        file = QT_OPEN(path.constData(),
                QT_OPEN_CREAT | O_EXCL | QT_OPEN_RDWR | QT_OPEN_LARGEFILE,
                0600);

        if (file != -1)
            return true;

        int err = errno;
        if (err != EEXIST) {
            error = QSystemError(err, QSystemError::NativeError);
            return false;
        }
#endif

        /* tricky little algorwwithm for backward compatibility */
        for (Char *iter = placeholderStart;;) {
            // Character progression: [0-9] => 'a' ... 'z' => 'A' .. 'Z'
            // String progression: "ZZaiC" => "aabiC"
            switch (char(*iter)) {
                case 'Z':
                    // Rollover, advance next character
                    *iter = Latin1Char('a');
                    if (++iter == placeholderEnd) {
                        // Out of alternatives. Return file exists error, previously set.
                        error = QSystemError(err, QSystemError::NativeError);
                        return false;
                    }

                    continue;

                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                    *iter = Latin1Char('a');
                    break;

                case 'z':
                    // increment 'z' to 'A'
                    *iter = Latin1Char('A');
                    break;

                default:
                    ++*iter;
                    break;
            }
            break;
        }
    }

    Q_ASSERT(false);
}