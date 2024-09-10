    void SBBox::SBBoxImpl::fillXValue(tmv::MatrixView<double> val,
                                      double x0, double dx, int izero,
                                      double y0, double dy, int jzero) const
    {
        dbg<<"SBBox fillXValue\n";
        dbg<<"x = "<<x0<<" + i * "<<dx<<", izero = "<<izero<<std::endl;
        dbg<<"y = "<<y0<<" + j * "<<dy<<", jzero = "<<jzero<<std::endl;

        assert(val.stepi() == 1);
        const int m = val.colsize();
        const int n = val.rowsize();
        typedef tmv::VIt<double,1,tmv::NonConj> It;

        // It will be useful to do everything in units of dx,dy
        x0 /= dx;
        double wo2 = _wo2 / std::abs(dx);
        y0 /= dy;
        double ho2 = _ho2 / std::abs(dy);
        xdbg<<"x0,y0 -> "<<x0<<','<<y0<<std::endl;
        xdbg<<"width,height -> "<<wo2*2.<<','<<ho2*2.<<std::endl;

        // Start by setting everything to zero
        val.setZero();

        // Then fill the interior with _norm:
        // Fill pixels where:
        //     x0 + ix >= -width/2
        //     x0 + ix < width/2
        //     y0 + iy >= -width/2
        //     y0 + iy < width/2

        int ix1 = std::max(0, int(std::ceil(-wo2 - x0)));
        int ix2 = std::min(m, int(std::ceil(wo2 - x0)));
        int iy1 = std::max(0, int(std::ceil(-ho2 - y0)));
        int iy2 = std::min(n, int(std::ceil(ho2 - y0)));

        if (ix1 < ix2 && iy1 < iy2)
            val.subMatrix(ix1,ix2,iy1,iy2).setAllTo(_norm);

#if 0
        // We used to implement this by making the pixels that cross the edge have a
        // fractional flux value appropriate for the fraction of the box that goes through
        // each pixel.  However, this isn't actually correct.  SBProfile objects are always
        // rendered as the local surface brightness at the center of the pixel.  To get
        // the right flux, you need to convolve by a Pixel.  So if someone renders a Box
        // without convolving by a pixel, it is inconsistent to do this differently than we
        // do all the other SBProfile types.  However, since it was an involved calculation
        // and someone might actually care to resurrect it in a different guise at some point,
        // I'm leaving it here, just commented out.

        // We need to make sure the pixels where the edges of the box fall only get
        // a fraction of the flux.
        //
        // We divide up the range into 3 sections in x:
        //    left of the box where val = 0
        //    in the box where val = _norm
        //    right of the box where val = 0 again
        //
        // ... and 3 sections in y:
        //    below the box where val = 0
        //    in the box where val = _norm
        //    above the box where val = 0 again
        //
        // Furthermore, we have to calculate the correct values for the pixels on the border.

        int ix_left, ix_right, iy_bottom, iy_top;
        double x_left, x_right, y_bottom, y_top;

        // Find the x edges:
        double tmp = 0.5*width + 0.5;
        ix_left = int(-tmp-x0+1);
        ix_right = int(tmp-x0);

        // If the box goes off the image, it's ok, but it will cause us problems
        // later on if we don't change it.  Just use ix_left = 0.
        if (ix_left < 0) { ix_left = 0; x_left = 1.; }

        // If the whole box is off the image, just zero and return.
        else if (ix_left >= m) { val.setZero(); return; }

        // Normal case: calculate the fractional flux in the edge
        else x_left = tmp+x0+ix_left;

        // Now the right side.
        if (ix_right >= m) { ix_right = m-1; x_right = 1.; }
        else if (ix_right < 0) { val.setZero(); return; }
        else x_right = tmp-x0-ix_right;
        xdbg<<"ix_left = "<<ix_left<<" with partial flux "<<x_left<<std::endl;
        xdbg<<"ix_right = "<<ix_right<<" with partial flux "<<x_right<<std::endl;

        // Repeat for y values
        tmp = 0.5*height + 0.5;
        iy_bottom = int(-tmp-y0+1);
        iy_top = int(tmp-y0);

        if (iy_bottom < 0) { iy_bottom = 0; y_bottom = 1.; }
        else if (iy_bottom >= n) { val.setZero(); return; }
        else y_bottom = tmp+y0+iy_bottom;

        if (iy_top >= n) { iy_top = n-1; y_top = 1.; }
        else if (iy_top < 0) { val.setZero(); return; }
        else y_top = tmp-y0-iy_top;
        xdbg<<"iy_bottom = "<<iy_bottom<<" with partial flux "<<y_bottom<<std::endl;
        xdbg<<"iy_top = "<<iy_top<<" with partial flux "<<y_top<<std::endl;
        xdbg<<"m,n = "<<m<<','<<n<<std::endl;

        // Now we need to fill the matrix with the appropriate values in each section.
        // Start with the zeros:
        if (0 < ix_left)
            val.subMatrix(0,ix_left,iy_bottom,iy_top+1).setZero();
        if (ix_right+1 < m)
            val.subMatrix(ix_right+1,m,iy_bottom,iy_top+1).setZero();
        if (0 < iy_bottom)
            val.colRange(0,iy_bottom).setZero();
        if (iy_top+1 < n)
            val.colRange(iy_top+1,n).setZero();
        // Then the interior:
        if (ix_left+1 < ix_right && iy_bottom+1 < iy_top)
            val.subMatrix(ix_left+1,ix_right,iy_bottom+1,iy_top).setAllTo(_norm);
        // And now the edges:
        if (ix_left+1 < ix_right) {
            val.col(iy_bottom,ix_left+1,ix_right).setAllTo(y_bottom * _norm);
            val.col(iy_top,ix_left+1,ix_right).setAllTo(y_top * _norm);
        }
        if (iy_bottom+1 < iy_top) {
            val.row(ix_left,iy_bottom+1,iy_top).setAllTo(x_left * _norm);
            val.row(ix_right,iy_bottom+1,iy_top).setAllTo(x_right * _norm);
        }
        // Finally the corners
        val(ix_left,iy_bottom) = x_left * y_bottom * _norm;
        val(ix_right,iy_bottom) = x_right * y_bottom * _norm;
        val(ix_left,iy_top) = x_left * y_top * _norm;
        val(ix_right,iy_top) = x_right * y_top * _norm;
#endif
    }