void fillCircle( const RGB& c, int centerX, int centerY, int radius )
{
    int radius2 = radius * radius;
    for(int y = 0; y < img.height() ; y++) {
        for(int x = 0; x < img.width(); x++) {
            int dx = x - centerX;
            int dy = y - centerY;
            int rr = dx * dx + dy * dy;
            if( rr > radius2 ) continue;

            img.setPixel(x, y, c);
        }
    }
}