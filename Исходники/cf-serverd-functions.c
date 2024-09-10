int OpenReceiverChannel(void)
{
    struct addrinfo *response, *ap;
    struct addrinfo query = {
        .ai_flags = AI_PASSIVE,
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM
    };

    /* Listen to INADDR(6)_ANY if BINDINTERFACE unset. */
    char *ptr = NULL;
    if (BINDINTERFACE[0] != '\0')
    {
        ptr = BINDINTERFACE;
    }

    char servname[10];
    snprintf(servname, 10, "%d", CFENGINE_PORT);

    /* Resolve listening interface. */
    if (getaddrinfo(ptr, servname, &query, &response) != 0)
    {
        Log(LOG_LEVEL_ERR, "DNS/service lookup failure. (getaddrinfo: %s)", GetErrorStr());
        return -1;
    }

    int sd = -1;
    for (ap = response; ap != NULL; ap = ap->ai_next)
    {
        if ((sd = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol)) == -1)
        {
            continue;
        }

        int yes = 1;
        if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,
                       &yes, sizeof(yes)) == -1)
        {
            Log(LOG_LEVEL_ERR, "Socket option SO_REUSEADDR was not accepted. (setsockopt: %s)", GetErrorStr());
            exit(1);
        }

        struct linger cflinger = {
            .l_onoff = 1,
            .l_linger = 60
        };
        if (setsockopt(sd, SOL_SOCKET, SO_LINGER,
                       &cflinger, sizeof(cflinger)) == -1)
        {
            Log(LOG_LEVEL_ERR, "Socket option SO_LINGER was not accepted. (setsockopt: %s)", GetErrorStr());
            exit(1);
        }

        if (bind(sd, ap->ai_addr, ap->ai_addrlen) != -1)
        {
            if (LogGetGlobalLevel() >= LOG_LEVEL_DEBUG)
            {
                /* Convert IP address to string, no DNS lookup performed. */
                char txtaddr[CF_MAX_IP_LEN] = "";
                getnameinfo(ap->ai_addr, ap->ai_addrlen,
                            txtaddr, sizeof(txtaddr),
                            NULL, 0, NI_NUMERICHOST);
                Log(LOG_LEVEL_DEBUG, "Bound to address '%s' on '%s' = %d", txtaddr,
                    CLASSTEXT[VSYSTEMHARDCLASS], VSYSTEMHARDCLASS);
            }
            break;
        }
        else
        {
            Log(LOG_LEVEL_ERR, "Could not bind server address. (bind: %s)", GetErrorStr());
            cf_closesocket(sd);
        }
    }

    if (sd < 0)
    {
        Log(LOG_LEVEL_ERR, "Couldn't open/bind a socket");
        exit(1);
    }

    freeaddrinfo(response);
    return sd;
}

/*********************************************************************/
/* Level 3                                                           */
/*********************************************************************/

void CheckFileChanges(EvalContext *ctx, Policy **policy, GenericAgentConfig *config, time_t *last_policy_reload)
{
    time_t validated_at;

    Log(LOG_LEVEL_DEBUG, "Checking file updates for input file '%s'", config->input_file);

    validated_at = ReadTimestampFromPolicyValidatedMasterfiles(config);

    if (*last_policy_reload < validated_at)
    {
        *last_policy_reload = validated_at;

        Log(LOG_LEVEL_VERBOSE, "New promises detected...");

        if (GenericAgentArePromisesValid(config))
        {
            Log(LOG_LEVEL_INFO, "Rereading policy file '%s'", config->input_file);

            /* Free & reload -- lock this to avoid access errors during reload */
            
            EvalContextClear(ctx);

            free(SV.allowciphers);
            SV.allowciphers = NULL;

            DeleteItemList(SV.trustkeylist);
            DeleteItemList(SV.attackerlist);
            DeleteItemList(SV.nonattackerlist);
            DeleteItemList(SV.multiconnlist);

            DeleteAuthList(SV.admit);
            DeleteAuthList(SV.deny);

            DeleteAuthList(SV.varadmit);
            DeleteAuthList(SV.vardeny);

            DeleteAuthList(SV.roles);

            strcpy(VDOMAIN, "undefined.domain");

            SV.admit = NULL;
            SV.admittop = NULL;

            SV.varadmit = NULL;
            SV.varadmittop = NULL;

            SV.deny = NULL;
            SV.denytop = NULL;

            SV.vardeny = NULL;
            SV.vardenytop = NULL;

            SV.roles = NULL;
            SV.rolestop = NULL;

            SV.trustkeylist = NULL;
            SV.attackerlist = NULL;
            SV.nonattackerlist = NULL;
            SV.multiconnlist = NULL;

            PolicyDestroy(*policy);
            *policy = NULL;

            {
                char *existing_policy_server = ReadPolicyServerFile(GetWorkDir());
                SetPolicyServer(ctx, existing_policy_server);
                free(existing_policy_server);
            }
            UpdateLastPolicyUpdateTime(ctx);

            DetectEnvironment(ctx);
            KeepHardClasses(ctx);

            EvalContextClassPutHard(ctx, CF_AGENTTYPES[config->agent_type], "cfe_internal,source=agent");

            time_t t = SetReferenceTime();
            UpdateTimeClasses(ctx, t);
            *policy = GenericAgentLoadPolicy(ctx, config);
            KeepPromises(ctx, *policy, config);
            Summarize();
        }
        else
        {
            Log(LOG_LEVEL_INFO, "File changes contain errors -- ignoring");
        }
    }
    else
    {
        Log(LOG_LEVEL_DEBUG, "No new promises found");
    }
}