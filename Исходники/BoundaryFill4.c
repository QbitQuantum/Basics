void boundaryfill4(int x , int y,int IC)
{
    if(getpixel(x,y)!=IC && getpixel(x,y)!=2)
    {
        putpixel(x,y,IC);
        boundaryfill4( x+1,  y, IC);
        boundaryfill4( x-1,  y, IC);
        boundaryfill4( x,  y+1, IC);
        boundaryfill4( x, y-1, IC);
    }
}