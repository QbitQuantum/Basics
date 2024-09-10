runner::env_vars_list_t runner::set_environment_for_process() const
{
    auto curr_vars = read_environment(GetEnvironmentStringsW());

    if (options.environmentMode == "user-default")
    {
        LPVOID envBlock = NULL;

        CreateEnvironmentBlock(&envBlock, NULL, FALSE);

        auto default_vars = read_environment((WCHAR*)envBlock);

        DestroyEnvironmentBlock(envBlock);

        for (auto i = default_vars.cbegin(); i != default_vars.cend(); ++i)
        {
            SetEnvironmentVariableA(i->first.c_str(), i->second.c_str());
        }

        for (auto i = curr_vars.cbegin(); i != curr_vars.cend(); ++i)
        {
            if (std::find(default_vars.cbegin(), default_vars.cend(), *i) == default_vars.cend())
            {
                SetEnvironmentVariableA(i->first.c_str(), NULL);
            }
        }
    }
    else if (options.environmentMode == "clear")
    {
        for (auto i = curr_vars.cbegin(); i != curr_vars.cend(); ++i)
        {
            SetEnvironmentVariableA(i->first.c_str(), NULL);
        }
    }

    for (auto i = options.environmentVars.cbegin(); i != options.environmentVars.cend(); ++i) {
        SetEnvironmentVariableA(i->first.c_str(), i->second.c_str());
    }

    return curr_vars;
}