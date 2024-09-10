void main(void)
{
    int seg, data;
    char c;
    unsigned e=0x9000,i=0;
    
    InitLib();
    
    Print("\r\nPlease Input a value writting to segment 0x9000 of Flash Member: ");
    Scanf("%d", &seg);
    
    FlashErase(e);
    while(i<65535)
    {
        FlashWrite(e, i, seg);
        Print("\r\nThe value %d is writting to offset %d of Flash Memory", seg, i);
        i++;
        seg++;
        if(i%100==0)
        {
            Print("\r\nPress q to quit or any key to continue...");
            c=Getch();
            if ((c=='q') || (c=='Q'))
                return;
        }
    }
}