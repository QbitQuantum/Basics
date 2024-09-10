int IsUnicodeFile(char* szFileName)
{
    FILE *fpUnicode;
    char l_szCharBuffer[80];

    //Open the file
    if((fpUnicode= fopen(szFileName,"r")) == NULL)
    return 0; //Unable to open file

    if(!feof(fpUnicode))
    {
        fread(l_szCharBuffer,80,1,fpUnicode);
        fclose(fpUnicode);
        if(IsTextUnicode(l_szCharBuffer,80,NULL))
        {
            return 2; //Text is Unicode
        }
       else
       {
           return 1; //Text is ASCII
       }
    }
    return 0; // Some error happened
}