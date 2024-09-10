int main()
{
    char word[20];
    int i,k,nowlen;
    freopen("poj1035.txt","r",stdin);
    freopen("poj1035ans.txt","w",stdout);

    InitHash();

    n=0;
    while (scanf("%s",word) && word[0]!='#')
    {
        strcpy(dict[n].word,word);
        dict[n].id=n;
        dict[n].len=strlen(word);
        dict[n].weight=dict[n].len*100000+n;
        n++;
        Find(word,INSERT);
    }

    QSort(0,n-1);

    nowlen=0;
    memset(startpos,-1,sizeof(startpos));
    for (i=0;i<n;i++)
    {
        if (dict[i].len==nowlen) continue;
        else
        {
            nowlen=dict[i].len;
            startpos[nowlen]=i;
        }
    }
    
    while (scanf("%s",word) && word[0]!='#')
    {
        nowlen=strlen(word);
        cnt=0;
        if (Find(word,QUERY)!=-1) printf("%s is correct\n",word);
        else
        {
            printf("%s:",word);
            CheckLen(word,nowlen);
            if (nowlen==1) CheckLen(word,2);
            else if (nowlen==15) CheckLen(word,14);
            else
            {
                CheckLen(word,nowlen-1);
                CheckLen(word,nowlen+1);
            }
            QSort2(0,cnt-1);
            for (i=0;i<cnt;i++) printf(" %s",ans[i].word);
            printf("\n");
        }
    }
    
    return 0;
}