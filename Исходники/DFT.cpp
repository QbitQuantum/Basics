void FFTConvolve::convolveSingle(Image im, Image filter, Image out, Convolve::BoundaryCondition b) {

    // Deal with the homogeneous case recursively. This is slightly
    // inefficient because we construct and transform the filter
    // twice, but it makes the code much simpler
    if (b == Convolve::Homogeneous) {
        Image result = apply(im, filter, Convolve::Zero, Multiply::Outer);
        Image weight(im.width, im.height, im.frames, 1);
        weight.set(1.0f);
        Image resultW = apply(weight, filter, Convolve::Zero, Multiply::Outer);
        out += Stats(filter).sum() * result / resultW;
        return;
    }

    assert(filter.width % 2 == 1 &&
           filter.height % 2 == 1 &&
           filter.frames % 2 == 1,
           "The filter must have odd dimensions\n");

    int xPad = filter.width/2;
    int yPad = filter.height/2;
    int tPad = filter.frames/2;

    if (b == Convolve::Wrap) {
        xPad = yPad = tPad = 0;
    }

    Image weightT;

    Image imT = Image(im.width+xPad*2, im.height+yPad*2, im.frames+tPad*2, 2);

    //printf("1\n"); fflush(stdout);
    // 1) Make the padded complex image
    if (b == Convolve::Clamp) {
        for (int t = 0; t < imT.frames; t++) {
            int st = clamp(t-tPad, 0, im.frames-1);
            for (int y = 0; y < imT.height; y++) {
                int sy = clamp(y-yPad, 0, im.height-1);
                for (int x = 0; x < imT.width; x++) {
                    int sx = clamp(x-xPad, 0, im.width-1);
                    imT(x, y, t, 0) = im(sx, sy, st, 0);
                }
            }
        }
    } else { // Zero or Wrap
        imT.region(xPad, yPad, tPad, 0,
                   im.width, im.height, im.frames, 1).set(im);
    }

    //printf("2\n"); fflush(stdout);
    // 2) Transform the padded image
    FFT::apply(imT);

    //printf("3\n"); fflush(stdout);
    // 3) Make a padded complex filter of the same size
    Image filterT(imT.width, imT.height, imT.frames, 2);
    for (int t = 0; t < filter.frames; t++) {
        int ft = t - filter.frames/2;
        if (ft < 0) ft += filterT.frames;
        for (int y = 0; y < filter.height; y++) {
            int fy = y - filter.height/2;
            if (fy < 0) fy += filterT.height;
            for (int x = 0; x < filter.width; x++) {
                int fx = x - filter.width/2;
                if (fx < 0) fx += filterT.width;
                filterT(fx, fy, ft, 0) = filter(x, y, t, 0);
            }
        }
    }

    //printf("4\n"); fflush(stdout);
    // 4) Transform the padded filter
    FFT::apply(filterT);

    //printf("5\n"); fflush(stdout);
    // 5) Multiply the two into a padded complex transformed result
    ComplexMultiply::apply(imT, filterT);

    //printf("6\n"); fflush(stdout);
    // 6) Inverse transorm the result
    IFFT::apply(imT);

    //printf("7\n"); fflush(stdout);
    // 7) Remove the padding, and convert back to real numbers
    out += imT.region(xPad, yPad, tPad, 0,
                      im.width, im.height, im.frames, 1);
}