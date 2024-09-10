/** alert_data *GetAlertData(FILE *fp)
 * Returns alert data for the file specified
 */
alert_data *GetAlertData(int flag, FILE *fp)
{
    int _r = 0, issyscheck = 0;
    size_t log_size = 0;
    char *p;

    char *alertid = NULL;
    char *date = NULL;
    char *comment = NULL;
    char *location = NULL;
    char *srcip = NULL;
    char *dstip = NULL;
    char *user = NULL;
    char *group = NULL;
    char *filename = NULL;
    char *old_md5 = NULL;
    char *new_md5 = NULL;
    char *old_sha1 = NULL;
    char *new_sha1 = NULL;
    char **log = NULL;
#ifdef LIBGEOIP_ENABLED
    char *geoipdatasrc = NULL;
    char *geoipdatadst = NULL;
#endif
    int level = 0, rule = 0, srcport = 0, dstport = 0;


    char str[OS_BUFFER_SIZE+1];
    str[OS_BUFFER_SIZE]='\0';


    while(fgets(str, OS_BUFFER_SIZE, fp) != NULL)
    {

        /* Enf of alert */
        if(strcmp(str, "\n") == 0 && log_size > 0)
        {
            /* Found in here */
            if(_r == 2)
            {
                alert_data *al_data;
                os_calloc(1, sizeof(alert_data), al_data);
                al_data->alertid = alertid;
                al_data->level = level;
                al_data->rule = rule;
                al_data->location = location;
                al_data->comment = comment;
                al_data->group = group;
                al_data->log = log;
                al_data->srcip = srcip;
                al_data->srcport = srcport;
                al_data->dstip = dstip;
                al_data->dstport = dstport;
                al_data->user = user;
                al_data->date = date;
                al_data->filename = filename;
#ifdef LIBGEOIP_ENABLED
                al_data->geoipdatasrc = geoipdatasrc;
                al_data->geoipdatadst = geoipdatadst;
#endif
                al_data->old_md5 = old_md5;
                al_data->new_md5 = new_md5;
                al_data->old_sha1 = old_sha1;
                al_data->new_sha1 = new_sha1;


                return(al_data);
            }
            _r = 0;
        }


        /* Checking for the header */
        if(strncmp(ALERT_BEGIN, str, ALERT_BEGIN_SZ) == 0)
        {
            char *m;
            size_t z = 0;
            p = str + ALERT_BEGIN_SZ + 1;

            m = strstr(p, ":");
            if (!m)
            {
                continue;
            }

            z = strlen(p) - strlen(m);
            os_realloc(alertid, (z + 1)*sizeof(char), alertid);
            strncpy(alertid, p, z);
            alertid[z] = '\0';

            /* Searching for email flag */
            p = strchr(p, ' ');
            if(!p)
            {
                continue;
            }

            p++;


            /* Checking for the flags */
            if((flag & CRALERT_MAIL_SET) &&
               (strncmp(ALERT_MAIL, p, ALERT_MAIL_SZ) != 0))
            {
                continue;
            }

            p = strchr(p, '-');
            if(p)
            {
                p++;
                free(group);
                os_strdup(p, group);

                /* Cleaning new line from group */
                os_clearnl(group, p);
                if(group != NULL && strstr(group, "syscheck") != NULL)
                {
                    issyscheck = 1;
                }
            }


            /* Searching for active-response flag */
            _r = 1;
            continue;
        }

        if(_r < 1)
            continue;


        /*** Extract information from the event ***/

        /* r1 means: 2006 Apr 13 16:15:17 /var/log/auth.log */
        if(_r == 1)
        {
            /* Clear new line */
            os_clearnl(str, p);

            p = strchr(str, ':');
            if(p)
            {
                p = strchr(p, ' ');
                if(p)
                {
                    *p = '\0';
                    p++;
                }
                else
                {
                    /* If p is null it is because strchr failed */
                    merror("ZZZ: 1() Merror date or location not NULL");
                    goto l_error;
                }
            }


            /* If not, str is date and p is the location */
            if(date || location || !p)
            {
                merror("ZZZ Merror date or location not NULL or p is NULL");
                goto l_error;
            }

            os_strdup(str, date);
            os_strdup(p, location);
            _r = 2;
            log_size = 0;
            continue;
        }


        else if(_r == 2)
        {
            /* Rule begin */
            if(strncmp(RULE_BEGIN, str, RULE_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + RULE_BEGIN_SZ;
                rule = atoi(p);

                p = strchr(p, ' ');
                if(p)
                {
                    p++;
                    p = strchr(p, ' ');
                    if(p)
                        p++;
                }

                if(!p)
                    goto l_error;

                level = atoi(p);

                /* Getting the comment */
                p = strchr(p, '\'');
                if(!p)
                    goto l_error;

                p++;
                os_strdup(p, comment);

                /* Must have the closing \' */
                p = strrchr(comment, '\'');
                if(p)
                {
                    *p = '\0';
                }
                else
                {
                    goto l_error;
                }
            }

            /* srcip */
            else if(strncmp(SRCIP_BEGIN, str, SRCIP_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + SRCIP_BEGIN_SZ;
                os_strdup(p, srcip);
            }
#ifdef LIBGEOIP_ENABLED
            /* GeoIP Source Location */
            else if (strncmp(GEOIP_BEGIN_SRC, str, GEOIP_BEGIN_SRC_SZ) == 0)
            {
                os_clearnl(str,p);
                p = str + GEOIP_BEGIN_SRC_SZ;
                os_strdup(p, geoipdatasrc);
            }
#endif
            /* srcport */
            else if(strncmp(SRCPORT_BEGIN, str, SRCPORT_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + SRCPORT_BEGIN_SZ;
                srcport = atoi(p);
            }
            /* dstip */
            else if(strncmp(DSTIP_BEGIN, str, DSTIP_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + DSTIP_BEGIN_SZ;
                os_strdup(p, dstip);
            }
#ifdef LIBGEOIP_ENABLED
            /* GeoIP Destination Location */
            else if (strncmp(GEOIP_BEGIN_DST, str, GEOIP_BEGIN_DST_SZ) == 0)
            {
		os_clearnl(str,p);
		p = str + GEOIP_BEGIN_DST_SZ;
		os_strdup(p, geoipdatadst);
            }
#endif
            /* dstport */
            else if(strncmp(DSTPORT_BEGIN, str, DSTPORT_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + DSTPORT_BEGIN_SZ;
                dstport = atoi(p);
            }
            /* username */
            else if(strncmp(USER_BEGIN, str, USER_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + USER_BEGIN_SZ;
                os_strdup(p, user);
            }
            /* Old MD5 */
            else if(strncmp(OLDMD5_BEGIN, str, OLDMD5_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + OLDMD5_BEGIN_SZ;
                os_strdup(p, old_md5);
            }
            /* New MD5 */
            else if(strncmp(NEWMD5_BEGIN, str, NEWMD5_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + NEWMD5_BEGIN_SZ;
                os_strdup(p, new_md5);
            }
            /* Old SHA1 */
            else if(strncmp(OLDSHA1_BEGIN, str, OLDSHA1_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + OLDSHA1_BEGIN_SZ;
                os_strdup(p, old_sha1);
            }
            /* New SHA1 */
            else if(strncmp(NEWSHA1_BEGIN, str, NEWSHA1_BEGIN_SZ) == 0)
            {
                os_clearnl(str,p);

                p = str + NEWSHA1_BEGIN_SZ;
                os_strdup(p, new_sha1);
            }
            /* It is a log message */
            else if(log_size < 20)
            {
                os_clearnl(str,p);

                if(issyscheck == 1)
                {
                    if(strncmp(str, "Integrity checksum changed for: '",33) == 0)
                    {
                        filename = strdup(str+33);
                        if(filename)
                        {
                            filename[strlen(filename) -1] = '\0';
                        }
                    }
                    issyscheck = 0;
                }

                os_realloc(log, (log_size +2)*sizeof(char *), log);
                os_strdup(str, log[log_size]);
                log_size++;
                log[log_size] = NULL;
            }
        }

        continue;
        l_error:

        /* Freeing the memory */
        _r = 0;
        if(date)
        {
            free(date);
            date = NULL;
        }
        if(location)
        {
            free(location);
            location = NULL;
        }
        if(comment)
        {
            free(comment);
            comment = NULL;
        }
        if(srcip)
        {
            free(srcip);
            srcip = NULL;
        }
#ifdef LIBGEOIP_ENABLED
        if(geoipdatasrc)
        {
            free(geoipdatasrc);
            geoipdatasrc = NULL;
        }
        if(geoipdatadst)
        {
            free(geoipdatadst);
            geoipdatadst = NULL;
        }
#endif
        if(user)
        {
            free(user);
            user = NULL;
        }
        if(filename)
        {
            free(filename);
            filename = NULL;
        }
        if(group)
        {
            free(group);
            group = NULL;
        }
        if(old_md5)
        {
            free(old_md5);
            old_md5 = NULL;
        }

        if(new_md5)
        {
            free(new_md5);
            new_md5 = NULL;
        }

        if(old_sha1)
        {
            free(old_sha1);
            old_sha1 = NULL;
        }

        if(new_sha1)
        {
            free(new_sha1);
            new_sha1 = NULL;
        }
        while(log_size > 0)
        {
            log_size--;
            if(log[log_size])
            {
                free(log[log_size]);
                log[log_size] = NULL;
            }
        }
    }

    if(alertid)
	{
		free(alertid);
		alertid = NULL;
	}
    if(group)
    {
        free(group);
        group = NULL;
    }
    if(location)
    {
        free(location);
        location = NULL;
    }
    if(date)
    {
        free(date);
        date = NULL;
    }

    while(log_size > 0)
    {
        log_size--;
        if(log[log_size])
        {
            free(log[log_size]);
            log[log_size] = NULL;
        }
    }
    free(log);

    free(comment);

    free(srcip);

    free(dstip);

    free(user);

    free(old_md5);

    free(new_md5);

    free(old_sha1);

    free(new_sha1);

    free(filename);

    /* We need to clean end of file before returning */
    clearerr(fp);
    return(NULL);
}