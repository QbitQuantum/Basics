//=============================================================================
//  This routine loads a 256 color PCX file. The file can be a standalone
// PCX file or it can be combined with a resource. If the data is part
// of a resource, the rshandle flag will be set. The bitmap data is read
// into a buffer that is the size of the bitmap + 4 bytes. The first 4
// bytes in the buffer contain the width and height of the bitmap.
//=============================================================================
unsigned char *AckReadPCX(char *filename)
{
    int32_t i;
    int mode=NORMAL,nbytes;
    char abyte,*p;
    short   handle;
    PcxFile *pcx;

pcx = &pcxGlobal;
// Open the file since no resource is open.
if (!rsHandle)
    {
    handle = _lopen(filename,OF_READ); // Open the file for reading
    if (handle == HFILE_ERROR) // Make sure file is opened
        {
        ErrorCode = ERR_BADFILE;
        return NULL;
        }
    }
else // Use the resource instead
    {
    handle = rsHandle; // Use the handle to the resource file
    // Move to the location in the resource where the data is stored
    _llseek(handle,(int)(rbaTable[(int64_t)filename]),SEEK_SET);
    }


_lread(handle,&pcx->hdr,sizeof(PcxHeader)); // Read in the header data
pcx->width=1+pcx->hdr.xmax-pcx->hdr.xmin;   // Store width and height
pcx->height=1+pcx->hdr.ymax-pcx->hdr.ymin;
// Store number of bytes used for image
pcx->imagebytes=(unsigned int)(pcx->width*pcx->height);

// Make sure bitmap is correct size
if (pcx->imagebytes > PCX_MAX_SIZE)
    {
    if (!rsHandle)
        _lclose(handle);
    ErrorCode = ERR_INVALIDFORM;
    return(NULL);
    }

// Allocate size for bitmap. 4 extra bytes are included to give
// room to store bitmap width and height info.
pcx->bitmap=(UCHAR*)AckMalloc(pcx->imagebytes+4);

if (pcx->bitmap == NULL)    // Make sure memory is allocated
    {
    if (!rsHandle)
        _lclose(handle);
    ErrorCode = ERR_NOMEMORY;
    return(NULL);
    }
p=(char*)(&pcx->bitmap[4]);      // Get address of data area

// Loop and read in pixel data for bitmap
// Uses RLE decompression
for (i=0;i<pcx->imagebytes;i++)
    {
    if (mode == NORMAL)     // Normal color read mode
        {
        _lread(handle,&abyte,1);    // Read in pixel value from file
        if ((unsigned char)abyte > 0xbf) // Value read > 191
            {
            nbytes=abyte & 0x3f;    // Get the RLE counter
            _lread(handle,&abyte,1);
            if (--nbytes > 0)       // Is counter greater than 1?
                mode=RLE;           // Yes, we're in RLE mode
            }
        }
    else if (--nbytes == 0)         // When counter down to 0
            mode=NORMAL;            // return to color read mode
    *p++=abyte;                     // Store pixel value
    }

// Get palette from PCX file, 256 color palette store 768 bytes from
// end of file. For a resource file we need to find the position where
// the next file starts and then backup 768 bytes
if (rsHandle)
    _llseek(handle,(int)(rbaTable[(int64_t)(filename + 1)])-768,SEEK_CUR);
else
    _llseek(handle,-768,SEEK_END);

// Store the palette data in our global colordat array
_lread(handle,colordat,768);
p=(char*)colordat;
for (i=0;i<768;i++)            // bit shift palette
    *p++ = *p >> 2;

if (!rsHandle)                  // Close pcx file if not using a resource
    _lclose(handle);

// Add in bitmap width and height to first 4 bytes of buffer
p = (char*)pcx->bitmap;
(*(short *)p) = pcx->width;
p += sizeof(short);
(*(short *)p) = pcx->height;

return(pcx->bitmap);         // return bitmap buffer
}