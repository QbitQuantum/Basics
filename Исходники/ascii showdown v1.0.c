void score(int uhealth,int chealth,int ubullets,int uboomerang,int uwall,int boost,int nofboost)   ///prints score
{
    HANDLE out;
    out=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD ctext={68,4},utext={68,16},utext1={68,17},utext2={68,18},utext3={68,19},utext4={68,20};
    SetConsoleCursorPosition(out,ctext);
    printf("   ");
    SetConsoleCursorPosition(out,utext);
    printf("   ");
    SetConsoleCursorPosition(out,utext1);
    printf("   ");
    SetConsoleCursorPosition(out,utext2);
    printf("  ");
    SetConsoleCursorPosition(out,utext3);
    printf("  ");
    SetConsoleCursorPosition(out,utext4);
    printf("   ");
    SetConsoleCursorPosition(out,ctext);
    printf("%d",chealth);
    SetConsoleCursorPosition(out,utext);
    printf("%d",uhealth);
    SetConsoleCursorPosition(out,utext1);
    printf("%d",ubullets);
    SetConsoleCursorPosition(out,utext2);
    printf("%d",uboomerang);
    SetConsoleCursorPosition(out,utext3);
    printf("%d",uwall);
    if(nofboost==1 && boost==0)
    {
        SetConsoleCursorPosition(out,utext4);
        SetConsoleTextAttribute(out,12);
        printf("OFF");
        SetConsoleTextAttribute(out,7);
    }
    else if(nofboost==0 && boost==1)
    {
        SetConsoleCursorPosition(out,utext4);
        SetConsoleTextAttribute(out,10);
        printf("ON");
        SetConsoleTextAttribute(out,7);
    }
    else if(nofboost==0 && boost==0)
    {
        SetConsoleCursorPosition(out,utext4);
        SetConsoleTextAttribute(out,14);
        printf("...");
        SetConsoleTextAttribute(out,7);
    }
}