    bool initializeServerGlobalState(bool isMongodShutdownSpecialCase) {

        Listener::globalTicketHolder.resize( cmdLine.maxConns );

#ifndef _WIN32
        if (!fs::is_directory(cmdLine.socket)) {
            cout << cmdLine.socket << " must be a directory" << endl;
            return false;
        }

        if (cmdLine.doFork) {
            fassert(16447, !cmdLine.logpath.empty() || cmdLine.logWithSyslog);

            cout.flush();
            cerr.flush();

            cmdLine.parentProc = getpid();

            // facilitate clean exit when child starts successfully
            setupLaunchSignals();

            cout << "about to fork child process, waiting until server is ready for connections."
                 << endl;

            pid_t child1 = fork();
            if (child1 == -1) {
                cout << "ERROR: stage 1 fork() failed: " << errnoWithDescription();
                _exit(EXIT_ABRUPT);
            }
            else if (child1) {
                // this is run in the original parent process
                int pstat;
                waitpid(child1, &pstat, 0);

                if (WIFEXITED(pstat)) {
                    if (WEXITSTATUS(pstat)) {
                        cout << "ERROR: child process failed, exited with error number "
                             << WEXITSTATUS(pstat) << endl;
                    }
                    else {
                        cout << "child process started successfully, parent exiting" << endl;
                    }

                    _exit(WEXITSTATUS(pstat));
                }

                _exit(50);
            }

            if ( chdir("/") < 0 ) {
                cout << "Cant chdir() while forking server process: " << strerror(errno) << endl;
                ::_exit(-1);
            }
            setsid();

            cmdLine.leaderProc = getpid();

            pid_t child2 = fork();
            if (child2 == -1) {
                cout << "ERROR: stage 2 fork() failed: " << errnoWithDescription();
                _exit(EXIT_ABRUPT);
            }
            else if (child2) {
                // this is run in the middle process
                int pstat;
                cout << "forked process: " << child2 << endl;
                waitpid(child2, &pstat, 0);

                if ( WIFEXITED(pstat) ) {
                    _exit( WEXITSTATUS(pstat) );
                }

                _exit(51);
            }

            // this is run in the final child process (the server)

            // stdout handled in initLogging
            //fclose(stdout);
            //freopen("/dev/null", "w", stdout);

            fclose(stderr);
            fclose(stdin);

            FILE* f = freopen("/dev/null", "w", stderr);
            if ( f == NULL ) {
                cout << "Cant reassign stderr while forking server process: " << strerror(errno) << endl;
                return false;
            }

            f = freopen("/dev/null", "r", stdin);
            if ( f == NULL ) {
                cout << "Cant reassign stdin while forking server process: " << strerror(errno) << endl;
                return false;
            }

            setupCoreSignals();
            setupSignals( true );
        }

        if (cmdLine.logWithSyslog) {
            StringBuilder sb;
            sb << cmdLine.binaryName << "." << cmdLine.port;
            Logstream::useSyslog( sb.str().c_str() );
        }
#endif
        if (!cmdLine.logpath.empty() && !isMongodShutdownSpecialCase) {
            fassert(16448, !cmdLine.logWithSyslog);
            string absoluteLogpath = boost::filesystem::absolute(
                    cmdLine.logpath, cmdLine.cwd).string();
            if (!initLogging(absoluteLogpath, cmdLine.logAppend)) {
                cout << "Bad logpath value: \"" << absoluteLogpath << "\"; terminating." << endl;
                return false;
            }
        }

        if (!cmdLine.pidFile.empty()) {
            writePidFile(cmdLine.pidFile);
        }

        if (!cmdLine.keyFile.empty()) {

            if (!setUpSecurityKey(cmdLine.keyFile)) {
                // error message printed in setUpPrivateKey
                return false;
            }

            noauth = false;
        }

#ifdef MONGO_SSL
        if (cmdLine.sslOnNormalPorts) {

            if ( cmdLine.sslPEMKeyFile.size() == 0 ) {
                log() << "need sslPEMKeyFile" << endl;
                return false;
            }

            cmdLine.sslServerManager = new SSLManager( false );
            if ( ! cmdLine.sslServerManager->setupPEM( cmdLine.sslPEMKeyFile , cmdLine.sslPEMKeyPassword ) ) {
                return false;
            }
        }
        else if ( cmdLine.sslPEMKeyFile.size() || cmdLine.sslPEMKeyPassword.size() ) {
            log() << "need to enable sslOnNormalPorts" << endl;
            return false;
        }
#endif

        return true;
    }