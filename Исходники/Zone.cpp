QRectF Zone::boundingRect() const
{
    // Assuming that (0,0) is the center of the object
    QRectF rectF(-width/2, -height/2, width, height);

    return rectF;
}