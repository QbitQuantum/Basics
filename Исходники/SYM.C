void sym_patchnames(void)
{
    int i,j;
    char *p;

    for(j=0; ospatch[j]; j++)
    {
        p=strchr(ospatch[j],' ');
        if(!p)
        {
            print("ERROR in ospatch.h (%s)\n",ospatch[j]);
            return;
        }
        else
        {
            if(p[-1]=='*')
            {
                ospatchwild[j]=1;
                ospatchlen[j]=p-ospatch[j]-1;
            }
            else
            {
                ospatchwild[j]=0;
                ospatchlen[j]=p-ospatch[j];
            }
        }
    }

    for(i=0; i<symnum; i++)
    {
        p=strchr(sym[i].text,'%');
        if(p) continue; // patch disabled
        p=strchr(sym[i].text,'#');
        if(!p)
        {   // no patch yet, add one from ospatch[] if applicable
            for(j=0; ospatch[j]; j++)
            {
                if(strlen(sym[i].text)<ospatchlen[j]) continue;
                if(memicmp(sym[i].text,ospatch[j],ospatchlen[j])) continue;
                if(!ospatchwild[j] && sym[i].text[ospatchlen[j]]>32) continue;
                // match
                {
                    char buf[256];
//                    print("- symbol patch %s [%s,%i] => ",sym[i].text,ospatch[j],ospatchlen[j]);
                    sprintf(buf,"%s %s",sym[i].text,ospatch[j]+ospatchlen[j]+1);
                    p=strchr(ospatch[j],'#');
                    if(!p) p="0";
                    sym_add(sym[i].addr,buf,atoi(p+1));
//                    print("%s\n",sym[i].text);
                }
                break;
            }
        }
    }
}