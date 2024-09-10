static void TalkPoll()
{
    if(!rainin)
    {
        rainin=_fsopen(raincmdname,"rt",SH_DENYNO);
        if(rainin) setbuf(rainin,NULL);
    }
    if(rainin)
    {
        ParseString("0"); //just 50 or more Hz polling with no command
        a:
        fgets(input+inputlen,MAX_LINE_LENGTH-inputlen,rainin);
        inputlen+=strlen(input+inputlen);
        if ((inputlen && input[inputlen-1]=='\n') || inputlen>=MAX_LINE_LENGTH-1)
        {
            ParseString(input); //parse real command
            inputlen=0;
            input[0]=0;
            goto a;  //parse all commands until end of file
        }
    }
    {
        char *err;
        while (err=errGet())
        {
            fprintf(rainout,"%s\n",err);
            free(err);
        }
    }
}