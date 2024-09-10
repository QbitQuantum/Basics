void OutputList::parseDoc(const char *fileName,int startLine,
                          Definition *ctx,MemberDef * md,
                          const QCString &docStr,bool indexWords,
                          bool isExample,const char *exampleName,
                          bool singleLine,bool linkFromIndex)
{
    int count=0;
    if (docStr.isEmpty()) return;

    OutputGenerator *og=outputs->first();
    while (og)
    {
        if (og->isEnabled()) count++;
        og=outputs->next();
    }
    if (count==0) return; // no output formats enabled.

    DocNode *root=0;
    if (docStr.at(docStr.length()-1)=='\n')
    {
        root = validatingParseDoc(fileName,startLine,
                                  ctx,md,docStr,indexWords,isExample,exampleName,
                                  singleLine,linkFromIndex);
    }
    else
    {
        root = validatingParseDoc(fileName,startLine,
                                  ctx,md,docStr+"\n",indexWords,isExample,exampleName,
                                  singleLine,linkFromIndex);
    }

    og=outputs->first();
    while (og)
    {
        //printf("og->printDoc(extension=%s)\n",
        //    ctx?ctx->getDefFileExtension().data():"<null>");
        if (og->isEnabled()) og->printDoc(root,ctx?ctx->getDefFileExtension():QCString(""));
        og=outputs->next();
    }

    delete root;
}