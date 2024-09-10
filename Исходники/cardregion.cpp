int CardRegion::GetOverlapRatio(int x, int y, int w, int h)
{
    RECT me, him;
    RECT inter;
    SetRect(&him, x, y, x+w, y+h);
    SetRect(&me,  xpos, ypos, xpos+width, ypos+height);

    //see if the specified rectangle overlaps us
    if(IntersectRect(&inter, &me, &him))
    {
        int wi = inter.right  - inter.left;
        int hi = inter.bottom - inter.top;

        int overlap = wi * hi;
        int total   = width * height;

        int percent = (overlap << 16) / total;
        return (percent * 100) >> 16;
    }