static void line(FILE *pt,WORD x1,WORD y1,WORD x2,WORD y2)
{
    WORD points[4];
    points[0]=x1;
    points[1]=y1;
    points[2]=x2;
    points[3]=y2;
    polyline(pt,points,4);
    return;
}