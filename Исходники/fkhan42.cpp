int main(int argc, char **argv)
{
    debugMode= debugSwitch(argv);//either TRUE or FALSE
    DIR           *theDirectory;
    struct dirent *aFile;
    char inFileName[12];
    FILE *inFile;
    content *tableofContents;//point to the structs
    int fileCount;//number of .txt files
    char sml[7]; //the user will specify small,medium or large
    int stringLength;
    int displayPairs;
    int mossSpace;
    

    intro();
    
    theDirectory=specifyDirLengthPairs(sml,&stringLength,&displayPairs);
    
    tableofContents= allocateSpaceStruct(fileCount=ListFileNames(theDirectory));
    
    readInFileNames(tableofContents, theDirectory, sml);
    
    combineDIRandTxtName(tableofContents, sml, fileCount);
    
    numbValidChar(tableofContents,fileCount);
    
    mallocSpaceChar (tableofContents, fileCount);
    
    readInChar(tableofContents,fileCount);
    
    numberofBlocks(tableofContents,stringLength,fileCount);
    
    mallocBlocksofChar(tableofContents,fileCount, stringLength);
    
    sortBlocksChar(tableofContents,fileCount);
    
    moss* mossKeeper=mossMalloc(fileCount,&mossSpace);

    int mKindex=0;
    while(mKindex<mossSpace)
    {
        //printf("mkindex::%d,,txtA:%d,,txtB::%d\n",mKindex ,mossKeeper[mKindex].txtNumA,mossKeeper[mKindex].txtNumB);
        
        Bsearch(mossKeeper,tableofContents,mKindex,stringLength);
        mKindex++;
    }
    
    diplayTop(displayPairs,mossKeeper,mossSpace,tableofContents);
    
    freeAll(tableofContents,fileCount,mossKeeper);
    
    return 0;
 
}