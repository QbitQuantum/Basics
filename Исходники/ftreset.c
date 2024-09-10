VOID vPageOut(HDC hdc,int page,int doc, PSZ pszMode)
{
    int x,y;
    CHAR ach[120];

    StartPage(hdc);
    x = GetDeviceCaps(hdc,HORZRES) - 1;
    y = GetDeviceCaps(hdc,VERTRES) - 1;

    sprintf(ach,"Page %ld, Doc %ld, (%ld x %ld), in %s",page,doc,x,y,pszMode);

    TextOut(hdc,500,50,ach,strlen(ach));

    MoveToEx(hdc,0,0,NULL);
    LineTo(hdc,x,0);
    LineTo(hdc,x,y);
    LineTo(hdc,0,y);
    LineTo(hdc,0,0);

    vPage1F(NULL,hdc,NULL);

    EndPage(hdc);
}