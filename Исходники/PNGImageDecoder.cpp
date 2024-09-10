void PNGImageDecoder::headerAvailable()
{
    png_structp png = m_reader->pngPtr();
    png_infop info = m_reader->infoPtr();
    png_uint_32 width = png_get_image_width(png, info);
    png_uint_32 height = png_get_image_height(png, info);

    // Protect against large PNGs. See http://bugzil.la/251381 for more details.
    const unsigned long maxPNGSize = 1000000UL;
    if (width > maxPNGSize || height > maxPNGSize) {
        longjmp(JMPBUF(png), 1);
        return;
    }

    // Set the image size now that the image header is available.
    if (!setSize(width, height)) {
        longjmp(JMPBUF(png), 1);
        return;
    }

    int bitDepth, colorType, interlaceType, compressionType, filterType, channels;
    png_get_IHDR(png, info, &width, &height, &bitDepth, &colorType, &interlaceType, &compressionType, &filterType);

    // The options we set here match what Mozilla does.

    // Expand to ensure we use 24-bit for RGB and 32-bit for RGBA.
    if (colorType == PNG_COLOR_TYPE_PALETTE || (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8))
        png_set_expand(png);

    png_bytep trns = 0;
    int trnsCount = 0;
    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_get_tRNS(png, info, &trns, &trnsCount, 0);
        png_set_expand(png);
    }

    if (bitDepth == 16)
        png_set_strip_16(png);

    if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

#if USE(QCMSLIB)
    if ((colorType & PNG_COLOR_MASK_COLOR) && !m_ignoreGammaAndColorProfile) {
        // We only support color profiles for color PALETTE and RGB[A] PNG. Supporting
        // color profiles for gray-scale images is slightly tricky, at least using the
        // CoreGraphics ICC library, because we expand gray-scale images to RGB but we
        // do not similarly transform the color profile. We'd either need to transform
        // the color profile or we'd need to decode into a gray-scale image buffer and
        // hand that to CoreGraphics.
        bool sRGB = false;
        ColorProfile colorProfile;
        getColorProfile(png, info, colorProfile, sRGB);
        bool imageHasAlpha = (colorType & PNG_COLOR_MASK_ALPHA) || trnsCount;
        m_reader->createColorTransform(colorProfile, imageHasAlpha, sRGB);
        m_hasColorProfile = !!m_reader->colorTransform();
    }
#endif

    if (!m_hasColorProfile) {
        // Deal with gamma and keep it under our control.
        const double inverseGamma = 0.45455;
        const double defaultGamma = 2.2;
        double gamma;
        if (!m_ignoreGammaAndColorProfile && png_get_gAMA(png, info, &gamma)) {
            const double maxGamma = 21474.83;
            if ((gamma <= 0.0) || (gamma > maxGamma)) {
                gamma = inverseGamma;
                png_set_gAMA(png, info, gamma);
            }
            png_set_gamma(png, defaultGamma, gamma);
        } else {
            png_set_gamma(png, defaultGamma, inverseGamma);
        }
    }

    // Tell libpng to send us rows for interlaced pngs.
    if (interlaceType == PNG_INTERLACE_ADAM7)
        png_set_interlace_handling(png);

    // Update our info now.
    png_read_update_info(png, info);
    channels = png_get_channels(png, info);
    ASSERT(channels == 3 || channels == 4);

    m_reader->setHasAlpha(channels == 4);

    if (m_reader->decodingSizeOnly()) {
        // If we only needed the size, halt the reader.
#if PNG_LIBPNG_VER_MAJOR > 1 || (PNG_LIBPNG_VER_MAJOR == 1 && PNG_LIBPNG_VER_MINOR >= 5)
        // '0' argument to png_process_data_pause means: Do not cache unprocessed data.
        m_reader->setReadOffset(m_reader->currentBufferSize() - png_process_data_pause(png, 0));
#else
        m_reader->setReadOffset(m_reader->currentBufferSize() - png->buffer_size);
        png->buffer_size = 0;
#endif
    }
}