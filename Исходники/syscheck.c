/* DB_Search
 * Search the DB for any entry related to the file being received
 */
int DB_Search(char *f_name, char *c_sum, Eventinfo *lf)
{
    int p = 0;
    int sn_size;
    int agent_id;
    
    char *saved_sum;
    char *saved_name;
    
    FILE *fp;


    /* Getting db pointer */
    fp = DB_File(lf->location, &agent_id);
    if(!fp)
    {
        merror("%s: Error handling integrity database.",ARGV0);
        sdb.db_err++; /* Increment db error */
        return(0);
    }


    /* Reads the integrity file and search for a possible
     * entry
     */
    if(fgetpos(fp, &sdb.init_pos) == -1)
    {
        merror("%s: Error handling integrity database (fgetpos).",ARGV0);
        return(0);
    }
    
    
    /* Looping the file */
    while(fgets(sdb.buf, OS_MAXSTR, fp) != NULL)
    {
        /* Ignore blank lines and lines with a comment */
        if(sdb.buf[0] == '\n' || sdb.buf[0] == '#')
        {
            fgetpos(fp, &sdb.init_pos); /* getting next location */
            continue;
        }


        /* Getting name */    
        saved_name = strchr(sdb.buf, ' ');
        if(saved_name == NULL)
        {
            merror("%s: Invalid integrity message in the database.",ARGV0);
            fgetpos(fp, &sdb.init_pos); /* getting next location */
            continue;
        }
        *saved_name = '\0';
        saved_name++;
        
        
        /* New format - with a timestamp */
        if(*saved_name == '!')
        {
            saved_name = strchr(saved_name, ' ');
            if(saved_name == NULL)
            {
                merror("%s: Invalid integrity message in the database",ARGV0);
                fgetpos(fp, &sdb.init_pos); /* getting next location */
                continue;
            }
            saved_name++;
        }


        /* Removing new line from saved_name */
        sn_size = strlen(saved_name);
        sn_size -= 1;
        if(saved_name[sn_size] == '\n')
            saved_name[sn_size] = '\0';


        /* If name is different, go to next one. */
        if(strcmp(f_name,saved_name) != 0)
        {
            /* Saving currently location */
            fgetpos(fp, &sdb.init_pos);
            continue;
        }
        

        saved_sum = sdb.buf;


        /* First three bytes are for frequency check */
        saved_sum+=3;


        /* checksum match, we can just return and keep going */
        if(strcmp(saved_sum, c_sum) == 0)
            return(0);


        /* If we reached here, the checksum of the file has changed */
        if(saved_sum[-3] == '!')
        {
            p++;
            if(saved_sum[-2] == '!')
            {
                p++;
                if(saved_sum[-1] == '!')    
                    p++;
                else if(saved_sum[-1] == '?')
                    p+=2;    
            }
        }


        /* Checking the number of changes */
        if(!Config.syscheck_auto_ignore)
        {
            sdb.syscheck_dec->id = sdb.id1;
        }
        else
        {
            switch(p)
            {
                case 0:
                sdb.syscheck_dec->id = sdb.id1;
                break;

                case 1:
                sdb.syscheck_dec->id = sdb.id2;
                break;

                case 2:
                sdb.syscheck_dec->id = sdb.id3;
                break;

                default:
                return(0);
                break;
            }
        }


        /* Adding new checksum to the database */
        /* Commenting the file entry and adding a new one latter */
        fsetpos(fp, &sdb.init_pos);
        fputc('#',fp);


        /* Adding the new entry at the end of the file */
        fseek(fp, 0, SEEK_END);
        fprintf(fp,"%c%c%c%s !%d %s\n",
                '!',
                p >= 1? '!' : '+',
                p == 2? '!' : (p > 2)?'?':'+',
                c_sum,
                lf->time,
                f_name);
        fflush(fp);


        /* File deleted */
        if(c_sum[0] == '-' && c_sum[1] == '1')
        {
            sdb.syscheck_dec->id = sdb.idd;
            snprintf(sdb.comment, OS_MAXSTR,
                    "File '%.756s' was deleted. Unable to retrieve "
                    "checksum.", f_name);
        }
        
        /* If file was re-added, do not compare changes */
        else if(saved_sum[0] == '-' && saved_sum[1] == '1')
        {
            sdb.syscheck_dec->id = sdb.idn;
            snprintf(sdb.comment, OS_MAXSTR,
                     "File '%.756s' was re-added.", f_name);
        }

        else    
        {
            int oldperm = 0, newperm = 0;
            
            /* Providing more info about the file change */
            char *oldsize = NULL, *newsize = NULL;
            char *olduid = NULL, *newuid = NULL;
            char *c_oldperm = NULL, *c_newperm = NULL;
            char *oldgid = NULL, *newgid = NULL;
            char *oldmd5 = NULL, *newmd5 = NULL;
            char *oldsha1 = NULL, *newsha1 = NULL;

            oldsize = saved_sum;
            newsize = c_sum;

            c_oldperm = strchr(saved_sum, ':');
            c_newperm = strchr(c_sum, ':');

            /* Get old/new permissions */
            if(c_oldperm && c_newperm)
            {
                *c_oldperm = '\0';
                c_oldperm++;

                *c_newperm = '\0';
                c_newperm++;

                /* Get old/new uid/gid */
                olduid = strchr(c_oldperm, ':');
                newuid = strchr(c_newperm, ':');

                if(olduid && newuid)
                {
                    *olduid = '\0';
                    *newuid = '\0';

                    olduid++;
                    newuid++;

                    oldgid = strchr(olduid, ':');
                    newgid = strchr(newuid, ':');

                    if(oldgid && newgid)
                    {
                        *oldgid = '\0';
                        *newgid = '\0';

                        oldgid++;
                        newgid++;


                        /* Getting md5 */
                        oldmd5 = strchr(oldgid, ':');
                        newmd5 = strchr(newgid, ':');

                        if(oldmd5 && newmd5)
                        {
                            *oldmd5 = '\0';
                            *newmd5 = '\0';

                            oldmd5++;
                            newmd5++;

                            /* getting sha1 */
                            oldsha1 = strchr(oldmd5, ':');
                            newsha1 = strchr(newmd5, ':');

                            if(oldsha1 && newsha1)
                            {
                                *oldsha1 = '\0';
                                *newsha1 = '\0';

                                oldsha1++;
                                newsha1++;
                            }
                        }
                    }
                }
            }

            /* Getting integer values */
            if(c_newperm && c_oldperm)
            {
                newperm = atoi(c_newperm);
                oldperm = atoi(c_oldperm);
            }

            /* Generating size message */
            if(!oldsize || !newsize || strcmp(oldsize, newsize) == 0)
            {
                sdb.size[0] = '\0';
            }
            else
            {
                snprintf(sdb.size, OS_FLSIZE,
                        "Size changed from '%s' to '%s'\n",
                        oldsize, newsize);

                #ifdef PRELUDE
                os_strdup(oldsize, lf->size_before);
                os_strdup(newsize, lf->size_after);
                #endif
            }

            /* Permission message */
            if(oldperm == newperm)
            {
                sdb.perm[0] = '\0';
            }
            else if(oldperm > 0 && newperm > 0)
            {

                snprintf(sdb.perm, OS_FLSIZE, "Permissions changed from "
                        "'%c%c%c%c%c%c%c%c%c' "
                        "to '%c%c%c%c%c%c%c%c%c'\n",
                        (oldperm & S_IRUSR)? 'r' : '-',
                        (oldperm & S_IWUSR)? 'w' : '-',
                        
                        (oldperm & S_ISUID)? 's' :
                        (oldperm & S_IXUSR)? 'x' : '-',
                        
                        (oldperm & S_IRGRP)? 'r' : '-',
                        (oldperm & S_IWGRP)? 'w' : '-',

                        (oldperm & S_ISGID)? 's' :
                        (oldperm & S_IXGRP)? 'x' : '-',
                        
                        (oldperm & S_IROTH)? 'r' : '-',
                        (oldperm & S_IWOTH)? 'w' : '-',

                        (oldperm & S_ISVTX)? 't' :
                        (oldperm & S_IXOTH)? 'x' : '-',



                        (newperm & S_IRUSR)? 'r' : '-',
                        (newperm & S_IWUSR)? 'w' : '-',

                        (newperm & S_ISUID)? 's' :
                        (newperm & S_IXUSR)? 'x' : '-',

                        
                        (newperm & S_IRGRP)? 'r' : '-',
                        (newperm & S_IWGRP)? 'w' : '-',
                        
                        (newperm & S_ISGID)? 's' :
                        (newperm & S_IXGRP)? 'x' : '-',

                        (newperm & S_IROTH)? 'r' : '-',
                        (newperm & S_IWOTH)? 'w' : '-',

                        (newperm & S_ISVTX)? 't' :
                        (newperm & S_IXOTH)? 'x' : '-');

                #ifdef PRELUDE
                lf->perm_before = oldperm;
                lf->perm_after = newperm;
                #endif
            }

            /* Ownership message */
            if(!newuid || !olduid || strcmp(newuid, olduid) == 0)
            {
                sdb.owner[0] = '\0';
            }
            else
            {
                snprintf(sdb.owner, OS_FLSIZE, "Ownership was '%s', "
                        "now it is '%s'\n",
                        olduid, newuid);


                #ifdef PRELUDE
                os_strdup(olduid, lf->owner_before);
                os_strdup(newuid, lf->owner_after);
                #endif
            }    

            /* group ownership message */
            if(!newgid || !oldgid || strcmp(newgid, oldgid) == 0)
            {
                sdb.gowner[0] = '\0';
            }
            else
            {
                snprintf(sdb.gowner, OS_FLSIZE,"Group ownership was '%s', "
                        "now it is '%s'\n",
                        oldgid, newgid);
                #ifdef PRELUDE
                os_strdup(oldgid, lf->gowner_before);
                os_strdup(newgid, lf->gowner_after);
                #endif
            }

            /* md5 message */
            if(!newmd5 || !oldmd5 || strcmp(newmd5, oldmd5) == 0)
            {
                sdb.md5[0] = '\0';
            }
            else
            {
                snprintf(sdb.md5, OS_FLSIZE, "Old md5sum was: '%s'\n"
                        "New md5sum is : '%s'\n",
                        oldmd5, newmd5);
                #ifdef PRELUDE
                os_strdup(oldmd5, lf->md5_before);
                os_strdup(newmd5, lf->md5_after);
                #endif
            }

            /* sha1 */
            if(!newsha1 || !oldsha1 || strcmp(newsha1, oldsha1) == 0)
            {
                sdb.sha1[0] = '\0';
            }
            else
            {
                snprintf(sdb.sha1, OS_FLSIZE, "Old sha1sum was: '%s'\n"
                        "New sha1sum is : '%s'\n",
                        oldsha1, newsha1);
                #ifdef PRELUDE
                os_strdup(oldsha1, lf->sha1_before);
                os_strdup(newsha1, lf->sha1_after);
                #endif
            }
            #ifdef PRELUDE
            os_strdup(f_name, lf->filename);
            #endif


if(lf->data)
{
    merror("XXX changed: %s",lf->data);
}
            /* Provide information about the file */    
            snprintf(sdb.comment, OS_MAXSTR, "Integrity checksum changed for: "
                    "'%.756s'\n"
                    "%s"
                    "%s"
                    "%s"
                    "%s"
                    "%s"
                    "%s"
                    "%s%s",
                    f_name, 
                    sdb.size,
                    sdb.perm,
                    sdb.owner,
                    sdb.gowner,
                    sdb.md5,
                    sdb.sha1,
                    lf->data == NULL?"":"What changed:\n",
                    lf->data == NULL?"":lf->data
                    );
        }


        /* Creating a new log message */
        free(lf->full_log);
        os_strdup(sdb.comment, lf->full_log);
        lf->log = lf->full_log;
        lf->data = NULL;

        
        /* Setting decoder */
        lf->decoder_info = sdb.syscheck_dec;
                        

        return(1); 

    } /* continuiing... */


    /* If we reach here, this file is not present on our database */
    fseek(fp, 0, SEEK_END);
    
    fprintf(fp,"+++%s !%d %s\n", c_sum, lf->time, f_name);


    /* Alert if configured to notify on new files */
    if((Config.syscheck_alert_new == 1) && (DB_IsCompleted(agent_id)))
    {
        sdb.syscheck_dec->id = sdb.idn;

        /* New file message */
        snprintf(sdb.comment, OS_MAXSTR,
                              "New file '%.756s' "
                              "added to the file system.", f_name);
        

        /* Creating a new log message */
        free(lf->full_log);
        os_strdup(sdb.comment, lf->full_log);
        lf->log = lf->full_log;


        /* Setting decoder */
        lf->decoder_info = sdb.syscheck_dec;

        return(1);
    }

    return(0);
}