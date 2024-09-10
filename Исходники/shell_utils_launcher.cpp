void ProgramRunner::launchProcess(int child_stdout) {
    std::vector<std::string> envStrings;
    for (const auto& envKeyValue : _envp) {
        envStrings.emplace_back(envKeyValue.first + '=' + envKeyValue.second);
    }

#ifdef _WIN32
    stringstream ss;
    for (unsigned i = 0; i < _argv.size(); i++) {
        if (i)
            ss << ' ';
        if (_argv[i].find(' ') == string::npos)
            ss << _argv[i];
        else {
            ss << '"';
            // escape all embedded quotes
            for (size_t j = 0; j < _argv[i].size(); ++j) {
                if (_argv[i][j] == '"')
                    ss << '\\';
                ss << _argv[i][j];
            }
            ss << '"';
        }
    }

    std::wstring args = toNativeString(ss.str().c_str());

    // Construct the environment block which the new process will use.
    // An environment block is a NULL terminated array of NULL terminated WCHAR strings. The
    // strings are of the form "name=value\0". Because the strings are variable length, we must
    // precompute the size of the array before we may allocate it.
    size_t environmentBlockSize = 0;
    std::vector<std::wstring> nativeEnvStrings;

    // Compute the size of the environment block, in characters. Note that we have to count
    // wchar_t characters, which we'll actually be storing in the block later, rather than UTF8
    // characters we have in _envp and need to convert.
    for (const std::string& envKeyValue : envStrings) {
        std::wstring nativeKeyValue = toNativeString(envKeyValue.c_str());
        environmentBlockSize += (nativeKeyValue.size() + 1);
        nativeEnvStrings.emplace_back(std::move(nativeKeyValue));
    }

    // Reserve space for the final NULL character which terminates the environment block
    environmentBlockSize += 1;

    auto lpEnvironment = stdx::make_unique<wchar_t[]>(environmentBlockSize);
    size_t environmentOffset = 0;
    for (const std::wstring& envKeyValue : nativeEnvStrings) {
        // Ensure there is enough room to write the string, the string's NULL byte, and the block's
        // NULL byte
        invariant(environmentOffset + envKeyValue.size() + 1 + 1 <= environmentBlockSize);
        wcscpy_s(
            lpEnvironment.get() + environmentOffset, envKeyValue.size() + 1, envKeyValue.c_str());
        environmentOffset += envKeyValue.size();
        std::memset(lpEnvironment.get() + environmentOffset, 0, sizeof(wchar_t));
        environmentOffset += 1;
    }
    std::memset(lpEnvironment.get() + environmentOffset, 0, sizeof(wchar_t));

    HANDLE h = reinterpret_cast<HANDLE>(_get_osfhandle(child_stdout));
    invariant(h != INVALID_HANDLE_VALUE);
    invariant(SetHandleInformation(h, HANDLE_FLAG_INHERIT, 1));

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdError = h;
    si.hStdOutput = h;
    si.dwFlags |= STARTF_USESTDHANDLES;

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    DWORD dwCreationFlags = 0;
    dwCreationFlags |= CREATE_UNICODE_ENVIRONMENT;

    bool success = CreateProcessW(nullptr,
                                  const_cast<LPWSTR>(args.c_str()),
                                  nullptr,
                                  nullptr,
                                  true,
                                  dwCreationFlags,
                                  lpEnvironment.get(),
                                  nullptr,
                                  &si,
                                  &pi) != 0;
    if (!success) {
        const auto ewd = errnoWithDescription();
        ss << "couldn't start process " << _argv[0] << "; " << ewd;
        uasserted(14042, ss.str());
    }

    CloseHandle(pi.hThread);
    invariant(SetHandleInformation(h, HANDLE_FLAG_INHERIT, 0));

    _pid = ProcessId::fromNative(pi.dwProcessId);
    registry.insertHandleForPid(_pid, pi.hProcess);
#else

    std::string execErrMsg = str::stream() << "Unable to start program " << _argv[0];
    auto constCharStorageMaker = [](const std::vector<std::string>& in) {
        std::vector<const char*> out;
        std::transform(in.begin(), in.end(), std::back_inserter(out), [](const std::string& x) {
            return x.c_str();
        });
        out.push_back(nullptr);
        return out;
    };

    std::vector<const char*> argvStorage = constCharStorageMaker(_argv);
    std::vector<const char*> envpStorage = constCharStorageMaker(envStrings);

    pid_t nativePid = fork();
    _pid = ProcessId::fromNative(nativePid);
    // Async signal unsafe functions should not be called in the child process.

    if (nativePid == -1) {
        // Fork failed so it is time for the process to exit
        const auto ewd = errnoWithDescription();
        cout << "ProgramRunner is unable to fork child process: " << ewd << endl;
        fassertFailed(34363);
    }

    if (nativePid == 0) {
        // DON'T ASSERT IN THIS BLOCK - very bad things will happen
        //
        // Also, deliberately call _exit instead of quickExit. We intended to
        // fork() and exec() here, so we never want to run any form of cleanup.
        // This includes things that quickExit calls, such as atexit leak
        // checks.

        if (dup2(child_stdout, STDOUT_FILENO) == -1 || dup2(child_stdout, STDERR_FILENO) == -1) {
            // Async signal unsafe code reporting a terminal error condition.
            perror("Unable to dup2 child output: ");
            _exit(-1);  // do not pass go, do not call atexit handlers
        }

        execve(argvStorage[0],
               const_cast<char**>(argvStorage.data()),
               const_cast<char**>(envpStorage.data()));

        // Async signal unsafe code reporting a terminal error condition.
        perror(execErrMsg.c_str());

        _exit(-1);
    }

#endif
}