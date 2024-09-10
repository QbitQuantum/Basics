int main(int argc,char **argv)
{
 URL *Url;
 URL **list,*refresh;
 int j;

 if(argc==1)
   {fprintf(stderr,"usage: test-doc URL < contents-of-url\n");return(1);}

 StderrLevel=ExtraDebug;

 InitErrorHandler("test-doc",0,1);

 InitConfigurationFile("./wwwoffle.conf");

 init_io(STDERR_FILENO);

 if(ReadConfigurationFile(STDERR_FILENO))
    PrintMessage(Fatal,"Error in configuration file 'wwwoffle.conf'.");

 finish_io(STDERR_FILENO);

 Url=SplitURL(argv[1]);

 init_io(0);

 ParseDocument(0,Url,1);

 if((refresh=GetReference(RefMetaRefresh)))
    printf("Refresh = %s\n",refresh->file);

 if((list=GetReferences(RefStyleSheet)))
    for(j=0;list[j];j++)
       printf("StyleSheet = %s\n",list[j]->file);

 if((list=GetReferences(RefImage)))
    for(j=0;list[j];j++)
       printf("Image = %s\n",list[j]->file);

 if((list=GetReferences(RefFrame)))
    for(j=0;list[j];j++)
       printf("Frame = %s\n",list[j]->file);

 if((list=GetReferences(RefScript)))
    for(j=0;list[j];j++)
       printf("Script = %s\n",list[j]->file);

 if((list=GetReferences(RefObject)))
    for(j=0;list[j];j++)
       printf("Object = %s\n",list[j]->file);

 if((list=GetReferences(RefInlineObject)))
    for(j=0;list[j];j++)
       printf("InlineObject = %s\n",list[j]->file);

 if((list=GetReferences(RefLink)))
    for(j=0;list[j];j++)
       printf("Link = %s\n",list[j]->file);

 FreeURL(Url);

 finish_io(0);

 return(0);
}