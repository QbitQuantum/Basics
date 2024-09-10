ZRect ZRect::Intersection(const ZRect &rect) const
{
    float tempX=0,tempY=0,tempW=0,tempH=0;

    //can only grab the intersection if they intersect
    if(Intersects(rect))
    {
        tempX = rX > rect.X() ? rX : rect.X();
        tempY = rY > rect.Y() ? rY : rect.Y();
        tempW = rX+rWidth < rect.Right() ? rX+rWidth : rect.Right();
        tempH = rY+rHeight < rect.Bottom() ? rY+rHeight : rect.Bottom();

        tempW -= tempX;        //adjust width and height
        tempH -= tempY;
    }

    return ZRect(tempX,tempY,tempW,tempH);
}