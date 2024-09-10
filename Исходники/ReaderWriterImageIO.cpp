/* Create a CGImageRef from osg::Image.
 * Code adapted from
 * http://developer.apple.com/samplecode/OpenGLScreenSnapshot/listing2.html
 */
CGImageRef CreateCGImageFromOSGData(const osg::Image& osg_image)
{
    size_t image_width = osg_image.s();
    size_t image_height = osg_image.t();
    /* From Apple's header for CGBitmapContextCreate()
     * Each row of the bitmap consists of `bytesPerRow' bytes, which must be at
     * least `(width * bitsPerComponent * number of components + 7)/8' bytes.
     */
    size_t target_bytes_per_row;

    CGColorSpaceRef color_space;
    CGBitmapInfo bitmap_info;
    /* From what I can figure out so far...
     * We need to create a CGContext connected to the data we want to save
     * and then call CGBitmapContextCreateImage() on that context to get
     * a CGImageRef.
     * However, OS X only allows 4-component image formats (e.g. RGBA) and not
     * just RGB for the RGB-based CGContext. So for a 24-bit image coming in,
     * we need to expand the data to 32-bit.
     * The easiest and fastest way to do that is through the vImage framework
     * which is part of the Accelerate framework.
     * Also, the osg::Image data coming in is inverted from what we want, so
     * we need to invert the image too. Since the osg::Image is const,
     * we don't want to touch the data, so again we turn to the vImage framework
     * and invert the data.
     */
    vImage_Buffer vimage_buffer_in =
    {
        (void*)osg_image.data(), // need to override const, but we don't modify the data so it's safe
        image_height,
        image_width,
        osg_image.getRowSizeInBytes()
    };

    void* out_image_data;
    vImage_Buffer vimage_buffer_out =
    {
        NULL, // will fill-in in switch
        image_height,
        image_width,
        0 // will fill-in in switch
    };
    vImage_Error vimage_error_flag;

    // FIXME: Do I want to use format, type, or internalFormat?
    switch(osg_image.getPixelFormat())
    {
        case GL_LUMINANCE:
        {
            bitmap_info = kCGImageAlphaNone;
            target_bytes_per_row = (image_width * 8 + 7)/8;
            //color_space = CGColorSpaceCreateWithName(kCGColorSpaceGenericGray);
            color_space = CGColorSpaceCreateDeviceGray();
            if(NULL == color_space)
            {
                return NULL;
            }

            //    out_image_data = calloc(target_bytes_per_row, image_height);
            out_image_data = malloc(target_bytes_per_row * image_height);
            if(NULL == out_image_data)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, malloc failed" << std::endl;
                CGColorSpaceRelease(color_space);
                return NULL;
            }

            vimage_buffer_out.data = out_image_data;
            vimage_buffer_out.rowBytes = target_bytes_per_row;

            // Now invert the image
            vimage_error_flag = vImageVerticalReflect_Planar8(
                &vimage_buffer_in, // since the osg_image is const...
                &vimage_buffer_out, // don't reuse the buffer
                kvImageNoFlags
            );
            if(vimage_error_flag != kvImageNoError)
            {
                OSG_WARN << "In CreateCGImageFromOSGData for GL_LUMINANCE, vImageVerticalReflect_Planar8 failed with vImage Error Code: " << vimage_error_flag << std::endl;
                free(out_image_data);
                CGColorSpaceRelease(color_space);
                return NULL;
            }


            break;
        }
        case GL_ALPHA:
        {
            bitmap_info = kCGImageAlphaOnly;
            target_bytes_per_row = (image_width * 8 + 7)/8;
            // According to:
            // http://developer.apple.com/qa/qa2001/qa1037.html
            // colorSpace=NULL is for alpha only
            color_space = NULL;

            //    out_image_data = calloc(target_bytes_per_row, image_height);
            out_image_data = malloc(target_bytes_per_row * image_height);
            if(NULL == out_image_data)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, malloc failed" << std::endl;
                return NULL;
            }

            vimage_buffer_out.data = out_image_data;
            vimage_buffer_out.rowBytes = target_bytes_per_row;

            // Now invert the image
            vimage_error_flag = vImageVerticalReflect_Planar8(
                &vimage_buffer_in, // since the osg_image is const...
                &vimage_buffer_out, // don't reuse the buffer
                kvImageNoFlags
            );
            if(vimage_error_flag != kvImageNoError)
            {
                OSG_WARN << "In CreateCGImageFromOSGData for GL_ALPHA, vImageVerticalReflect_Planar8 failed with vImage Error Code: " << vimage_error_flag << std::endl;
                free(out_image_data);
                return NULL;
            }


            break;
        }
