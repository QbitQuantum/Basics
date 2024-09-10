/*!
  Install a single package
  \param package the package to be installed
  \param parser the argument parser to be used
  \param update whether this is an update transaction
*/
InstallTransaction::InstallResult
InstallTransaction::installPackage( const Package* package,
                                    const ArgParser* parser,
                                    bool update ) const
{

    InstallTransaction::InstallResult result = SUCCESS;
#ifdef USE_LOCKING
    LockFile lockFile;
#endif

    int fderr, fdout, tmperr, tmpout;
    if ( m_config->writeLog() ) {
        string logFile = m_config->logFilePattern();
        if ( logFile == "" ) {
            return NO_LOG_FILE;
        }

        StringHelper::replaceAll( logFile, "%n", package->name() );
        StringHelper::replaceAll( logFile, "%p", package->path() );

#ifdef USE_LOCKING
        lockFile.setFile( logFile );
        if ( !lockFile.lockWrite() ) {
            cout << "here" << logFile << endl;
            return CANT_LOCK_LOG_FILE;
        }
#endif

        size_t pos = logFile.find_last_of( "/" );
        if ( pos != string::npos ) {
            if ( !Repository::createOutputDir( logFile.substr( 0, pos ) ) ) {
                return LOG_DIR_FAILURE;
            }
        }

        if ( !m_config->appendLog() ) {
            unlink( logFile.c_str() );
        }

        fderr = open( logFile.c_str(),
                          O_APPEND | O_WRONLY | O_CREAT, 0666 );
        fdout = open( logFile.c_str(),
                          O_APPEND | O_WRONLY | O_CREAT, 0666 );


        if ( fderr == -1  || fdout == -1 ) {
            return LOG_FILE_FAILURE;
        }


        tmpout = dup( 1 );
        tmperr = dup( 2 );

        dup2( fdout, 1 );  // redirect stderr
        dup2( fderr, 2 );  // redirect stdout
    }

    string pkgdir = package->path() + "/" + package->name();
    chdir( pkgdir.c_str() );

    // -- build
    string cmd = "pkgmk";
    string args = "-d " + parser->pkgmkArgs();
    Process makeProc( cmd, args );
    if ( makeProc.executeShell() ) {
        result = PKGMK_FAILURE;
    } else {
        // -- update
        string pkgdest = getPkgDest();
        if ( pkgdest != "" ) {
            pkgdir = pkgdest;
            cout << "Using PKGMK_PACKAGE_DIR: " << pkgdir << endl;
        }

        // the following chdir is a noop if usePkgDest() returns false
        if ( chdir( pkgdir.c_str() ) != 0 ) {
            result = PKGDEST_ERROR;
        } else {
            cmd = "pkgadd";

            args = "";
            if ( update ) {
                args += "-u ";
            }
            if ( !parser->pkgaddArgs().empty() ) {
                args += parser->pkgaddArgs() + " ";
            }
            args +=
                package->name()    + "#" +
                package->version() + "-" +
                package->release() + ".pkg.tar.gz";

            string commandName = "prt-get";
            if ( parser->wasCalledAsPrtCached() ) {
                commandName = "prt-cache";
            }
            cout << commandName << ": " << cmd << " " << args << endl;

            Process installProc( cmd, args );
            if ( installProc.executeShell() ) {
                result = PKGADD_FAILURE;
            }
        }
    }

    if ( m_config->writeLog() ) {

#ifdef USE_LOCKING
        lockFile.unlock();
#endif

        // restore
        dup2( tmpout, 1 );
        dup2( tmperr, 2 );

        close ( fdout );
        close ( fderr );
    }
    return result;
}