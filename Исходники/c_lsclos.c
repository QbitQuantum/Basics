lasErr FUNCTION c_lsclos (FILE **fd, const char *hostname, int *action)
{
FILE *fdtemp;
int	clen, dlen, total_len, empty,  more, nbytes;
int	buf_size = 1024;
char	tempfile[CMLEN];
char	*buffer;
char    dtype[TYPL];
char	header[HDRL];
char	*key=NULL;
char	msgtxt[ERRLEN + 1];
char	*ptr;

switch (*action)
    {
    case 0:					/***  normal close    ***/
	FCLOSE(*fd);
	break;

    case 1:					/***  crunch file     ***/
	FSEEK64(*fd, 0, 0);

	strcpy(tempfile,hostname);
	strcat(tempfile,"_temp");

	fdtemp = FOPEN (tempfile, "w");

	buffer = MALLOC((unsigned)buf_size);

	empty = 1;
	more = 1;
	while (more)
	    {
 	    nbytes = fread(header,sizeof(char),HDRL,*fd);
	    if (nbytes == 0)
	       break;

	    if (nbytes == -1)
	       {
	       c_errmsg("Error reading header record from label services file",
                         "lsclos-read",NON_FATAL);
	       return(E_FAIL);
	       }

	    clen = dlen = 0;
            if (((ptr = strchr(header,'/')) != NULL ) && ((int)(ptr - header) < LENL))
                sscanf(header,"%d/%d%s",&clen,&dlen,dtype); 
            else
                sscanf(header,"%d%s",&dlen,dtype); 

            key = squeeze(header+LENL+TYPL,strlen(header+LENL+TYPL));
	    total_len = clen + dlen;

	    if (strcmp(key,"DELETED") != 0)		/* copy record	*/
		{					/* to new file	*/
		if (total_len > buf_size)
		    {
		    free(buffer);
		    buf_size = total_len;

		    buffer = MALLOC((unsigned)buf_size);
		    }

		FREAD(buffer,1,total_len,*fd);

		FWRITE(header,1,HDRL,fdtemp);
		FWRITE(buffer,1,nbytes,fdtemp);

		empty = 0;
		}
	    else					/* skip record	*/ 
		{
		if (fseek(*fd, (int)total_len, 1) == -1)
		    {
		    c_errmsg("Error seeking in label services file",
			     "lsclos-seek",NON_FATAL);
		    return(E_FAIL);
		    }
		}
	    }

        free(buffer);

	if (fclose(*fd) != 0)
	    {
	    c_errmsg("Error closing label services file","lsclos-close",
			NON_FATAL);
	    return(E_FAIL);
	    }

	if (fclose(fdtemp) != 0)
	    {
	    sprintf(msgtxt,"Error closing temporary file %s",tempfile);
	    c_errmsg(msgtxt,"lsclos-close",NON_FATAL);
	    return(E_FAIL);
	    }

	 if (unlink(hostname) == -1)
	     {
	     sprintf(msgtxt,"Error deleting label services file %s",
		     hostname);
	     c_errmsg(msgtxt,"lsclos-delete",NON_FATAL);
	     return(E_FAIL);
	     }

	if (!empty)					/***  delete file   ***/
	   {
	   if (rename(tempfile,hostname) != E_SUCC)
	       {
	       sprintf(msgtxt,"Error renaming file %s to %s",
		        tempfile,hostname);
	       c_errmsg(msgtxt,"lsclos-rename",NON_FATAL);
	       return(E_FAIL);
	       }
           }
	else
	   if (unlink(tempfile) == -1)
	      {
	      sprintf(msgtxt,"Error deleting label services file %s",
		     hostname);
	      c_errmsg(msgtxt,"lsclos-delete",NON_FATAL);
	      return(E_FAIL);
	      }

	free(key);
	break;

    case 2:					/***  delete file     ***/
	if (unlink(hostname) == -1)
	    {
	    sprintf(msgtxt,"Error deleting label services file %s",
		    hostname);
	    c_errmsg(msgtxt,"lsclos-delete",NON_FATAL);
	    return(E_FAIL);
	    }
	break;
    }

return(E_SUCC);
}