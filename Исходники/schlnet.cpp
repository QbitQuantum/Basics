 Application(char* input,char* output)
                   :cin(input),cout(output)
 {
                   memset(m,false,sizeof(m));
                   cin>>N;
                   for (int i=1;i<=N;i++)
                   {
                       int t;
                       for (;;)
                       {
                           cin>>t;
                           if (t) m[i][t]=true;
                           else break;
                       }
                   }
 }