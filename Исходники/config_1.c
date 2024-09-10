void main(void)
{
    static FILE_DATA far *config;
    int i;
    char sItem1[20];
    char sItem2[20];
    char sItem3[20];
    char sItem4[20];
    char sTemp[40];
      
    unsigned long lPointer=0;
    int iTh;    // iThe: to find information from ?th * in the text file
    
    InitLib();
    
    config=GetFileInfoByName("config_1.ini");   // Opens one file by name
    
    while(lPointer<config->size) 
    {
        lPointer=FSeek(config, '*', lPointer, 1);
        if(lPointer)    // cannot find '*'
        {
            sscanf(config->addr+lPointer, "%s %s %s %s", &sItem1, &sItem2, &sItem3, &sItem4); 
            sprintf(sTemp, "Item1=%s Item2=%s Item3=%s Item4=%s", sItem1, sItem2, sItem3, sItem4);
            Print("%s\n\r", sTemp);
        }   
        else
            break;
    }
}