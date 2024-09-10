/* SMTP: mail */
static int smtpMail(int sfd,char *to,char *cc,char *bcc,char *from,char *rrr,char *rt,
                    char *subject,char *attach_file,char *msg_body_file,
                    char *the_msg,int is_mime,int add_dateh)
{
    char
        *os="Unix",
        boundary[17],
        related[17],
        alternative[17],
        mbuf[1024];

    int
        newline_before;

    Sll
        *oneline_attachment_list,
        *attachment_list,
        *embed_image_list;

#ifdef WINNT
    os="Windows";
#else
    os="Unix";
#endif /* WINNT */

    memset(boundary, 0, sizeof(boundary));
    memset(related, 0, sizeof(related));
    memset(alternative, 0, sizeof(alternative));

    attachment_list=get_attachment_list();
    embed_image_list = get_embed_image_attachment_list();
    oneline_attachment_list = get_oneline_attachment_list();
    if (attachment_list || embed_image_list || oneline_attachment_list)
    {
        is_mime=1;
    }

    if (subject)
    {
        memset(buf,0,sizeof(buf));
        (void) snprintf(buf,sizeof(buf)-1,"Subject: %s\r\n",subject);

        msock_puts(buf);

        showVerbose(buf);
    }

    /* headers */
    if (from)
    {
        memset(buf,0,sizeof(buf));
        if (*g_from_name != '\0')
        {
            /* Name in From: */

            memset(buf,0,sizeof(buf));
            (void) snprintf(buf,sizeof(buf)-1,"From: %s <%s>\r\n",
                            g_from_name,from);
        }
        else
        {
            (void) snprintf(buf,sizeof(buf)-1,"From: %s\r\n",from);
        }
        msock_puts(buf);

        showVerbose(buf);
    }

    if (add_dateh)
    {
        /* add Date: header */
        char
            datebuf[65];

        memset(datebuf,0,sizeof(datebuf));
        if (rfc822_date(time(NULL),datebuf,sizeof(datebuf)-1) == 0)
        {
            memset(buf,0,sizeof(buf));
            (void) snprintf(buf,sizeof(buf)-1,"Date: %s\r\n",datebuf);
            msock_puts(buf);

            showVerbose(buf);
        }
    }
    
    if (to)
    {
        memset(buf,0,sizeof(buf));
        (void) snprintf(buf,sizeof(buf)-1,"To: %s\r\n",to);
        msock_puts(buf);

        showVerbose(buf);

    }

    if (cc)
    {
        memset(buf,0,sizeof(buf));
        (void) snprintf(buf,sizeof(buf)-1,"Cc: %s\r\n",cc);
        msock_puts(buf);
        showVerbose(buf);
    }

    /*
    if (bcc)
    {
        memset(buf,0,sizeof(buf));
        (void) snprintf(buf,sizeof(buf)-1,"Bcc: %s\r\n",bcc);
        msock_puts(buf);

        showVerbose(buf);
    }
    */

    if (rt != NULL)
    {
        memset(buf,0,sizeof(buf));
        (void) snprintf(buf,sizeof(buf)-1,"Reply-To: %s\r\n",rt);
        msock_puts(buf);
        showVerbose(buf);

    }
    if (rrr != NULL)
    {
        memset(buf,0,sizeof(buf));
        (void) snprintf(buf,sizeof(buf)-1,"Disposition-Notification-To: %s\r\n",rrr);
        msock_puts(buf);
        showVerbose(buf);
    }

    /* add custom headers if any. No verification is done */
    {
        Sll 
            *l,
            *custom_header_list;
        custom_header_list = get_custom_header_list();
        if (custom_header_list)
        {
            for (l = custom_header_list; l; l = l->next)
            {
                if (l->data)
                {
                    msock_puts((char *) l->data);
                    msock_puts("\r\n");
                    showVerbose((char *) l->data);
                    showVerbose("\r\n");
                }
            }
        }
    }


    memset(buf,0,sizeof(buf));
    (void) snprintf(buf,sizeof(buf)-1,"X-Mailer: %s (%s)\r\n",MAILSEND_VERSION,os);
    msock_puts(buf);
    showVerbose(buf);

    memset(buf,0,sizeof(buf));
    (void) snprintf(buf,sizeof(buf)-1,"X-Copyright: %s\r\n",NO_SPAM_STATEMENT);
    msock_puts(buf);
    showVerbose(buf);

    if (is_mime)
    {
        int
            rc;
        srand(time(NULL));
        memset(boundary,0,sizeof(boundary));
        mutilsGenerateMIMEBoundary(boundary,sizeof(boundary));

        /* if msg body file is specified, include and return */
        if (msg_body_file)
        {
            return (include_msg_body());
        }

        rc = print_content_type_header(boundary);
        RETURN_IF_NOT_ZERO(rc);

        rc = process_oneline_messages(boundary);
        RETURN_IF_NOT_ZERO(rc);

        rc = process_embeded_images(boundary);
        RETURN_IF_NOT_ZERO(rc);

        rc = process_attachments(boundary);
        RETURN_IF_NOT_ZERO(rc);

        /*
        ** if there were other kind of MIME types but no attachments,
        ** we have to print the last boundary 
        */
        print_end_boundary(boundary);

        /* handle MIME attachments ends */
        goto done;
    } /* is_mime */

    /* mail body */
    if (attach_file == NULL && the_msg == NULL) /* read from stdin */
    {

        /* if stdin is a terminal, print the instruction */
        if (isInConsole(_fileno(stdin)))
        {
            (void) printf("=========================================================================\n");
            (void) printf("Type . in a new line and press Enter to end the message, CTRL+C to abort\n");
            (void) printf("=========================================================================\n");
        }

#ifdef WINNT
        SetConsoleCtrlHandler(CntrlHandler,TRUE);
#endif /* WINNT */

        newline_before=1;
        msock_puts("\r\n"); /* RFC822 sec 3.1 */
        showVerbose("\r\n");
        while (fgets(mbuf,sizeof(mbuf)-1,stdin) && (break_out == 0))
        {
            if (newline_before && *mbuf == '.')
            {
                break;
            }
            else
            {
                int
                    len;
                /* vinicio qmail fix */
                len=strlen(mbuf);
                if (mbuf[len-1] != '\n')
                    strcat(mbuf,"\r\n");
                else
                {
                   mbuf[--len]='\0';
                   strcat(mbuf,"\r\n");
                }
                /* vinicio qmail fix */
                msock_puts(mbuf);
                showVerbose("[C] %s",mbuf);
            }
            newline_before=(*mbuf != '\0' && mbuf[strlen(mbuf)-1] == '\n');
            if (break_out == 1)
            {
                (void) fprintf(stderr," Breaking out\n");
                return (0);
            }
        }
    }
done:

    return (0);
}