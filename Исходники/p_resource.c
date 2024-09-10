static void
pdf_read_resourcefile(PDF *p, const char *filename)
{
    pdc_file   *fp = NULL;
    char      **linelist;
    char       *line;
    char       *category = NULL;
    char       *uprfilename = NULL;
#if defined(AS400) || defined(WIN32)
#define BUFSIZE 2048
    char        buffer[BUFSIZE];
#ifdef WIN32
    char        regkey[128];
    HKEY        hKey = NULL;
    DWORD       size, lType;
#endif
#endif
    int         il, nlines = 0, nextcat, begin;

#ifdef WIN32

/* don't add patchlevel's to registry searchpath */
#define stringiz1(x)	#x
#define stringiz(x)	stringiz1(x)

#define PDFLIBKEY  "Software\\PDFlib\\PDFlib\\"

    strcpy(regkey, PDFLIBKEY);
    strcat(regkey, PDFLIB_VERSIONSTRING);

    /* process registry entries */
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, regkey, 0L,
        (REGSAM) KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
    {
        size = BUFSIZE - 2;
        if (RegQueryValueExA(hKey, "SearchPath", (LPDWORD) NULL,
                             &lType, (LPBYTE) buffer, &size)
            == ERROR_SUCCESS && *buffer)
        {
            char **pathlist;
            int ip, np;

            np = pdc_split_stringlist(p->pdc, buffer,
                                      ";", &pathlist);
            for (ip = 0; ip < np; ip++)
                pdf_add_resource(p, "SearchPath", pathlist[ip]);
            pdc_cleanup_stringlist(p->pdc, pathlist);
        }

        size = BUFSIZE - 2;
        if (RegQueryValueExA(hKey, "prefix", (LPDWORD) NULL,
                             &lType, (LPBYTE) buffer, &size)
            == ERROR_SUCCESS && *buffer)
        {
            /* '/' because of downward compatibility */
            if (p->prefix)
            {
                pdc_free(p->pdc, p->prefix);
                p->prefix = NULL;
            }
            p->prefix = pdc_strdup(p->pdc,
                            &buffer[buffer[0] == '/' ? 1 : 0]);
        }

        RegCloseKey(hKey);
    }
#endif  /* WIN32 */

#ifdef AS400
    strcpy (buffer, "/pdflib/");
    strcat (buffer, PDFLIB_VERSIONSTRING);
    il = (int) strlen(buffer);
    strcat (buffer, "/fonts");
    pdf_add_resource(p, "SearchPath", buffer);
    strcpy(&buffer[il], "/bind/data");
    pdf_add_resource(p, "SearchPath", buffer);
#endif  /* AS400 */

    /* searching for name of upr file */
    uprfilename = (char *)filename;
    if (!uprfilename || *uprfilename == '\0')
    {
        /* user-supplied upr file */
        uprfilename = pdc_getenv(RESOURCEFILE);
        if (!uprfilename || *uprfilename == '\0')
        {
            uprfilename = DEFAULTRESOURCEFILE;

            /* user-supplied upr file */
            fp = pdf_fopen(p, uprfilename, NULL, 0);
            if (fp == NULL)
            {
                uprfilename = NULL;
#ifdef WIN32
                /* process registry entries */
                if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, regkey, 0L,
                    (REGSAM) KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
                {
                    size = BUFSIZE - 2;
                    if (RegQueryValueExA(hKey, "resourcefile", (LPDWORD) NULL,
                                         &lType, (LPBYTE) buffer, &size)
                        == ERROR_SUCCESS && *buffer)
                    {
                        uprfilename = buffer;
                    }

                    RegCloseKey(hKey);
                }
#endif  /* WIN32 */
            }
        }

        if (!uprfilename || *uprfilename == '\0')
            return;

        if (p->resourcefilename)
        {
            pdc_free(p->pdc, p->resourcefilename);
            p->resourcefilename = NULL;
        }
        p->resourcefilename = pdc_strdup(p->pdc, uprfilename);
    }

    /* read upr file */
    if ((fp == NULL) && ((fp = pdf_fopen(p, uprfilename, "UPR ", 0)) == NULL))
	pdc_error(p->pdc, -1, 0, 0, 0, 0);

    nlines = pdc_read_textfile(p->pdc, fp, &linelist);
    pdc_fclose(fp);

    if (!nlines) return;

    /* Lines loop */
    begin = 1;
    nextcat = 0;
    for (il = 0; il < nlines; il++)
    {
        line = linelist[il];

        /* Next category */
        if (line[0] == '.' && strlen(line) == 1)
        {
            begin = 0;
            nextcat = 1;
            continue;
        }

        /* Skip category list */
        if (begin) continue;

        /* Prefiex or category expected */
        if (nextcat)
        {
            /* Directory prefix */
            if (line[0] == '/')
            {
                if (p->prefix)
                {
                    pdc_free(p->pdc, p->prefix);
                    p->prefix = NULL;
                }
                p->prefix = pdc_strdup(p->pdc, &line[1]);
                continue;
            }

            /* Ressource Category */
            category = line;
            nextcat = 0;
            continue;
        }

        /* Add resource */
        pdf_add_resource(p, category, line);
    }

    pdc_cleanup_stringlist(p->pdc, linelist);
}