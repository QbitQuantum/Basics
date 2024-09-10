void mno_alph::encrypt()
{
   strcpy(strtext,"   ");
  strcpy(strcode,"    ");
  len=0;
  cout<<"enter key "<<endl;
  for(i=0;i<=25;++i)
  {
   lettertext[i]=toascii(i+97);
   cout<<"enter key for "<<lettertext[i];
   cin>>key[i];

  }
 cout<<"Enter text   "<<endl;
 cin>>strtext;
 len=strlen(strtext);

 for(i=0;i<=len-1;++i)
 {
    for(j=0;j<=25;++j)
    {
     if(strtext[i]==lettertext[j])
     {
       strcode[i]=key[j];
     }
    }
 }
 cout<<"code=   "<<strcode<<endl;

 }