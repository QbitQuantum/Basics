OIIO_NAMESPACE_BEGIN



bool
ImageBufAlgo::from_IplImage (ImageBuf &dst, const IplImage *ipl,
                             TypeDesc convert)
{
    if (! ipl) {
        DASSERT (0 && "ImageBufAlgo::fromIplImage called with NULL ipl");
        dst.error ("Passed NULL source IplImage");
        return false;
    }
#ifdef USE_OPENCV
    TypeDesc srcformat;
    switch (ipl->depth) {
    case int(IPL_DEPTH_8U) :
        srcformat = TypeDesc::UINT8;  break;
    case int(IPL_DEPTH_8S) :
        srcformat = TypeDesc::INT8;  break;
    case int(IPL_DEPTH_16U) :
        srcformat = TypeDesc::UINT16;  break;
    case int(IPL_DEPTH_16S) :
        srcformat = TypeDesc::INT16;  break;
    case int(IPL_DEPTH_32F) :
        srcformat = TypeDesc::FLOAT;  break;
    case int(IPL_DEPTH_64F) :
        srcformat = TypeDesc::DOUBLE;  break;
    default:
        DASSERT (0 && "unknown IplImage type");
        dst.error ("Unsupported IplImage depth %d", (int)ipl->depth);
        return false;
    }

    TypeDesc dstformat = (convert != TypeDesc::UNKNOWN) ? convert : srcformat;
    ImageSpec spec (ipl->width, ipl->height, ipl->nChannels, dstformat);
    // N.B. The OpenCV headers say that ipl->alphaChannel,
    // ipl->colorModel, and ipl->channelSeq are ignored by OpenCV.

    if (ipl->dataOrder != IPL_DATA_ORDER_PIXEL) {
        // We don't handle separate color channels, and OpenCV doesn't either
        dst.error ("Unsupported IplImage data order %d", (int)ipl->dataOrder);
        return false;
    }

    dst.reset (dst.name(), spec);
    size_t pixelsize = srcformat.size()*spec.nchannels;
    // Account for the origin in the line step size, to end up with the
    // standard OIIO origin-at-upper-left:
    size_t linestep = ipl->origin ? -ipl->widthStep : ipl->widthStep;
    // Block copy and convert
    convert_image (spec.nchannels, spec.width, spec.height, 1,
                   ipl->imageData, srcformat,
                   pixelsize, linestep, 0,
                   dst.pixeladdr(0,0), dstformat,
                   spec.pixel_bytes(), spec.scanline_bytes(), 0);
    // FIXME - honor dataOrder.  I'm not sure if it is ever used by
    // OpenCV.  Fix when it becomes a problem.

    // OpenCV uses BGR ordering
    // FIXME: what do they do with alpha?
    if (spec.nchannels >= 3) {
        float pixel[4];
        for (int y = 0;  y < spec.height;  ++y) {
            for (int x = 0;  x < spec.width;  ++x) {
                dst.getpixel (x, y, pixel, 4);
                float tmp = pixel[0];  pixel[0] = pixel[2]; pixel[2] = tmp;
                dst.setpixel (x, y, pixel, 4);
            }
        }
    }
    // FIXME -- the copy and channel swap should happen all as one loop,
    // probably templated by type.

    return true;
#else
    dst.error ("fromIplImage not supported -- no OpenCV support at compile time");
    return false;
#endif
}