bool Q3Process::start( QStringList *env )
{
#if defined(QT_Q3PROCESS_DEBUG)
    qDebug( "Q3Process::start()" );
#endif
    reset();

    if ( _arguments.isEmpty() )
	return false;

    // Open the pipes.  Make non-inheritable copies of input write and output
    // read handles to avoid non-closable handles (this is done by the
    // DuplicateHandle() call).
    SECURITY_ATTRIBUTES secAtt = { sizeof( SECURITY_ATTRIBUTES ), NULL, TRUE };
#ifndef Q_OS_WINCE
    // I guess there is no stdin stdout and stderr on Q_OS_WINCE to dup
    // CreatePipe and DupilcateHandle aren't available for Q_OS_WINCE
    HANDLE tmpStdin, tmpStdout, tmpStderr;
    if ( comms & Stdin ) {
	if ( !CreatePipe( &d->pipeStdin[0], &tmpStdin, &secAtt, 0 ) ) {
	    d->closeHandles();
	    return false;
	}
	if ( !DuplicateHandle( GetCurrentProcess(), tmpStdin, GetCurrentProcess(), &d->pipeStdin[1], 0, FALSE, DUPLICATE_SAME_ACCESS ) ) {
	    d->closeHandles();
	    return false;
	}
	if ( !CloseHandle( tmpStdin ) ) {
	    d->closeHandles();
	    return false;
	}
    }
    if ( comms & Stdout ) {
	if ( !CreatePipe( &tmpStdout, &d->pipeStdout[1], &secAtt, 0 ) ) {
	    d->closeHandles();
	    return false;
	}
	if ( !DuplicateHandle( GetCurrentProcess(), tmpStdout, GetCurrentProcess(), &d->pipeStdout[0], 0, FALSE, DUPLICATE_SAME_ACCESS ) ) {
	    d->closeHandles();
	    return false;
	}
	if ( !CloseHandle( tmpStdout ) ) {
	    d->closeHandles();
	    return false;
	}
    }
    if ( comms & Stderr ) {
	if ( !CreatePipe( &tmpStderr, &d->pipeStderr[1], &secAtt, 0 ) ) {
	    d->closeHandles();
	    return false;
	}
	if ( !DuplicateHandle( GetCurrentProcess(), tmpStderr, GetCurrentProcess(), &d->pipeStderr[0], 0, FALSE, DUPLICATE_SAME_ACCESS ) ) {
	    d->closeHandles();
	    return false;
	}
	if ( !CloseHandle( tmpStderr ) ) {
	    d->closeHandles();
	    return false;
	}
    }
    if ( comms & DupStderr ) {
	CloseHandle( d->pipeStderr[1] );
	d->pipeStderr[1] = d->pipeStdout[1];
    }
#endif

    // construct the arguments for CreateProcess()
    QString args;
    QString appName;
    QStringList::Iterator it = _arguments.begin();
    args = *it;
    ++it;
    if ( args.endsWith( QLatin1String(".bat") ) && args.contains( QLatin1Char(' ') ) ) {
	// CreateProcess() seems to have a strange semantics (see also
	// http://www.experts-exchange.com/Programming/Programming_Platforms/Win_Prog/Q_11138647.html):
	// If you start a batch file with spaces in the filename, the first
	// argument to CreateProcess() must be the name of the batchfile
	// without quotes, but the second argument must start with the same
	// argument with quotes included. But if the same approach is used for
	// .exe files, it doesn't work.
	appName = args;
	args = QLatin1Char('"') + args + QLatin1Char('"');
    }
    for ( ; it != _arguments.end(); ++it ) {
	QString tmp = *it;
	// escape a single " because the arguments will be parsed
	tmp.replace( QLatin1Char('\"'), QLatin1String("\\\"") );
	if ( tmp.isEmpty() || tmp.contains( QLatin1Char(' ') ) || tmp.contains( QLatin1Char('\t') ) ) {
	    // The argument must not end with a \ since this would be interpreted
	    // as escaping the quote -- rather put the \ behind the quote: e.g.
	    // rather use "foo"\ than "foo\"
	    QString endQuote( QLatin1String("\"") );
	    int i = tmp.length();
	    while ( i>0 && tmp.at( i-1 ) == QLatin1Char('\\') ) {
		--i;
		endQuote += QLatin1Char('\\');
	    }
        args += QLatin1String(" \"") + tmp.left( i ) + endQuote;
	} else {
	    args += QLatin1Char(' ') + tmp;
	}
    }
#if defined(QT_Q3PROCESS_DEBUG)
    qDebug( "Q3Process::start(): args [%s]", args.latin1() );
#endif

    // CreateProcess()
    bool success;
    d->newPid();

    STARTUPINFOW startupInfo = {
        sizeof( STARTUPINFO ), 0, 0, 0,
        (ulong)CW_USEDEFAULT, (ulong)CW_USEDEFAULT, (ulong)CW_USEDEFAULT, (ulong)CW_USEDEFAULT,
        0, 0, 0,
        STARTF_USESTDHANDLES,
        0, 0, 0,
        d->pipeStdin[0], d->pipeStdout[1], d->pipeStderr[1]
    };
    wchar_t *applicationName;
    if ( appName.isNull() )
        applicationName = 0;
    else
        applicationName = _wcsdup( (wchar_t*)appName.utf16() );
    wchar_t *commandLine = _wcsdup( (wchar_t*)args.utf16() );
    QByteArray envlist;
    if ( env != 0 ) {
        int pos = 0;
        // add PATH if necessary (for DLL loading)
        QByteArray path = qgetenv( "PATH" );
        if ( env->grep( QRegExp(QLatin1String("^PATH="),FALSE) ).empty() && !path.isNull() ) {
            QString tmp = QString::fromLatin1("PATH=%1").arg(QLatin1String(path.constData()));
            uint tmpSize = sizeof(wchar_t) * (tmp.length() + 1);
            envlist.resize( envlist.size() + tmpSize );
            memcpy( envlist.data() + pos, tmp.utf16(), tmpSize );
            pos += tmpSize;
        }
        // add the user environment
        for ( QStringList::Iterator it = env->begin(); it != env->end(); it++ ) {
            QString tmp = *it;
            uint tmpSize = sizeof(wchar_t) * (tmp.length() + 1);
            envlist.resize( envlist.size() + tmpSize );
            memcpy( envlist.data() + pos, tmp.utf16(), tmpSize );
            pos += tmpSize;
        }
        // add the 2 terminating 0 (actually 4, just to be on the safe side)
        envlist.resize( envlist.size()+4 );
        envlist[pos++] = 0;
        envlist[pos++] = 0;
        envlist[pos++] = 0;
        envlist[pos++] = 0;
    }
    success = CreateProcess( applicationName, commandLine,
                            0, 0, TRUE, ( comms == 0 ? CREATE_NEW_CONSOLE : CREATE_NO_WINDOW )
#ifndef Q_OS_WINCE
                            | CREATE_UNICODE_ENVIRONMENT
#endif
                            , env == 0 ? 0 : envlist.data(),
                            (wchar_t*)QDir::toNativeSeparators(workingDir.absPath()).utf16(),
                            &startupInfo, d->pid );

    free( applicationName );
    free( commandLine );

    if  ( !success ) {
	d->deletePid();
	return false;
    }

#ifndef Q_OS_WINCE
    if ( comms & Stdin )
	CloseHandle( d->pipeStdin[0] );
    if ( comms & Stdout )
        CloseHandle( d->pipeStdout[1] );
    if ( (comms & Stderr) && !(comms & DupStderr) )
	CloseHandle( d->pipeStderr[1] );
#endif

    if ( ioRedirection || notifyOnExit ) {
	d->lookup->start( 100 );
    }

    // cleanup and return
    return true;
}