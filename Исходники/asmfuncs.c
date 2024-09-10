/*---------------------------------------------------------------------------
|  update_sample_info()/5
|
|  update_sample_info - 
|	Takes a automation directory and filename of sample_info structure (e.g., doneQ,enterq,sampleinfo)
|	Searches through the file for a match between the match_target value
|	  and the match_value;
|       Upon finding the match it then updates the update_target with the
|	  update_value;
|       For example: You want to update the doneQ  'STATUS' entry to Complete,
|		     for the experiment inwhich the DATA entry matches with
|		     '/vnmr/auto/greg.1201' (i.e. DATA is a unique identifier).
|       The call would be:
|	  update_sample_info("systemdir/auto","doneQ",
|			     "DATA:","/vnmr/auto/greg.1201",
|			     "STATUS","Complete");
|
|				Author:  Greg Brissey 1/28/88
+--------------------------------------------------------------------------*/
int update_sample_info(char *autodir, char *filename, char *match_target,
                       char *match_value, char *update_target, char *update_value)
{
    FILE *update_file,*tmp_file;
    char filepath[128],value[MAX_TEXT_LEN];
    struct sample_info	sample_entry;
    int stat,entryline,foundit;
    
    strncpy(filepath,autodir,110);
    strcat(filepath,"/");
    strcat(filepath,filename);

    /* if autoinfo mapping file hase not be read do so now */
    if (infomap.mapped != 1)		/* true if autoinfo has been read for mapping */
    {
	read_info_file(autodir);
    }


    if (lockfile(filepath) == ERROR) /* lock file for excusive use */
    {
        fprintf(stderr,"update_sample_info: could not lock '%s' file.\n",filepath);
    }
 
    update_file = fopen(filepath,"r");
    if (update_file == NULL)  /* does file exist? */
    {
        unlockfile(filepath);   /* unlock file */
        fprintf(stderr,"update_sample_info: '%s' file is not present for reading.\n",
			filepath);
        return(ERROR);
    }

    tmp_file = fopen("/tmp/update_sample_info.tmp","w");
    if (tmp_file == NULL)  /* does file exist? */
    {
        unlockfile(filepath);   /* unlock file */
        fclose(update_file);
        fprintf(stderr,
	    "update_sample_info: temp file '/tmp/update_sample_info.tmp' could not be created.\n");
        return(ERROR);
    }
 
    /* read through the the file writing to a tmp file as changes are made */
    foundit = 0;
    while ( (stat = read_sample_info(update_file,&sample_entry)) != ENDOFFILE)
    {
	if (stat == ERROR)
	{
           unlockfile(filepath);   /* unlock file */
    	   fclose(update_file);
    	   fclose(tmp_file);
           fprintf(stderr,
	    "update_sample_info: read error on file '%s'.\n",filepath);
           return(ERROR);
	}

        /* Once found and changed we can skip all this */
        if (!foundit)
        {
	  get_sample_info(&sample_entry,match_target,value,MAX_TEXT_LEN,&entryline);
          if (strncmp(value,match_value,MAX_TEXT_LEN) == 0)
          {
	     get_sample_info(&sample_entry,update_target,value,MAX_TEXT_LEN,&entryline);

	     /* If updating STATUS and STATUS: Shimming, then remove this entry */
             if ( (strcmp(infomap.status,update_target) == 0) && 
	          ( (strcmp(update_value,"Complete") == 0) || (strcmp(update_value,"Error") == 0)) &&
		  (strcmp(sample_entry.prompt_entry[entryline].etext,"Shimming") == 0) )
             {
		/* elimenate Shimming Experiment from doneQ */
	        foundit = 1;
		continue;	/* don't update, don't write it out */
             }

	     strncpy(sample_entry.prompt_entry[entryline].etext,update_value,MAX_TEXT_LEN);
	     sample_entry.prompt_entry[entryline].etext[MAX_TEXT_LEN-1] = '\0';
	     foundit = 1;
          }
        }

	if (write_sample_info(tmp_file,&sample_entry) == ERROR)
	{
           unlockfile(filepath);   /* unlock file */
    	   fclose(update_file);
    	   fclose(tmp_file);
           fprintf(stderr,
	    "update_sample_info: write error to temp file '/tmp/update_sample_info.tmp'.\n");
           return(ERROR);
	}
    }

    fclose(update_file);
    fclose(tmp_file);

    /* Changes are complete in the tmp file, now copy the tmp file into the orginal file */
    tmp_file = fopen("/tmp/update_sample_info.tmp","r");
    if (tmp_file == NULL)  /* does file exist? */
    {
        unlockfile(filepath);   /* unlock file */
        fprintf(stderr,
          "update_sample_info: temp file '/tmp/update_sample_info.tmp' could not be opened to be read.\n");
        return(ERROR);
    }

    update_file = fopen(filepath,"w");
    if (update_file == NULL)  /* does file exist? */
    {
        unlockfile(filepath);   /* unlock file */
        fclose(tmp_file);
        fprintf(stderr,"update_sample_info: '%s' file is not present for writing.\n",
			filepath);
        return(ERROR);
    }

    while ( ( stat = read_sample_info(tmp_file,&sample_entry)) != ENDOFFILE)
    {
	if (stat == ERROR)
	{
           unlockfile(filepath);   /* unlock file */
    	   fclose(update_file);
    	   fclose(tmp_file);
           fprintf(stderr,
	    "update_sample_info: read error on file '/tmp/update_sample_info.tmp'.\n");
           return(ERROR);
	}
	if (write_sample_info(update_file,&sample_entry) == ERROR)
	{
           unlockfile(filepath);   /* unlock file */
    	   fclose(update_file);
    	   fclose(tmp_file);
           fprintf(stderr,
	    "update_sample_info: write error to file '%s'.\n",filepath);
           return(ERROR);
	}
    }

    fclose(update_file);
    fclose(tmp_file);

    unlockfile(filepath);   /* unlock file */
    return(OK); 
}