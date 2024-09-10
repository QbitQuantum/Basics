 Application(char* input,char* output)
 :cin(input),cout(output)
 {
                         cin>>H>>W;
                         memset(appear,false,sizeof(appear));
                         appearSet_len=0;
                         for (int i=1;i<=H;i++)
                             for (int j=1;j<=W;j++)
                             {
                                 cin>>pic[i][j];
                                 if (pic[i][j]!='.')
                                 {
                                    if (!appear[pic[i][j]])
                                       appearSet[++appearSet_len]=pic[i][j];
                                    appear[pic[i][j]]=true;
                                 }
                                 box[pic[i][j]].update(i,j);
                             }
                         /*
                         for (int i=1;i<=H;i++)
                         {
                             for (int j=1;j<=W;j++)
                                 cout<<pic[i][j];
                             cout<<endl;
                         }
                         for (char* i=SETLIST;*i;i++)
                         {
                             if (appear[*i])
                                cout<<*i<<":"<<box[*i].x1<<","<<box[*i].y1<<" "
                                             <<box[*i].x2<<","<<box[*i].y2<<endl;
                             //cout<<*i<<":"<<appear[*i]<<endl;
                         }
                         for (int i=1;i<=appearSet_len;i++)
                             cout<<appearSet[i]<<endl;
                         */
 }