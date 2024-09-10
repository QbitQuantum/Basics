/* Get domain specific configuration info.  We are returning void because if anything goes wrong
   we just return defaults.
 */
void 
GetDomainLogonOptions( PLUID lpLogonId, char * username, char * domain, LogonOptions_t *opt ) {
    HKEY hkParm = NULL; /* Service parameter */
    HKEY hkNp = NULL;   /* network provider key */
    HKEY hkDoms = NULL; /* domains key */
    HKEY hkDom = NULL;  /* DOMAINS/domain key */
    HKEY hkTemp = NULL;
    LONG rv;
    DWORD dwSize;
    DWORD dwType;
    DWORD dwDummy;
    char computerName[MAX_COMPUTERNAME_LENGTH + 1]="";
    char *effDomain = NULL;

    memset(opt, 0, sizeof(LogonOptions_t));

    DebugEvent("In GetDomainLogonOptions for user [%s] in domain [%s]", username, domain);
    /* If the domain is the same as the Netbios computer name, we use the LOCALHOST domain name*/
    opt->flags = LOGON_FLAG_REMOTE;
    if(domain) {
        dwSize = MAX_COMPUTERNAME_LENGTH + 1;
        if(GetComputerName(computerName, &dwSize)) {
            if(!cm_stricmp_utf8(computerName, domain)) {
                effDomain = "LOCALHOST";
                opt->flags = LOGON_FLAG_LOCAL;
            }
        }
        if (effDomain == NULL)
            effDomain = domain;
    }

    rv = RegOpenKeyEx( HKEY_LOCAL_MACHINE, AFSREG_CLT_SVC_PARAM_SUBKEY, 0, KEY_READ, &hkParm );
    if(rv != ERROR_SUCCESS) {
        hkParm = NULL;
        DebugEvent("GetDomainLogonOption: Can't open parms key [%d]", rv);
    }

    rv = RegOpenKeyEx( HKEY_LOCAL_MACHINE, AFSREG_CLT_SVC_PROVIDER_SUBKEY, 0, KEY_READ, &hkNp );
    if(rv != ERROR_SUCCESS) {
        hkNp = NULL;
        DebugEvent("GetDomainLogonOptions: Can't open NP key [%d]", rv);
    }

    if(hkNp) {
        rv = RegOpenKeyEx( hkNp, REG_CLIENT_DOMAINS_SUBKEY, 0, KEY_READ, &hkDoms );
        if( rv != ERROR_SUCCESS ) {
            hkDoms = NULL;
            DebugEvent("GetDomainLogonOptions: Can't open Domains key [%d]", rv);
        }
    }

    if(hkDoms && effDomain) {
        rv = RegOpenKeyEx( hkDoms, effDomain, 0, KEY_READ, &hkDom );
        if( rv != ERROR_SUCCESS ) {
            hkDom = NULL;
            DebugEvent("GetDomainLogonOptions: Can't open domain key for [%s] [%d]", effDomain, rv);
            /* If none of the domains match, we shouldn't use the domain key either */
            RegCloseKey(hkDoms);
            hkDoms = NULL;
        }
    } else
        DebugEvent0("Not opening domain key");

    /* Each individual can either be specified on the domain key, the domains key or in the
       net provider key.  They fail over in that order.  If none is found, we just use the 
       defaults. */

    /* LogonOption */
    LOOKUPKEYCHAIN(opt->LogonOption, REG_DWORD, DEFAULT_LOGON_OPTION, REG_CLIENT_LOGON_OPTION_PARM);

    /* FailLoginsSilently */
    dwSize = sizeof(dwDummy);
    rv = RegQueryValueEx(hkParm, REG_CLIENT_FAIL_SILENTLY_PARM, 0, &dwType, (LPBYTE) &dwDummy, &dwSize);
    if (rv != ERROR_SUCCESS)
        LOOKUPKEYCHAIN(dwDummy, REG_DWORD, DEFAULT_FAIL_SILENTLY, REG_CLIENT_FAIL_SILENTLY_PARM);
    opt->failSilently = dwDummy ? 1 :0;

    /* Retry interval */
    LOOKUPKEYCHAIN(opt->retryInterval, REG_DWORD, DEFAULT_RETRY_INTERVAL, REG_CLIENT_RETRY_INTERVAL_PARM);

    /* Sleep interval */
    LOOKUPKEYCHAIN(opt->sleepInterval, REG_DWORD, DEFAULT_SLEEP_INTERVAL, REG_CLIENT_SLEEP_INTERVAL_PARM);

    if(!ISLOGONINTEGRATED(opt->LogonOption)) {
        DebugEvent0("Integrated logon disabled");
        goto cleanup; /* no need to lookup the logon script */
    }

    /* come up with SMB username */
    if(ISHIGHSECURITY(opt->LogonOption)) {
        DebugEvent0("High Security Mode active");
        opt->smbName = malloc( MAXRANDOMNAMELEN );
        if (opt->smbName == NULL)
            goto cleanup;
        GenRandomName(opt->smbName);
    } else if (lpLogonId) {
        /* username and domain for logon session is not necessarily the same as
           username and domain passed into network provider. */
        PSECURITY_LOGON_SESSION_DATA plsd=NULL;
        char lsaUsername[MAX_USERNAME_LENGTH]="";
        char lsaDomain[MAX_DOMAIN_LENGTH]="";
        size_t len, tlen;
        NTSTATUS Status;

        Status = LsaGetLogonSessionData(lpLogonId, &plsd);
        if ( FAILED(Status) || plsd == NULL ) {
            DebugEvent("LsaGetLogonSessionData failed [0x%x]", Status);
            goto bad_strings;
        }
        
        if (!UnicodeStringToANSI(plsd->UserName, lsaUsername, MAX_USERNAME_LENGTH))
            goto bad_strings;

        if (!UnicodeStringToANSI(plsd->LogonDomain, lsaDomain, MAX_DOMAIN_LENGTH))
            goto bad_strings;

        DebugEvent("PLSD username[%s] domain[%s]",lsaUsername,lsaDomain);

        if(SUCCEEDED(StringCbLength(lsaUsername, MAX_USERNAME_LENGTH, &tlen)))
            len = tlen;
        else
            goto bad_strings;

        if(SUCCEEDED(StringCbLength(lsaDomain, MAX_DOMAIN_LENGTH, &tlen)))
            len += tlen;
        else
            goto bad_strings;

        len += 2;

        opt->smbName = malloc(len);
        if (opt->smbName == NULL)
            goto cleanup;

        StringCbCopy(opt->smbName, len, lsaDomain);
        StringCbCat(opt->smbName, len, "\\");
        StringCbCat(opt->smbName, len, lsaUsername);

        strlwr(opt->smbName);

      bad_strings:
        if (plsd)
            LsaFreeReturnBuffer(plsd);
    }
    if (opt->smbName == NULL) {
        size_t len;

        DebugEvent("Constructing username using [%s] and [%s]",
                   username, domain);
 
        len = strlen(username) + strlen(domain) + 2;

        opt->smbName = malloc(len);
        if (opt->smbName == NULL)
            goto cleanup;

        StringCbCopy(opt->smbName, len, domain);
        StringCbCat(opt->smbName, len, "\\");
        StringCbCat(opt->smbName, len, username);

        strlwr(opt->smbName);
    }

    DebugEvent0("Looking up logon script");
    /* Logon script */
    /* First find out where the key is */
    hkTemp = NULL;
    rv = ~ERROR_SUCCESS;
    dwType = 0;
    if(hkDom)
        rv = RegQueryValueExW(hkDom, REG_CLIENT_LOGON_SCRIPT_PARMW, 0, &dwType, NULL, &dwSize);
    if(rv == ERROR_SUCCESS && (dwType == REG_SZ || dwType == REG_EXPAND_SZ)) {
        hkTemp = hkDom;
        DebugEvent0("Located logon script in hkDom");
    }
    else if(hkDoms) {
        rv = RegQueryValueExW(hkDoms, REG_CLIENT_LOGON_SCRIPT_PARMW, 0, &dwType, NULL, &dwSize);
        if(rv == ERROR_SUCCESS && !hkTemp && (dwType == REG_SZ || dwType == REG_EXPAND_SZ)) {
            hkTemp = hkDoms;
            DebugEvent0("Located logon script in hkDoms");
        }
        /* Note that the LogonScript in the NP key is only used if we are doing high security. */
        else if(hkNp && ISHIGHSECURITY(opt->LogonOption)) {
            rv = RegQueryValueExW(hkNp, REG_CLIENT_LOGON_SCRIPT_PARMW, 0, &dwType, NULL, &dwSize);
            if(rv == ERROR_SUCCESS && !hkTemp && (dwType == REG_SZ || dwType == REG_EXPAND_SZ)) {
                hkTemp = hkNp;
                DebugEvent0("Located logon script in hkNp");
            }
        }
    }

    if(hkTemp) {
        WCHAR *regscript	= NULL;
        WCHAR *regexscript	= NULL;
        WCHAR *regexuscript	= NULL;
        WCHAR *wuname		= NULL;
        HRESULT hr;

        size_t len;

        StringCbLength(opt->smbName, MAX_USERNAME_LENGTH, &len);
        len ++;

        wuname = malloc(len * sizeof(WCHAR));
        if (!wuname)
            goto doneLogonScript;
        MultiByteToWideChar(CP_ACP,0,opt->smbName,-1,wuname,(int)(len*sizeof(WCHAR)));

        DebugEvent("Username is set for [%S]", wuname);

        /* dwSize still has the size of the required buffer in bytes. */
        regscript = malloc(dwSize);
        if (!regscript)
            goto doneLogonScript;
        rv = RegQueryValueExW(hkTemp, REG_CLIENT_LOGON_SCRIPT_PARMW, 0, &dwType, (LPBYTE) regscript, &dwSize);
        if(rv != ERROR_SUCCESS) {/* what the ..? */
            DebugEvent("Can't look up logon script rv [%d] size [%d] gle %d",rv, dwSize, GetLastError());
            goto doneLogonScript;
        }

        DebugEvent("Found logon script [%S]", regscript);

        if(dwType == REG_EXPAND_SZ) {
            DWORD dwReq;

            dwSize += MAX_PATH * sizeof(WCHAR);  /* make room for environment expansion. */
            regexscript = malloc(dwSize);
            if (!regexscript)
                goto doneLogonScript;
            dwReq = ExpandEnvironmentStringsW(regscript, regexscript, dwSize / sizeof(WCHAR));
            free(regscript);
            regscript = regexscript;
            regexscript = NULL;
            if(dwReq > (dwSize / sizeof(WCHAR))) {
                DebugEvent0("Overflow while expanding environment strings.");
                goto doneLogonScript;
            }
        }

        DebugEvent("After expanding env strings [%S]", regscript);

        if(wcsstr(regscript, L"%s")) {
            dwSize += (DWORD)(len * sizeof(WCHAR)); /* make room for username expansion */
            regexuscript = (WCHAR *) LocalAlloc(LMEM_FIXED, dwSize);
            if (!regexuscript)
                goto doneLogonScript;
            hr = StringCbPrintfW(regexuscript, dwSize, regscript, wuname);
        } else {
            regexuscript = (WCHAR *) LocalAlloc(LMEM_FIXED, dwSize);
            if (!regexuscript)
                goto doneLogonScript;
            hr = StringCbCopyW(regexuscript, dwSize, regscript);
        }

        DebugEvent("After expanding username [%S]", regexuscript);

        if(hr == S_OK)
            opt->logonScript = regexuscript;
        else
            LocalFree(regexuscript);

      doneLogonScript:
        if(wuname) free(wuname);
        if(regscript) free(regscript);
        if(regexscript) free(regexscript);
    }

    DebugEvent0("Looking up TheseCells");
    /* TheseCells */
    /* First find out where the key is */
    hkTemp = NULL;
    rv = ~ERROR_SUCCESS;
    dwSize = 0;
    if (hkDom)
        rv = RegQueryValueEx(hkDom, REG_CLIENT_THESE_CELLS_PARM, 0, &dwType, NULL, &dwSize);
    if (rv == ERROR_SUCCESS && dwType == REG_MULTI_SZ) {
        hkTemp = hkDom;
        DebugEvent("Located TheseCells in hkDom size %d", dwSize);
    } else if (hkDoms) {
        rv = RegQueryValueEx(hkDoms, REG_CLIENT_THESE_CELLS_PARM, 0, &dwType, NULL, &dwSize);
        if (rv == ERROR_SUCCESS && !hkTemp && dwType == REG_MULTI_SZ) {
            hkTemp = hkDoms;
            DebugEvent("Located TheseCells in hkDoms size %d", dwSize);
        } else if (hkNp) {
            rv = RegQueryValueEx(hkNp, REG_CLIENT_THESE_CELLS_PARM, 0, &dwType, NULL, &dwSize);
            if (rv == ERROR_SUCCESS && !hkTemp && dwType == REG_MULTI_SZ) {
                hkTemp = hkNp;
                DebugEvent("Located TheseCells in hkNp size %d", dwSize);
            }
        }
    }

    if (hkTemp) {
        CHAR * thesecells = NULL;

        /* dwSize still has the size of the required buffer in bytes. */
        thesecells = malloc(dwSize*2);
        if (!thesecells)
            goto doneTheseCells;
        dwSize *= 2;
        SetLastError(0);
        rv = RegQueryValueEx(hkTemp, REG_CLIENT_THESE_CELLS_PARM, 0, NULL, (LPBYTE) thesecells, &dwSize);
        if(rv != ERROR_SUCCESS) {/* what the ..? */
            DebugEvent("Can't look up TheseCells rv [%d] size [%d] gle [%d]",rv, dwSize, GetLastError());
            goto doneTheseCells;
        }

        DebugEvent("Found TheseCells [%s]", thesecells);
        opt->theseCells = thesecells;
        thesecells = NULL;

      doneTheseCells:
        if (thesecells) free(thesecells);
    }

    DebugEvent0("Looking up Realm");
    /* Realm */
    /* First find out where the key is */
    hkTemp = NULL;
    rv = ~ERROR_SUCCESS;
    dwSize = 0;
    if (hkDom)
        rv = RegQueryValueEx(hkDom, REG_CLIENT_REALM_PARM, 0, &dwType, NULL, &dwSize);
    if (rv == ERROR_SUCCESS && dwType == REG_SZ) {
        hkTemp = hkDom;
        DebugEvent("Located Realm in hkDom size %d", dwSize);
    } else if (hkDoms) {
        rv = RegQueryValueEx(hkDoms, REG_CLIENT_REALM_PARM, 0, &dwType, NULL, &dwSize);
        if (rv == ERROR_SUCCESS && !hkTemp && dwType == REG_SZ) {
            hkTemp = hkDoms;
            DebugEvent("Located Realm in hkDoms size %d", dwSize);
        } else if (hkNp) {
            rv = RegQueryValueEx(hkNp, REG_CLIENT_REALM_PARM, 0, &dwType, NULL, &dwSize);
            if (rv == ERROR_SUCCESS && !hkTemp && dwType == REG_SZ) {
                hkTemp = hkNp;
                DebugEvent("Located Realm in hkNp size %d", dwSize);
            }
        }
    }

    if (hkTemp) {
        CHAR * realm = NULL;

        /* dwSize still has the size of the required buffer in bytes. */
        realm = malloc(dwSize*2);
        if (!realm)
            goto doneRealm;
        dwSize *=2;
        SetLastError(0);
        rv = RegQueryValueEx(hkTemp, REG_CLIENT_REALM_PARM, 0, NULL, (LPBYTE) realm, &dwSize);
        if(rv != ERROR_SUCCESS) {/* what the ..? */
            DebugEvent("Can't look up Realm rv [%d] size [%d] gle [%d]",rv, dwSize, GetLastError());
            goto doneRealm;
        }

        DebugEvent("Found Realm [%s]", realm);
        opt->realm = realm;
        realm = NULL;

      doneRealm:
        if (realm) free(realm);
    }

  cleanup:
    if(hkNp) RegCloseKey(hkNp);
    if(hkDom) RegCloseKey(hkDom);
    if(hkDoms) RegCloseKey(hkDoms);
    if(hkParm) RegCloseKey(hkParm);
}       