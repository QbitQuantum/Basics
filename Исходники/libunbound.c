int
ub_ctx_resolvconf(struct ub_ctx* ctx, char* fname)
{
    FILE* in;
    int numserv = 0;
    char buf[1024];
    char* parse, *addr;
    int r;

    if(fname == NULL) {
#if !defined(UB_ON_WINDOWS) || !defined(HAVE_WINDOWS_H)
        fname = "/etc/resolv.conf";
#else
        FIXED_INFO *info;
        ULONG buflen = sizeof(*info);
        IP_ADDR_STRING *ptr;

        info = (FIXED_INFO *) malloc(sizeof (FIXED_INFO));
        if (info == NULL)
            return UB_READFILE;

        if (GetNetworkParams(info, &buflen) == ERROR_BUFFER_OVERFLOW) {
            free(info);
            info = (FIXED_INFO *) malloc(buflen);
            if (info == NULL)
                return UB_READFILE;
        }

        if (GetNetworkParams(info, &buflen) == NO_ERROR) {
            int retval=0;
            ptr = &(info->DnsServerList);
            while (ptr) {
                numserv++;
                if((retval=ub_ctx_set_fwd(ctx,
                                          ptr->IpAddress.String)!=0)) {
                    free(info);
                    return retval;
                }
                ptr = ptr->Next;
            }
            free(info);
            if (numserv==0)
                return UB_READFILE;
            return UB_NOERROR;
        }
        free(info);
        return UB_READFILE;
#endif /* WINDOWS */
    }
    in = fopen(fname, "r");
    if(!in) {
        /* error in errno! perror(fname) */
        return UB_READFILE;
    }
    while(fgets(buf, (int)sizeof(buf), in)) {
        buf[sizeof(buf)-1] = 0;
        parse=buf;
        while(*parse == ' ' || *parse == '\t')
            parse++;
        if(strncmp(parse, "nameserver", 10) == 0) {
            numserv++;
            parse += 10; /* skip 'nameserver' */
            /* skip whitespace */
            while(*parse == ' ' || *parse == '\t')
                parse++;
            addr = parse;
            /* skip [0-9a-fA-F.:]*, i.e. IP4 and IP6 address */
            while(isxdigit(*parse) || *parse=='.' || *parse==':')
                parse++;
            /* terminate after the address, remove newline */
            *parse = 0;

            if((r = ub_ctx_set_fwd(ctx, addr)) != UB_NOERROR) {
                fclose(in);
                return r;
            }
        }
    }
    fclose(in);
    if(numserv == 0) {
        /* from resolv.conf(5) if none given, use localhost */
        return ub_ctx_set_fwd(ctx, "127.0.0.1");
    }
    return UB_NOERROR;
}