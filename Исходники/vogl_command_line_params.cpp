    dynamic_string get_command_line()
    {
        dynamic_string cmd_line;

#ifdef VOGL_USE_WIN32_API
        cmd_line.set(GetCommandLineA());
#else
        dynamic_string_array params(get_command_line_params());

        for (uint32_t i = 0; i < params.size(); i++)
        {
            dynamic_string tmp(params[i]);

            // If the param is not already quoted, and it has any whitespace, then quote it. (The goal here is to ensure the split_command_line_params() method,
            // which was unfortunately written for Windows where it's trivial to get the full unparsed cmd line as a string, doesn't split up this parameter.)
            if ((tmp.front() != '\"') && (tmp.contains(' ') || tmp.contains('\t')))
                tmp = "\"" + tmp + "\"";

            if (cmd_line.get_len())
                cmd_line += " ";

            cmd_line += tmp;
        }
#endif
        return cmd_line;
    }