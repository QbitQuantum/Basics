    virtual void run(Message& request, MessageResponder* out) {

        m_logger.log(L"invoked to run");
        // Deserialize the command line arguments.
        wchar_t* cmd_line;
        request.cast(&cmd_line, 0);
        int argc = 0;
        wchar_t** argv = CommandLineToArgvW(cmd_line, &argc);

        // The only command line argument is the name of the file to edit.
        if (argc == 1) {
            std::wstring docPath = argv[0];
            size_t dotIndex = docPath.rfind(L".");
            if (dotIndex == std::wstring::npos) {
                m_logger.log(docPath + L" file to launch has no extension");
                out->run(0, NULL);
            } else {
                std::wstring suffix = docPath.substr(dotIndex + 1);
                RegKey suffixesKey = RegKey::HKCU.open(Constants::registrySuffixes());
                RegKey suffixKey = suffixesKey.open(suffix);
                if (suffixKey.isGood()) {
                    std::wstring petname = suffixKey.getValue(Constants::registrySuffixPetname());
                    std::wstring appPath = suffixKey.getValue(Constants::registrySuffixAppName());
                    ActivePet* pet = m_world->load(petname);
                    if (pet) {
                        pet->send(makeLaunch(appPath, docPath, out));
                    } else {
                        out->run(0, NULL);
                    }
                } else {
                    //use icebox, suffix not recognized
                    ActivePet* pet = m_world->load(Constants::icebox());
                    if (pet) {
                        pet->send(new SyncAndShell(docPath, out));
                    } else {
                        out->run(0, NULL);
                    }
                }
            }
        } else {
            out->run(0, NULL);
        }
    }