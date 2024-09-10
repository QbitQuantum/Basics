/*
 * rotate image
 */
Image* ip_rotate (Image* src, double theta)
{
    Image* dest = new Image(src->getWidth(), src->getHeight());
    double x = src->getWidth()/2;
    double y = src->getHeight()/2;
    double ctheta = cos(-theta);
    double stheta = sin(-theta);
    Pixel white = Pixel(1, 1, 1);
    dest->fillImage(white);
    for (int i = 0; i < dest->getWidth(); ++i) {
        for (int j = 0; j < dest->getHeight(); ++j) {
            double xp = x + (i-x)*ctheta - (j-y)*stheta;
            double yp = y + (i-x)*stheta + (j-y)*ctheta;
            
            Pixel p = ip_resample_bilinear(src, xp, yp);
            
            dest->setPixel(i, j, p);
        }
    }
    
    return dest;
}