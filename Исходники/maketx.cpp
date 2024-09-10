static void
fix_latl_edges (ImageBuf &buf)
{
    ASSERT (envlatlmode && "only call fix_latl_edges for latlong maps");
    int n = buf.nchannels();
    float *left = ALLOCA (float, n);
    float *right = ALLOCA (float, n);

    // Make the whole first and last row be solid, since they are exactly
    // on the pole
    float wscale = 1.0f / (buf.spec().width);
    for (int j = 0;  j <= 1;  ++j) {
        int y = (j==0) ? buf.ybegin() : buf.yend()-1;
        // use left for the sum, right for each new pixel
        for (int c = 0;  c < n;  ++c)
            left[c] = 0.0f;
        for (int x = buf.xbegin();  x < buf.xend();  ++x) {
            buf.getpixel (x, y, right);
            for (int c = 0;  c < n;  ++c)
                left[c] += right[c];
        }
        for (int c = 0;  c < n;  ++c)
            left[c] += right[c];
        for (int c = 0;  c < n;  ++c)
            left[c] *= wscale;
        for (int x = buf.xbegin();  x < buf.xend();  ++x)
            buf.setpixel (x, y, left);
    }

    // Make the left and right match, since they are both right on the
    // prime meridian.
    for (int y = buf.ybegin();  y < buf.yend();  ++y) {
        buf.getpixel (buf.xbegin(), y, left);
        buf.getpixel (buf.xend()-1, y, right);
        for (int c = 0;  c < n;  ++c)
            left[c] = 0.5f * left[c] + 0.5f * right[c];
        buf.setpixel (buf.xbegin(), y, left);
        buf.setpixel (buf.xend()-1, y, left);
    }
}