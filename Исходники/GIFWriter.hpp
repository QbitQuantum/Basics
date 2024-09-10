// write the image header, LZW-compress and write out the image
inline void GifWriteLzwImage(s3d::IWriter* f, uint8_t* image, uint32_t left, uint32_t top, uint32_t width, uint32_t height, uint32_t delay, GifPalette* pPal, GifEncodingMode mode)
{
    // graphics control extension
    FPutc(0x21, f);
    FPutc(0xf9, f);
    FPutc(0x04, f);
	FPutc(mode == GifEncodingMode::AnimatedRGBA? 0x09 : 0x05, f); // leave prev frame in place, this frame has transparency
    FPutc(delay & 0xff, f);
    FPutc((delay >> 8) & 0xff, f);
    FPutc(kGifTransIndex, f); // transparent color index
    FPutc(0, f);
    
    FPutc(0x2c, f); // image descriptor block
    
    FPutc(left & 0xff, f);           // corner of image in canvas space
    FPutc((left >> 8) & 0xff, f);
    FPutc(top & 0xff, f);
    FPutc((top >> 8) & 0xff, f);
    
    FPutc(width & 0xff, f);          // width and height of image
    FPutc((width >> 8) & 0xff, f);
    FPutc(height & 0xff, f);
    FPutc((height >> 8) & 0xff, f);
    
    //FPutc(0, f); // no local color table, no transparency
    //FPutc(0x80, f); // no local color table, but transparency
    
    FPutc((uint8_t)(0x80 + pPal->bitDepth-1), f); // local color table present, 2 ^ bitDepth entries
    GifWritePalette(pPal, f);
    
    const int minCodeSize = pPal->bitDepth;
    const uint32_t clearCode = 1 << pPal->bitDepth;
    
    FPutc((uint8_t)minCodeSize, f); // min code size 8 bits
    
    GifLzwNode* codetree = (GifLzwNode*)GIF_TEMP_MALLOC(sizeof(GifLzwNode)*4096);
    
	::memset(codetree, 0, sizeof(GifLzwNode) * 4096);

    int32_t curCode = -1;
	uint32_t codeSize = (uint32_t)minCodeSize + 1;
    uint32_t maxCode = clearCode+1;
    
    GifBitStatus stat;
    stat.byte = 0;
    stat.bitIndex = 0;
    stat.chunkIndex = 0;
    
    GifWriteCode(f, stat, clearCode, codeSize);  // start with a fresh LZW dictionary
    
	for (uint32_t yy = 0; yy<height; ++yy)
    {
		for (uint32_t xx = 0; xx<width; ++xx)
        {
			uint8_t nextValue = image[(yy*width + xx) * 4 + 3];
            
            // "loser mode" - no compression, every single code is followed immediately by a clear
            //WriteCode( f, stat, nextValue, codeSize );
            //WriteCode( f, stat, 256, codeSize );
            
            if( curCode < 0 )
            {
                // first value in a new run
                curCode = nextValue;
            }
            else if( codetree[curCode].m_next[nextValue] )
            {
                // current run already in the dictionary
                curCode = codetree[curCode].m_next[nextValue];
            }
            else
            {
                // finish the current run, write a code
                GifWriteCode( f, stat, (uint32_t)curCode, codeSize );
                
                // insert the new run into the dictionary
                codetree[curCode].m_next[nextValue] = (uint16_t)++maxCode;
                
				if (maxCode >= (1ul << codeSize))
                {
                    // dictionary entry count has broken a size barrier,
                    // we need more bits for codes
                    codeSize++;
                }
                if( maxCode == 4095 )
                {
                    // the dictionary is full, clear it out and begin anew
                    GifWriteCode(f, stat, clearCode, codeSize); // clear tree
                    
					::memset(codetree, 0, sizeof(GifLzwNode) * 4096);
                    //bzero(codetree, sizeof(GifLzwNode)*4096);

                    codeSize = (uint32_t)(minCodeSize + 1);
                    maxCode = clearCode+1;
                }
                
                curCode = nextValue;
            }
        }
    }
    
    // compression footer
    GifWriteCode(f, stat, (uint32_t)curCode, codeSize);
    GifWriteCode(f, stat, clearCode, codeSize);
    GifWriteCode(f, stat, clearCode + 1, (uint32_t)minCodeSize + 1);
    
    // write out the last partial chunk
    while( stat.bitIndex ) GifWriteBit(stat, 0);
    if( stat.chunkIndex ) GifWriteChunk(f, stat);
    
    FPutc(0, f); // image block terminator
    
    GIF_TEMP_FREE(codetree);
}