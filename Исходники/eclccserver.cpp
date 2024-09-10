    void processOption(const char *option, const char *value, StringBuffer &eclccCmd, StringBuffer &eclccProgName, IPipeProcess &pipe, bool isLocal)
    {
        if (memicmp(option, "eclcc-", 6) == 0 || *option=='-')
        {
            //Allow eclcc-xx-<n> so that multiple values can be passed through for the same named debug symbol
            const char * start = option + (*option=='-' ? 1 : 6);
            const char * finger = (*start=='-') ? start+1 : start; //support leading double dash
            const char * dash = strrchr(finger, '-');     // position of trailing dash, if present
            StringAttr optName;
            if (dash && (dash != start))
                optName.set(start, dash-start);
            else
                optName.set(start);

            if (!optName)
                return;

            if (stricmp(optName, "hook") == 0)
            {
                if (isLocal)
                    throw MakeStringException(0, "eclcc-hook option can not be set per-workunit");  // for security reasons
                eclccProgName.set(value);
            }
            else if (stricmp(optName, "compileOption") == 0)
                eclccCmd.appendf(" -Wc,%s", value);
            else if (stricmp(optName, "linkOption") == 0)
                eclccCmd.appendf(" -Wl,%s", value);
            else if (stricmp(optName, "includeLibraryPath") == 0)
                eclccCmd.appendf(" -I%s", value);
            else if (stricmp(optName, "libraryPath") == 0)
                eclccCmd.appendf(" -L%s", value);
            else if (strnicmp(optName, "-allow", 6)==0)
            {
                if (isLocal)
                    throw MakeStringException(0, "eclcc-allow option can not be set per-workunit");  // for security reasons
                eclccCmd.appendf(" -%s=%s", optName.get(), value);
            }
            else if (*optName == 'd')
            {
                //Short term work around for the problem that all debug names get lower-cased
                eclccCmd.appendf(" -D%s=%s", optName.get()+1, value);
            }
            else
                eclccCmd.appendf(" -%s=%s", optName.get(), value);
        }
        else if (strchr(option, '-'))
        {
            StringBuffer envVar;
            if (isLocal)
                envVar.append("WU_");
            envVar.append(option);
            envVar.toUpperCase();
            envVar.replace('-','_');
            pipe.setenv(envVar, value);
        }
        else
            eclccCmd.appendf(" -f%s=%s", option, value);
    }