bool get_timeout_params(int & connection_ms, int & request_ms)
{
    // Get starting_proc_timeout_ms parameter
    char * pPath = getenv ("CPM_ETC");
    if (!pPath)
    {
        EVENT_HANDLER_SYSTEMLOG->handle_event(
            _SRC,
            CPMDEvents::ev_env_var_not_defined,
            LM_ERROR,
            "CPM_ETC");
        return false;
    }

    std::string path(pPath);
    std::string::iterator it;
    for (it = path.begin(); it != path.end(); it++)
    {
        if (*it == '\\')
        {
            *it = '/';
        }
    }

    std::string file = path + "/cpm.cfg";
    file = FileShortcut_ns::FileShortcut::resolve(file);

    Config cfg;

    try
    {
        cfg.readFile(file.c_str());

        // root
        Setting & root = cfg.getRoot();

        // boot
        Setting & cpmd = root["cpmd"];

        // getting_reference_timeout_ms
        if (!cpmd.lookupValue("connection_timeout_ms", connection_ms))
        {
            EVENT_HANDLER_SYSTEMLOG->handle_event(
                _SRC,
                CPMDEvents::ev_field_not_found,
                LM_ERROR,
                file.c_str(),
                "cpmd/connection_timeout_ms");
            return false;
        }

        // getting_reference_tries
        if (!cpmd.lookupValue("request_timeout_ms", request_ms))
        {
            EVENT_HANDLER_SYSTEMLOG->handle_event(
                _SRC,
                CPMDEvents::ev_field_not_found,
                LM_ERROR,
                file.c_str(),
                "cpmd/request_timeout_ms");
            return false;
        }
    }
    catch(...)
    {
        EVENT_HANDLER_SYSTEMLOG->handle_event(
            _SRC,
            CPMDEvents::ev_exception_with_settings_file,
            LM_ERROR,
            file.c_str());
        return false;
    }

    return true;
}