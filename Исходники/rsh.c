int main (int argc, char **argv)
{
    int index;

    struct passwd *pw;

    struct servent *sp;

    sigset_t sigs, osigs;

    int asrsh, rem;

    pid_t pid = 0;

    uid_t uid;

    char *args, *host;

    set_program_name (argv[0]);

    asrsh = 0;
    host = user = NULL;

    /* If called as something other than "rsh", use it as the host name */
    {
        char *p = strrchr (argv[0], '/');

        if (p)
            ++p;
        else
            p = argv[0];
        if (strcmp (p, "rsh"))
            host = p;
        else
            asrsh = 1;
    }

    /* Parse command line */
    iu_argp_init ("rsh", default_program_authors);
    argp_parse (&argp, argc, argv, ARGP_IN_ORDER, &index, NULL);

    if (index < argc)
        host = argv[index++];

    /* To few args.  */
    if (!host)
        error (1, 0, "host not specified");

    /* If no further arguments, must have been called as rlogin. */
    if (!argv[index])
    {
        if (asrsh)
            *argv = (char *) "rlogin";
        seteuid (getuid ());
        setuid (getuid ());
        execv (PATH_RLOGIN, argv);
        error (1, errno, "cannot execute %s", PATH_RLOGIN);
    }

    argc -= index;
    argv += index;

    /* We must be setuid root.  */
    if (geteuid ())
        error (1, 0, "must be setuid root.\n");

    if (!(pw = getpwuid (uid = getuid ())))
        error (1, 0, "unknown user id");

    /* Accept user1@host format, though "-l user2" overrides user1 */
    {
        char *p = strchr (host, '@');

        if (p)
        {
            *p = '\0';
            if (!user && p > host)
                user = host;
            host = p + 1;
            if (*host == '\0')
                error (1, 0, "empty host name");
        }
    }

#if defined(KERBEROS) || defined(SHISHI)
# ifdef ENCRYPTION
    /* -x turns off -n */
    if (doencrypt)
        null_input_option = 0;
# endif
#endif

    args = copyargs (argv);

    sp = NULL;
#ifdef KERBEROS
    if (use_kerberos)
    {
        sp = getservbyname ((doencrypt ? "ekshell" : "kshell"), "tcp");
        if (sp == NULL)
        {
            use_kerberos = 0;
            warning ("can't get entry for %s/tcp service", doencrypt ? "ekshell" : "kshell");
        }
    }
#elif defined(SHISHI)
    if (use_kerberos)
    {
        sp = getservbyname ("kshell", "tcp");
        if (sp == NULL)
        {
            use_kerberos = 0;
            warning ("can't get entry for %s/tcp service", "kshell");
        }
    }
#endif
    if (sp == NULL)
        sp = getservbyname ("shell", "tcp");
    if (sp == NULL)
        error (1, 0, "shell/tcp: unknown service");


#if defined (KERBEROS) || defined(SHISHI)
  try_connect:
    if (use_kerberos)
    {
        struct hostent *hp;

        /* fully qualify hostname (needed for krb_realmofhost) */
        hp = gethostbyname (host);
        if (hp != NULL && !(host = strdup (hp->h_name)))
            error (1, errno, "strdup");

# if defined (KERBEROS)
        rem = KSUCCESS;
        errno = 0;
        if (dest_realm == NULL)
            dest_realm = krb_realmofhost (host);
# elif defined (SHISHI)
        rem = SHISHI_OK;
        errno = 0;
# endif

# ifdef ENCRYPTION
        if (doencrypt)
#  if defined(SHISHI)
        {
            int i;

            char *term;

            term = xmalloc (strlen (args) + 4);
            strcpy (term, "-x ");
            strcat (term, args);

            rem = krcmd_mutual (&h, &host, sp->s_port, &user, term, &rfd2, dest_realm, &enckey);
            if (rem > 0)
            {
                keytype = shishi_key_type (enckey);
                keylen = shishi_cipher_blocksize (keytype);

                ivtab[0] = &iv1;
                ivtab[1] = &iv2;
                ivtab[2] = &iv3;
                ivtab[3] = &iv4;

                for (i = 0; i < 4; i++)
                {
                    ivtab[i]->ivlen = keylen;

                    switch (keytype)
                    {
                        case SHISHI_DES_CBC_CRC:
                        case SHISHI_DES_CBC_MD4:
                        case SHISHI_DES_CBC_MD5:
                        case SHISHI_DES_CBC_NONE:
                        case SHISHI_DES3_CBC_HMAC_SHA1_KD:
                            ivtab[i]->keyusage = SHISHI_KEYUSAGE_KCMD_DES;
                            ivtab[i]->iv = malloc (ivtab[i]->ivlen);
                            memset (ivtab[i]->iv, 2 * i + 1 * (i < 2) - 4 * (i >= 2), ivtab[i]->ivlen);
                            ivtab[i]->ctx =
                                shishi_crypto (h, enckey, ivtab[i]->keyusage,
                                               shishi_key_type (enckey), ivtab[i]->iv, ivtab[i]->ivlen);
                            break;
                        case SHISHI_ARCFOUR_HMAC:
                        case SHISHI_ARCFOUR_HMAC_EXP:
                            ivtab[i]->keyusage = SHISHI_KEYUSAGE_KCMD_DES + 2 + 4 * i;
                            ivtab[i]->ctx =
                                shishi_crypto (h, enckey, ivtab[i]->keyusage, shishi_key_type (enckey), NULL, 0);
                            break;
                        default:
                            ivtab[i]->keyusage = SHISHI_KEYUSAGE_KCMD_DES + 2 + 4 * i;
                            ivtab[i]->iv = malloc (ivtab[i]->ivlen);
                            memset (ivtab[i]->iv, 0, ivtab[i]->ivlen);
                            ivtab[i]->ctx =
                                shishi_crypto (h, enckey, ivtab[i]->keyusage,
                                               shishi_key_type (enckey), ivtab[i]->iv, ivtab[i]->ivlen);
                    }
                }
            }
            free (term);
        }
        else
#  else
            rem = krcmd_mutual (&host, sp->s_port, user, args, &rfd2, dest_realm, &cred, schedule);
        else
#  endif
# endif
            rem = krcmd (
# if defined (SHISHI)
                            &h, &host, sp->s_port, &user, args, &rfd2, dest_realm);
# else
                            &host, sp->s_port, user, args, &rfd2, dest_realm);
# endif
        if (rem < 0)
        {
            use_kerberos = 0;
            sp = getservbyname ("shell", "tcp");
            if (sp == NULL)
                error (1, 0, "shell/tcp: unknown service");
            if (errno == ECONNREFUSED)
                warning ("remote host doesn't support Kerberos");
            if (errno == ENOENT)
                warning ("can't provide Kerberos auth data");
            goto try_connect;
        }
    }