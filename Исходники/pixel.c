int64
get_pixel_simple(int64 pixelres, struct Point* pt)
{
    int64 pix=0;

    int64 i=0;
    int64 ps=0, p2=1;
    long double cth=0;
    int64 n=0, m=0;
    if (pixelres > 0) {
        for (i=0; i<pixelres; i++) { // Work out # pixels/dim and start pix.
            p2  = p2<<1;
            ps += (p2/2)*(p2/2);
        }
      cth = cosl(pt->theta);
      n   = (cth==1.0) ? 0: (int64) ( ceill( (1.0-cth)/2 * p2 )-1 );
      m   = (int64) ( floorl( (pt->phi/2./M_PI)*p2 ) );
      pix = p2*n+m + ps;

    }
    return pix;
}