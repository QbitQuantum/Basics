    unsigned  
    VLC::setup_video(char * chroma, unsigned *width, unsigned *height, unsigned *pitches, unsigned *lines) {
        AC_DEBUG << "VLC requesting " << chroma << " " << *width << "x" << *height << " for " << _mediaURL;

        // TODO: we could use our YUV shader here
        AC_INFO << "Can't render " << chroma << ", asking libvlc to convert to RGB";
        memcpy(chroma, "RV24", 4);  
        _rasterEncoding = BGR;
        
        _myFrameWidth = *width;
        _myFrameHeight = *height;
        (*pitches) = getBytesRequired(_myFrameWidth, _rasterEncoding);
        (*lines) = _myFrameHeight;
        
        setPixelFormat(_rasterEncoding);
        setFrameHeight(_myFrameHeight);
        setFrameWidth(_myFrameWidth);

        return 1; // one color plane
    }