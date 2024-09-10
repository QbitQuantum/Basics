static void
interppixel_NDC_clamped (const ImageBuf &buf, float x, float y, float *pixel,
                         bool envlatlmode)
{
    int fx = buf.spec().full_x;
    int fy = buf.spec().full_y;
    int fw = buf.spec().full_width;
    int fh = buf.spec().full_height;
    x = static_cast<float>(fx) + x * static_cast<float>(fw);
    y = static_cast<float>(fy) + y * static_cast<float>(fh);

    const int maxchannels = 64;  // Reasonable guess
    float p[4][maxchannels];
    DASSERT (buf.spec().nchannels <= maxchannels && 
             "You need to increase maxchannels");
    int n = std::min (buf.spec().nchannels, maxchannels);
    x -= 0.5f;
    y -= 0.5f;
    int xtexel, ytexel;
    float xfrac, yfrac;
    xfrac = floorfrac (x, &xtexel);
    yfrac = floorfrac (y, &ytexel);
    // Clamp
    int xnext = Imath::clamp (xtexel+1, buf.xmin(), buf.xmax());
    int ynext = Imath::clamp (ytexel+1, buf.ymin(), buf.ymax());
    xnext = Imath::clamp (xnext, buf.xmin(), buf.xmax());
    ynext = Imath::clamp (ynext, buf.ymin(), buf.ymax());

    // Get the four texels
    buf.getpixel (xtexel, ytexel, p[0], n);
    buf.getpixel (xnext, ytexel, p[1], n);
    buf.getpixel (xtexel, ynext, p[2], n);
    buf.getpixel (xnext, ynext, p[3], n);
    if (envlatlmode) {
        // For latlong environment maps, in order to conserve energy, we
        // must weight the pixels by sin(t*PI) because pixels closer to
        // the pole are actually less area on the sphere. Doing this
        // wrong will tend to over-represent the high latitudes in
        // low-res MIP levels.  We fold the area weighting into our
        // linear interpolation by adjusting yfrac.
        float w0 = (1.0f - yfrac) * sinf ((float)M_PI * (ytexel+0.5f)/(float)fh);
        float w1 = yfrac * sinf ((float)M_PI * (ynext+0.5f)/(float)fh);
        yfrac = w0 / (w0 + w1);
    }
    // Bilinearly interpolate
    bilerp (p[0], p[1], p[2], p[3], xfrac, yfrac, n, pixel);
}