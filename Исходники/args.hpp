        void fix_env(char **&en)
        {
            static char *dummy = 0;
            en = &dummy;
            wchar_t *wstrings = GetEnvironmentStringsW();
            if(!wstrings)
                return;
            try {
                wchar_t *wstrings_end = 0;
                int count = 0;
                for(wstrings_end = wstrings;*wstrings_end;wstrings_end+=wcslen(wstrings_end)+1)
                        count++;
                if(env_.convert(wstrings,wstrings_end)) {
                    envp_.resize(count+1,0);
                    char *p=env_.c_str();
                    int pos = 0;
                    for(int i=0;i<count;i++) {
                        if(*p!='=')
                            envp_[pos++] = p;
                        p+=strlen(p)+1;
                    }
                    en = &envp_[0];
                }
            }
            catch(...) {
                FreeEnvironmentStringsW(wstrings);
                throw;
            }
            FreeEnvironmentStringsW(wstrings);

        }