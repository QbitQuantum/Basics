PRC_REC *fetch_prc_rec(char *file, int recnum)
{
    FILE *fp;
    char buf[131];
    PRC_REC *tmp;
    int offset, i;
    char tmpbuf[20][20];

    /* Add null strings to end of temporary buffer */
    for (i=0; i< 20; i++) tmpbuf[i][19]='\0';

    /* Create structure & Add null characters to string fields */
    tmp = (PRC_REC *) MALLOC (sizeof(PRC_REC));
    tmp->reckey[6]='\0';
    tmp->spare[2]='\0';

    /* Open file, skip id and header, seek to recnum record */
    fp = FOPEN(file,"r");
    offset = 130 + 130 + 130 * recnum;
    if (fseek(fp,offset,0)!=0)
        asfPrintError("No state vector found - read past end of file \n");

    /* Read the current record */
    FREAD(buf,130,1,fp);

    FCLOSE(fp);

    /* Convert the buffer */
    sscanf(buf,"%6c%7c%c%6c%11c%12c%12c%12c%11c%11c%11c%6c%6c%6c%2c%3c%c%4c%2c",
           tmp->reckey, tmpbuf[0], &tmp->orbtyp, tmpbuf[1],tmpbuf[2],
           tmpbuf[3], tmpbuf[4], tmpbuf[5], tmpbuf[6], tmpbuf[7], tmpbuf[8],
           tmpbuf[9], tmpbuf[10], tmpbuf[11], tmpbuf[12], tmpbuf[13],
           &tmp->quali, tmpbuf[14], tmp->spare);

    /* Convert tmpbuf strings into numeric values */
    tmp->satid  = atoi(tmpbuf[0]);
    tmp->ttagd  = atof(tmpbuf[1]) / 10.0;   /* Units are 0.1 days */
    tmp->ttagms = strtoll(tmpbuf[2], (char **)NULL, 10);
    tmp->xsat   = strtoll(tmpbuf[3], (char **)NULL, 10);
    tmp->ysat   = strtoll(tmpbuf[4], (char **)NULL, 10);
    tmp->zsat   = strtoll(tmpbuf[5], (char **)NULL, 10);
    tmp->xdsat  = strtoll(tmpbuf[6], (char **)NULL, 10);
    tmp->ydsat  = strtoll(tmpbuf[7], (char **)NULL, 10);
    tmp->zdsat  = strtoll(tmpbuf[8], (char **)NULL, 10);
    tmp->roll   = atof(tmpbuf[9])/1000.0;   /* Units are 0.001 degrees */
    tmp->pitch  = atof(tmpbuf[10])/1000.0;  /* Units are 0.001 degrees */
    tmp->yaw    = atof(tmpbuf[11])/1000.0;  /* Units are 0.001 degrees */
    tmp->ascarc = atoi(tmpbuf[12]);
    tmp->check  = atoi(tmpbuf[13]);
    tmp->radcor = atoi(tmpbuf[14]);

    return(tmp);
}