/*
        case GL_LUMINANCE_ALPHA:
        {
            // I don't know if we can support this.
            // The qa1037 doesn't show both gray+alpha.
            break;
        }
*/
        case GL_RGB:
        {
            bitmap_info = kCGImageAlphaNoneSkipFirst;
            target_bytes_per_row = (image_width * 8 * 4 + 7)/8;
            //color_space = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
            color_space = CGColorSpaceCreateDeviceRGB();
             if(NULL == color_space)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, CGColorSpaceCreateWithName failed" << std::endl;
                return NULL;
            }

            //    out_image_data = calloc(target_bytes_per_row, image_height);
            out_image_data = malloc(target_bytes_per_row * image_height);
            if(NULL == out_image_data)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, malloc failed" << std::endl;
                CGColorSpaceRelease(color_space);
                return NULL;
            }

            // Use vImage to get an RGB buffer into ARGB.
            vimage_buffer_out.data = out_image_data;
            vimage_buffer_out.rowBytes = target_bytes_per_row;
            vimage_error_flag = vImageConvert_RGB888toARGB8888(
                &vimage_buffer_in,
                NULL, // we don't have a buffer containing alpha values
                255, // The alpha value we want given to all pixels since we don't have a buffer
                &vimage_buffer_out,
                0, // premultiply?
                kvImageNoFlags // Only responds to kvImageDoNotTile, but I think we want tiling/threading
            );
            if(vimage_error_flag != kvImageNoError)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, vImageConvert_RGB888toARGB8888 failed with vImage Error Code: " << vimage_error_flag << std::endl;
                free(out_image_data);
                CGColorSpaceRelease(color_space);
                return NULL;
            }
            // Now invert the image
            vimage_error_flag = vImageVerticalReflect_ARGB8888(
                &vimage_buffer_out,
                &vimage_buffer_out, // reuse the same buffer
                kvImageNoFlags
            );
            if(vimage_error_flag != kvImageNoError)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, vImageAffineWarp_ARGB8888 failed with vImage Error Code: " << vimage_error_flag << std::endl;
                free(out_image_data);
                CGColorSpaceRelease(color_space);
                return NULL;
            }

            break;
        }
        case GL_RGBA:
        {
            bitmap_info = kCGImageAlphaPremultipliedLast;
            target_bytes_per_row = osg_image.getRowSizeInBytes();
            //color_space = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
            color_space = CGColorSpaceCreateDeviceRGB();
            if(NULL == color_space)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, CGColorSpaceCreateWithName failed" << std::endl;
                return NULL;
            }
            //    out_image_data = calloc(target_bytes_per_row, image_height);
            out_image_data = malloc(target_bytes_per_row * image_height);
            if(NULL == out_image_data)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, malloc failed" << std::endl;
                CGColorSpaceRelease(color_space);
                return NULL;
            }
            vimage_buffer_out.data = out_image_data;
            vimage_buffer_out.rowBytes = target_bytes_per_row;
            // Invert the image
            vimage_error_flag = vImageVerticalReflect_ARGB8888(
                &vimage_buffer_in, // since the osg_image is const...
                &vimage_buffer_out, // don't reuse the buffer
                kvImageNoFlags
            );
            if(vimage_error_flag != kvImageNoError)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, vImageAffineWarp_ARGB8888 failed with vImage Error Code: " << vimage_error_flag << std::endl;
                free(out_image_data);
                CGColorSpaceRelease(color_space);
                return NULL;
            }
            break;
        }
        case GL_BGRA:
        {
            if(GL_UNSIGNED_INT_8_8_8_8_REV == osg_image.getDataType())
            {
#if __BIG_ENDIAN__
                bitmap_info = kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Big; /* XRGB Big Endian */
#else
                bitmap_info = kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little; /* XRGB Little Endian */
#endif
            }
            else
            {
                // FIXME: Don't know how to handle this case
                bitmap_info = kCGImageAlphaPremultipliedLast;
            }

            target_bytes_per_row = osg_image.getRowSizeInBytes();
            //color_space = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
            color_space = CGColorSpaceCreateDeviceRGB();
            if(NULL == color_space)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, CGColorSpaceCreateWithName failed" << std::endl;
                return NULL;
            }
            //    out_image_data = calloc(target_bytes_per_row, image_height);
            out_image_data = malloc(target_bytes_per_row * image_height);
            if(NULL == out_image_data)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, malloc failed" << std::endl;
                CGColorSpaceRelease(color_space);
                return NULL;
            }
            vimage_buffer_out.data = out_image_data;
            vimage_buffer_out.rowBytes = target_bytes_per_row;
            // Invert the image
            vimage_error_flag = vImageVerticalReflect_ARGB8888(
                                                               &vimage_buffer_in, // since the osg_image is const...
                                                               &vimage_buffer_out, // don't reuse the buffer
                                                               kvImageNoFlags
                                                               );
            if(vimage_error_flag != kvImageNoError)
            {
                OSG_WARN << "In CreateCGImageFromOSGData, vImageAffineWarp_ARGB8888 failed with vImage Error Code: " << vimage_error_flag << std::endl;
                free(out_image_data);
                CGColorSpaceRelease(color_space);
                return NULL;
            }
            break;
        }
        // FIXME: Handle other cases.
        // Use vImagePermuteChannels_ARGB8888 to swizzle bytes
        default:
        {
            OSG_WARN << "In CreateCGImageFromOSGData: Sorry support for this format is not implemented." << std::endl;
            return NULL;
            break;
        }
    }

    CGContextRef bitmap_context = CGBitmapContextCreate(
        vimage_buffer_out.data,
        vimage_buffer_out.width,
        vimage_buffer_out.height,
        8,
        vimage_buffer_out.rowBytes,
        color_space,
        bitmap_info
    );
    /* Done with color space */
    CGColorSpaceRelease(color_space);

    if(NULL == bitmap_context)
    {
        free(out_image_data);
        return NULL;
    }


    /* Make an image out of our bitmap; does a cheap vm_copy of the bitmap */
    CGImageRef image_ref = CGBitmapContextCreateImage(bitmap_context);

    /* Done with data */
    free(out_image_data);

    /* Done with bitmap_context */
    CGContextRelease(bitmap_context);

    return image_ref;
}