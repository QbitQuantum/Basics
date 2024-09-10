// Print Shellcode 
void PrintSc(unsigned char *sc, int len)
{
    int    i,j;
    char *p;
    char msg[6];
    
    //printf("/* %d bytes */\n", buffsize);
    
    // Print general shellcode
    for(i = 0; i < len; i++)
    {
        if((i%16)==0)
        {
            if(i!=0)
                printf("\"\n\"");
            else
                printf("\"");
        }
        
        //printf("\\x%.2X", sc[i]);
        
        sprintf(msg, "\\x%.2X", sc[i] & 0xff);

        for( p = msg, j=0; j < 4; p++, j++ )
        {
            if(isupper(*p))
                printf("%c", _tolower(*p));
            else
                printf("%c", p[0]);
        }
    }
    
    printf("\";\n");
}