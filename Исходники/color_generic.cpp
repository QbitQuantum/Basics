bool
ImageBufAlgo::colorconvert (ImageBuf &dst, const ImageBuf &src,
    const ColorProcessor* processor,
    bool unpremult)
{
    // If the processor is NULL, return false (error)
    if (!processor)
        return false;
    
    ImageSpec dstspec = dst.spec();
    
    std::vector<float> scanline(dstspec.width*4, 0.0f);
    
    // Only process up to, and including, the first 4 channels.
    // This does let us process images with fewer than 4 channels, which is the intent
    // FIXME: Instead of loading the first 4 channels, obey dstspec.alpha_channel index
    //        (but first validate that the index is set properly for normal formats)
    
    int channelsToCopy = std::min (4, dstspec.nchannels);
    
    // Walk through all data in our buffer. (i.e., crop or overscan)
    // FIXME: What about the display window?  Should this actually promote
    // the datawindow to be union of data + display? This is useful if
    // the color of black moves.  (In which case non-zero sections should
    // now be promoted).  Consider the lin->log of a roto element, where
    // black now moves to non-black
    //
    // FIXME: Use the ImageBuf::ConstIterator<T,T> s (src);   s.isValid()
    // idiom for traversal instead, to allow for more efficient tile access
    // iteration order
    
    float * dstPtr = NULL;
    const float fltmin = std::numeric_limits<float>::min();
    
    for (int k = dstspec.z; k < dstspec.z+dstspec.depth; k++) {
        for (int j = dstspec.y; j <  dstspec.y+dstspec.height; j++) {
            
            // Load the scanline
            dstPtr = &scanline[0];
            for (int i = dstspec.x; i < dstspec.x+dstspec.width ; i++) {
                src.getpixel (i, j, dstPtr, channelsToCopy);
                dstPtr += 4;
            }
            
            // Optionally unpremult
            if ((channelsToCopy>=4) && unpremult) {
                float alpha = 0.0;
                for (int i=0; i<dstspec.width; ++i) {
                    alpha = scanline[4*i+3];
                    if (alpha > fltmin) {
                        scanline[4*i+0] /= alpha;
                        scanline[4*i+1] /= alpha;
                        scanline[4*i+2] /= alpha;
                    }
                }
            }
            
            // Apply the color transformation in place
            // This is always an rgba float image, due to the conversion above.
            for(int i=0; i<dstspec.width; ++i)
            {
                scanline[4*i+0] = (*processor->t2)((*processor->t1)(scanline[4*i+0]));
                scanline[4*i+1] = (*processor->t2)((*processor->t1)(scanline[4*i+1]));
                scanline[4*i+2] = (*processor->t2)((*processor->t1)(scanline[4*i+2]));
            }
            
            // Optionally premult
            if ((channelsToCopy>=4) && unpremult) {
                float alpha = 0.0;
                for (int i=0; i<dstspec.width; ++i) {
                    alpha = scanline[4*i+3];
                    if (alpha > fltmin) {
                        scanline[4*i+0] *= alpha;
                        scanline[4*i+1] *= alpha;
                        scanline[4*i+2] *= alpha;
                    }
                }
            }
            
            // Store the scanline
            dstPtr = &scanline[0];
            for (int i = dstspec.x; i < dstspec.x+dstspec.width ; i++) {
                dst.setpixel (i, j, dstPtr, channelsToCopy);
                dstPtr += 4;
            }
        }
    }
    
    return true;
}