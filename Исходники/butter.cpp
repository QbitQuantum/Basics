 Application() :cin("butter.in"),cout("butter.out"),answer(oo)   
 {
               cin>>N>>P>>C;
               
               cow=new int[N+2];
               map=new int*[P+2];
               for (int i=1;i<=P;i++)
                   map[i]=new int[P+2];
               link=new List*[P+2];
               dist=new int[P+2];
               visited=new bool[P+2];
               q=new int[P+2];
               memset(link,0,sizeof(List*)*(P+2));
               
               for (int i=1;i<=N;i++)
                   cin>>cow[i];
               for (int i=1;i<=C;i++)
               {
                   int a,b,c;
                   cin>>a>>b>>c;
                   map[a][b]=c;
                   map[b][a]=c;
                   
                   if (link[a]==0)
                   {
                      link[a]=new List(b);
                   }
                   else
                   {
                       List* j;
                       for (j=link[a];j->next!=0;j=j->next) ;//do nothing
                       j->insert(b);
                   }
                   
                   if (link[b]==0)
                   {
                      link[b]=new List(a);
                   }
                   else
                   {
                       List* j;
                       for (j=link[b];j->next!=0;j=j->next) ;//do nothing
                       j->insert(a);
                   }
               }
 }