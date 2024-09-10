bool
ImageInput::read_scanlines (int ybegin, int yend, int z,
                            int chbegin, int chend,
                            TypeDesc format, void *data,
                            stride_t xstride, stride_t ystride)
{
    chend = clamp (chend, chbegin+1, m_spec.nchannels);
    int nchans = chend - chbegin;
    yend = std::min (yend, spec().y+spec().height);
    size_t native_pixel_bytes = m_spec.pixel_bytes (chbegin, chend, true);
    imagesize_t native_scanline_bytes = clamped_mult64 ((imagesize_t)m_spec.width,
                                                        (imagesize_t)native_pixel_bytes);
    bool native = (format == TypeDesc::UNKNOWN);
    size_t pixel_bytes = native ? native_pixel_bytes : format.size()*nchans;
    if (native && xstride == AutoStride)
        xstride = pixel_bytes;
    stride_t zstride = AutoStride;
    m_spec.auto_stride (xstride, ystride, zstride, format, nchans,
                        m_spec.width, m_spec.height);
    bool contiguous = (xstride == (stride_t) native_pixel_bytes &&
                       ystride == (stride_t) native_scanline_bytes);
    // If user's format and strides are set up to accept the native data
    // layout, read the scanlines directly into the user's buffer.
    bool rightformat = (format == TypeDesc::UNKNOWN) ||
        (format == m_spec.format && m_spec.channelformats.empty());
    if (rightformat && contiguous) {
        if (chbegin == 0 && chend == m_spec.nchannels)
            return read_native_scanlines (ybegin, yend, z, data);
        else
            return read_native_scanlines (ybegin, yend, z, chbegin, chend, data);
    }

    // No such luck.  Read scanlines in chunks.

    const imagesize_t limit = 16*1024*1024;   // Allocate 16 MB, or 1 scanline
    int chunk = std::max (1, int(limit / native_scanline_bytes));
    boost::scoped_array<char> buf (new char [chunk * native_scanline_bytes]);

    bool ok = true;
    int scanline_values = m_spec.width * nchans;
    for (;  ok && ybegin < yend;  ybegin += chunk) {
        int y1 = std::min (ybegin+chunk, yend);
        ok &= read_native_scanlines (ybegin, y1, z, chbegin, chend, &buf[0]);
        if (! ok)
            break;

        int nscanlines = y1 - ybegin;
        int chunkvalues = scanline_values * nscanlines;
        if (m_spec.channelformats.empty()) {
            // No per-channel formats -- do the conversion in one shot
            if (contiguous) {
                ok = convert_types (m_spec.format, &buf[0], format, data, chunkvalues);
            } else {
                ok = parallel_convert_image (nchans, m_spec.width, nscanlines, 1, 
                                    &buf[0], m_spec.format, AutoStride, AutoStride, AutoStride,
                                    data, format, xstride, ystride, zstride);
            }
        } else {
            // Per-channel formats -- have to convert/copy channels individually
            size_t offset = 0;
            for (int c = 0;  ok && c < nchans;  ++c) {
                TypeDesc chanformat = m_spec.channelformats[c+chbegin];
                ok = convert_image (1 /* channels */, m_spec.width, nscanlines, 1, 
                                    &buf[offset], chanformat, 
                                    native_pixel_bytes, AutoStride, AutoStride,
                                    (char *)data + c*format.size(),
                                    format, xstride, ystride, zstride);
                offset += chanformat.size ();
            }
        }
        if (! ok)
            error ("ImageInput::read_scanlines : no support for format %s",
                   m_spec.format.c_str());
        data = (char *)data + ystride*nscanlines;
    }
    return ok;
}