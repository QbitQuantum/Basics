static int dosignencode(int dosign, int doencode, int dodecode,
                        FILE *fpin, FILE *fpout,
                        int argc, char **argv)
{
    struct mimestack *boundary_stack=0;
    int iseof=0;

    while (!iseof)
    {
        static const char ct_s[]="content-type:";
        struct header *h=read_headers(&boundary_stack, &iseof, fpin,
                                      fpout, dodecode ? 0:1),
                         *hct;

        if (iseof && !h)
            continue;	/* Artifact */

        hct=find_header(h, ct_s);

        /*
        ** If this is a multipart MIME section, we can keep on
        ** truckin'.
        **
        */

        if (hct)
        {
            struct mime_header *mh=
                parse_mime_header(hct->header+
                                  (sizeof(ct_s)-1));

            const char *bv;

            if (strcasecmp(mh->header_name, "multipart/x-mimegpg")
                    == 0)
            {
                /* Punt */

                char *buf=malloc(strlen(hct->header)+100);
                const char *p;

                if (!buf)
                {
                    free_mime_header(mh);
                    free_header(h);
                    perror("malloc");
                    exit(1);
                }
                strcpy(buf, "Content-Type: multipart/mixed");
                p=strchr(hct->header, ';');
                strcat(buf, p ? p:"");
                free(hct->header);
                hct->header=buf;

                mh=parse_mime_header(hct->header+
                                     sizeof(ct_s)-1);
            }

            if (strncasecmp(mh->header_name, "multipart/", 10)==0
                    && (bv=get_mime_attr(mh, "boundary")) != 0

                    && (doencode & ENCODE_ENCAPSULATE) == 0
               )
            {
                struct header *p;

                push_mimestack(&boundary_stack, bv);

                if (dodecode)
                {
                    if (strcasecmp(mh->header_name,
                                   "multipart/signed")==0
                            && (dodecode & DECODE_CHECKSIGN)
                            && isgpg(mh))
                    {
                        print_noncontent_headers(h,
                                                 fpout
                                                );
                        free_mime_header(mh);
                        checksign(&boundary_stack,
                                  &iseof,
                                  h, fpin, fpout,
                                  argc, argv);
                        free_header(h);
                        continue;
                    }

                    if (strcasecmp(mh->header_name,
                                   "multipart/encrypted")
                            ==0
                            && (dodecode & DECODE_UNENCRYPT)
                            && isgpg(mh))
                    {
                        print_noncontent_headers(h,
                                                 fpout
                                                );
                        free_mime_header(mh);
                        decrypt(&boundary_stack,
                                &iseof,
                                h,
                                fpin, fpout,
                                argc, argv);
                        free_header(h);
                        continue;
                    }
                }

                for (p=h; p; p=p->next)
                {
                    fprintf(fpout, "%s", p->header);
                }

                putc('\n', fpout);
                free_header(h);
                free_mime_header(mh);

                find_boundary(&boundary_stack, &iseof, fpin,
                              fpout, dodecode ? 0:1);
                continue;
            }
            free_mime_header(mh);
        }

        if (dodecode)
        {
            struct header *p;
            int is_message_rfc822=0;

            for (p=h; p; p=p->next)
            {
                fprintf(fpout, "%s", p->header);
            }
            putc('\n', fpout);

            /*
            ** If this is a message/rfc822 attachment, we can
            ** resume reading the next set of headers.
            */

            hct=find_header(h, ct_s);
            if (hct)
            {
                struct mime_header *mh=
                    parse_mime_header(hct->header+
                                      (sizeof(ct_s)-1));

                if (strcasecmp(mh->header_name,
                               "message/rfc822") == 0)
                    is_message_rfc822=1;
                free_mime_header(mh);
            }
            free_header(h);

            if (!is_message_rfc822)
                find_boundary(&boundary_stack, &iseof,
                              fpin, fpout, 0);
            continue;
        }

        if (doencode)
            dogpgencrypt(&boundary_stack, h, &iseof,
                         fpin, fpout, argc, argv, dosign);
        else
            dogpgsign(&boundary_stack, h, &iseof,
                      fpin, fpout, argc, argv);
        free_header(h);
    }

    if (ferror(fpout))
        return (1);
    return (0);
}