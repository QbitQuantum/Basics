void LoadScriptFile(pzllst *lst,FManNode *filename, bool control, MList *controlst)
{
#ifdef TRACE
    printf("Loading script file %s\n",filename->File);
#endif

    if (control)
    {
        Rend_SetRenderer(RENDER_FLAT);
    }

    mfile *fl=mfopen(filename);
    if (fl == NULL)
    {
        printf("Error opening file %s\n",filename->File);
        exit(1);
        return;
    }

    char buf[FILE_LN_BUF];

    while(!mfeof(fl))
    {
        mfgets(buf,FILE_LN_BUF,fl);

        char *str=PrepareString(buf);


        if (strCMP(str,"puzzle")==0)
        {
            Parse_Puzzle(lst,fl,str);
        }
        else if (strCMP(str,"control")==0 && control )
        {
            Parse_Control(controlst,fl,str);
        }
    }

    mfclose(fl);
}