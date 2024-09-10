void optimizePolygon(ClipperLib::Polygon& poly)
{
    Point p0 = poly[poly.size()-1];
    for(unsigned int i=0;i<poly.size();i++)
    {
        Point p1 = poly[i];
        if (shorterThen(p0 - p1, 10))
        {
            poly.erase(poly.begin() + i);
            i --;
        }else{
            Point p2;
            if (i < poly.size() - 1)
                p2 = poly[i+1];
            else
                p2 = poly[0];
            
            Point diff0 = normal(p1 - p0, 1000000);
            Point diff2 = normal(p1 - p2, 1000000);
            
            int64_t d = dot(diff0, diff2);
            if (d < -999999000000LL)
            {
                poly.erase(poly.begin() + i);
                i --;
            }else{
                p0 = p1;
            }
        }
    }
}