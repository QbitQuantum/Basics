    static char* FindCGroupPathForSubsystem(bool (*is_subsystem)(const char *))
    {
        char *line = nullptr;
        size_t lineLen = 0;
        size_t maxLineLen = 0;
        char *subsystem_list = nullptr;
        char *cgroup_path = nullptr;
        bool result = false;

        FILE *cgroupfile = fopen(PROC_CGROUP_FILENAME, "r");
        if (cgroupfile == nullptr)
            goto done;

        while (!result && getline(&line, &lineLen, cgroupfile) != -1)
        {
            if (subsystem_list == nullptr || lineLen > maxLineLen)
            {
                PAL_free(subsystem_list);
                PAL_free(cgroup_path);
                subsystem_list = (char*)PAL_malloc(lineLen+1);
                if (subsystem_list == nullptr)
                    goto done;
                cgroup_path = (char*)PAL_malloc(lineLen+1);
                if (cgroup_path == nullptr)
                    goto done;
                maxLineLen = lineLen;
            }

            // See man page of proc to get format for /proc/self/cgroup file
            int sscanfRet = sscanf_s(line, 
                                     "%*[^:]:%[^:]:%s",
                                     subsystem_list, lineLen+1,
                                     cgroup_path, lineLen+1);
            if (sscanfRet != 2)
            {
                _ASSERTE(!"Failed to parse cgroup info file contents with sscanf_s.");
                goto done;
            }

            char* context = nullptr;
            char* strTok = strtok_s(subsystem_list, ",", &context); 
            while (strTok != nullptr)
            {
                if (is_subsystem(strTok))
                {
                    result = true;
                    break;  
                }
                strTok = strtok_s(nullptr, ",", &context);
            }
        }
    done:
        PAL_free(subsystem_list);
        if (!result)
        {
            PAL_free(cgroup_path);
            cgroup_path = nullptr;
        }
        free(line);
        if (cgroupfile)
            fclose(cgroupfile);
        return cgroup_path;
    }