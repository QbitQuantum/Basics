    size_t BitmapEncoding::compress(void* dst, const ConstChunk& chunk, size_t size) 
    {

#ifdef FORMAT_SENSITIVE_COMPRESSORS
        if (chunk.isRLE()) { return size; }
        Bitmap bitmap;
        return bitmap.compress(dst, chunk, size);
#else
        return size;
#endif
    }