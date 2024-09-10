bool
ImageBufAlgo::deepen (ImageBuf &dst, const ImageBuf &src, float zvalue,
                      ROI roi, int nthreads)
{
    if (src.deep()) {
        // For some reason, we were asked to deepen an already-deep image.
        // So just copy it.
        return dst.copy (src);
        // FIXME: once paste works for deep files, this should really be
        // return paste (dst, roi.xbegin, roi.ybegin, roi.zbegin, roi.chbegin,
        //               src, roi, nthreads);
    }

    // Construct an ideal spec for dst, which is like src but deep.
    const ImageSpec &srcspec (src.spec());
    int nc = srcspec.nchannels;
    int zback_channel = -1;
    ImageSpec force_spec = srcspec;
    force_spec.deep = true;
    force_spec.set_format (TypeDesc::FLOAT);
    force_spec.channelformats.clear();
    for (int c = 0; c < nc; ++c) {
        if (force_spec.channelnames[c] == "Z")
            force_spec.z_channel = c;
        else if (force_spec.channelnames[c] == "Zback")
            zback_channel = c;
    }
    bool add_z_channel = (force_spec.z_channel < 0);
    if (add_z_channel) {
        // No z channel? Make one.
        force_spec.z_channel = force_spec.nchannels++;
        force_spec.channelnames.push_back ("Z");
    }

    if (! IBAprep (roi, &dst, &src, NULL, &force_spec, IBAprep_SUPPORT_DEEP))
        return false;
    if (! dst.deep()) {
        dst.error ("Cannot deepen to a flat image");
        return false;
    }

    float *pixel = OIIO_ALLOCA (float, nc);

    // First, figure out which pixels get a sample and which do not
    for (int z = roi.zbegin; z < roi.zend; ++z)
    for (int y = roi.ybegin; y < roi.yend; ++y)
    for (int x = roi.xbegin; x < roi.xend; ++x) {
        bool has_sample = false;
        src.getpixel (x, y, z, pixel);
        for (int c = 0; c < nc; ++c)
            if (c != force_spec.z_channel && c != zback_channel
                  && pixel[c] != 0.0f) {
                has_sample = true;
                break;
            }
        if (! has_sample && ! add_z_channel)
            for (int c = 0; c < nc; ++c)
                if ((c == force_spec.z_channel || c == zback_channel)
                    && (pixel[c] != 0.0f && pixel[c] < 1e30)) {
                    has_sample = true;
                    break;
                }
        if (has_sample)
            dst.set_deep_samples (x, y, z, 1);
    }

    dst.deep_alloc ();

    // Now actually set the values
    for (int z = roi.zbegin; z < roi.zend; ++z)
    for (int y = roi.ybegin; y < roi.yend; ++y)
    for (int x = roi.xbegin; x < roi.xend; ++x) {
        if (dst.deep_samples (x, y, z) == 0)
            continue;
        for (int c = 0; c < nc; ++c)
            dst.set_deep_value (x, y, z, c, 0 /*sample*/,
                                src.getchannel (x, y, z, c));
        if (add_z_channel)
            dst.set_deep_value (x, y, z, nc, 0, zvalue);
    }

    bool ok = true;
    // FIXME -- the above doesn't split into threads. Someday, it should
    // be refactored like this:
    // OIIO_DISPATCH_COMMON_TYPES2 (ok, "deepen", deepen_,
    //                              dst.spec().format, srcspec.format,
    //                              dst, src, add_z_channel, z, roi, nthreads);
    return ok;
}