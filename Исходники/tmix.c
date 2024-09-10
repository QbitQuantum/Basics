int		GetScriptInfo(char *name)
{
    FILE		*fp;
    char		buffer[256];
    char		tempbuff[256];
    char		delims[] = {" \t,\n"};

    printf("Opening script file %s.\n", name);

    if (fp = fopen(name, "r"))
    {
        while(fgets(buffer, 256, fp))
        {
            if (strncmp(buffer, "//", 2) && strncmp(buffer, "\n", 1))
            {
                strupr(buffer);
                strcpy(tempbuff, buffer);
                if (strcmp(strtok(tempbuff, delims), "OUTPUT") == 0)
                {
                    strcpy(out.name, strtok(NULL, delims));
                    strlwr(out.name);
                }

                strcpy(tempbuff, buffer);
                if (strcmp(strtok(tempbuff, delims), "SOURCEDIR") == 0)
                {
                    strcpy(tempbuff, strtok(NULL, delims));
                    strcpy(sourcedir, ExpandPathAndArchive(tempbuff));
                }

                strcpy(tempbuff, buffer);
                if (strcmp(strtok(tempbuff, delims), "DOSORT") == 0)
                    dosort = 1;

                strcpy(tempbuff, buffer);
                if (strcmp(strtok(tempbuff, delims), "XCHARSIZE") == 0)
                    xcharsize = strtol(strtok(NULL, delims), NULL, 0);

                strcpy(tempbuff, buffer);
                if (strcmp(strtok(tempbuff, delims), "YCHARSIZE") == 0)
                    ycharsize = strtol(strtok(NULL, delims), NULL, 0);

                strcpy(tempbuff, buffer);
                if (strcmp(strtok(tempbuff, delims), "OUTSCRIPT") == 0)
                {
                    strcpy(outscript, strtok(NULL, delims));
                    strlwr(outscript);
                }

                strcpy(tempbuff, buffer);
                if (strcmp(strtok(tempbuff, delims), "OUTUSAGE") == 0)
                    strcpy(outusage, strtok(NULL, delims));

                strcpy(tempbuff, buffer);
                if (strcmp(strtok(tempbuff, delims), "POS") == 0)
                {
                    out.w = strtol(strtok(NULL, delims), NULL, 0);
                    out.h = strtol(strtok(NULL, delims), NULL, 0);
                }

                strcpy(tempbuff, buffer);
                if (strcmp(strtok(tempbuff, delims), "FILE") == 0)
                {
                    strcpy(in[filenum].name, strtok(NULL, delims));
                    in[filenum].x = strtol(strtok(NULL, delims), NULL, 0);
                    in[filenum].y = strtol(strtok(NULL, delims), NULL, 0);
                    in[filenum].col = strtol(strtok(NULL, delims), NULL, 0);
                    filenum++;
                }
            }
        }
        fclose(fp);
        return(true);
    }
    else
    {
        printf("ERROR : Could not open script file.\n");
        return(false);
    }
}