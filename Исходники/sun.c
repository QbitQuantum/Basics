/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d S U N I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadSUNImage reads a SUN image file and returns it.  It allocates
%  the memory necessary for the new Image structure and returns a pointer to
%  the new image.
%
%  The format of the ReadSUNImage method is:
%
%      Image *ReadSUNImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadSUNImage returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or
%      if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/
static Image *ReadSUNImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  Image
    *image;

  int
    bit;

  long
    y;

  register IndexPacket
    *indexes;

  register long
    x;

  register PixelPacket
    *q;

  register long
    i;

  register unsigned char
    *p;

  size_t
    bytes_per_image,
    bytes_per_line,
    count,
    sun_data_length;

  SUNInfo
    sun_info;

  unsigned char
    *sun_data,
    *sun_pixels;

  unsigned int
    index;

  unsigned int
    status;

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  image=AllocateImage(image_info);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == False)
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);
  /*
    Read SUN raster header.
  */
  (void) memset(&sun_info,0,sizeof(sun_info));
  sun_info.magic=ReadBlobMSBLong(image);
  do
  {
    /*
      Verify SUN identifier.
    */
    if (sun_info.magic != 0x59a66a95)
      ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
    sun_info.width=ReadBlobMSBLong(image);
    sun_info.height=ReadBlobMSBLong(image);
    sun_info.depth=ReadBlobMSBLong(image);
    sun_info.length=ReadBlobMSBLong(image);
    sun_info.type=ReadBlobMSBLong(image);
    sun_info.maptype=ReadBlobMSBLong(image);
    sun_info.maplength=ReadBlobMSBLong(image);
    LogSUNInfo(&sun_info);
    if (EOFBlob(image))
      ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
    /*
      Verify that header values are in positive numeric range of a
      32-bit 'int' even though we store them in an unsigned value.
    */
    if ((sun_info.magic | sun_info.width | sun_info.height | sun_info.depth |
         sun_info.type | sun_info.maptype | sun_info.maplength) & (1U << 31))
      ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
    /*
      Verify that we support the image sub-type
    */
    if ((sun_info.type != RT_STANDARD) &&
        (sun_info.type != RT_ENCODED) &&
        (sun_info.type != RT_FORMAT_RGB))
      ThrowReaderException(CoderError,DataEncodingSchemeIsNotSupported,image);
    /*
      Verify that we support the colormap type
    */
    if ((sun_info.maptype != RMT_NONE) &&
        (sun_info.maptype != RMT_EQUAL_RGB))
      ThrowReaderException(CoderError,ColormapTypeNotSupported,image);
    /*
      Insist that map length is zero if there is no colormap.
    */
    if ((sun_info.maptype == RMT_NONE) && (sun_info.maplength != 0))
      ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
    /*
      Insist on a supported depth
    */
    if ((sun_info.depth != 1) &&
        (sun_info.depth != 8) &&
        (sun_info.depth != 24) &&
        (sun_info.depth != 32))
      ThrowReaderException(CorruptImageError,ImproperImageHeader,image);

    image->columns=sun_info.width;
    image->rows=sun_info.height;
    if (((unsigned long) ((long) image->columns) != image->columns) ||
        ((unsigned long) ((long) image->rows) != image->rows))
      ThrowReaderException(CoderError,ImageColumnOrRowSizeIsNotSupported,image);
    if (CheckImagePixelLimits(image, exception) != MagickPass)
        ThrowReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);
    image->depth=sun_info.depth <= 8 ? 8 : QuantumDepth;
    if (sun_info.depth < 24)
      {
        image->colors=sun_info.maplength;
        if (sun_info.maptype == RMT_NONE)
          image->colors=1 << sun_info.depth;
        if (sun_info.maptype == RMT_EQUAL_RGB)
          image->colors=sun_info.maplength/3;
      }

    switch (sun_info.maptype)
    {
      case RMT_NONE:
      {
        if (sun_info.depth < 24)
          {
            /*
              Create linear color ramp.
            */
            if (!AllocateImageColormap(image,image->colors))
              ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,
                image);
          }
        break;
      }
      case RMT_EQUAL_RGB:
      {
        unsigned char
          *sun_colormap;

        /*
          Read SUN raster colormap.
        */
        if (!AllocateImageColormap(image,image->colors))
          ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,
            image);
        sun_colormap=MagickAllocateMemory(unsigned char *,image->colors);
        if (sun_colormap == (unsigned char *) NULL)
          ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,
                               image);
        do
          {
            if (ReadBlob(image,image->colors,(char *) sun_colormap) !=
                image->colors)
              {
                status = MagickFail;
                break;
              }
            for (i=0; i < (long) image->colors; i++)
              image->colormap[i].red=ScaleCharToQuantum(sun_colormap[i]);
            if (ReadBlob(image,image->colors,(char *) sun_colormap) !=
                image->colors)
              {
                status = MagickFail;
                break;
              }
            for (i=0; i < (long) image->colors; i++)
              image->colormap[i].green=ScaleCharToQuantum(sun_colormap[i]);
            if (ReadBlob(image,image->colors,(char *) sun_colormap) !=
                image->colors)
              {
                status = MagickFail;
                break;
              }
            for (i=0; i < (long) image->colors; i++)
              image->colormap[i].blue=ScaleCharToQuantum(sun_colormap[i]);
            break;
          } while (1);
        MagickFreeMemory(sun_colormap);
        if (MagickFail == status)
          ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
        break;
      }
      case RMT_RAW:
      {
        unsigned char
          *sun_colormap;

        /*
          Read SUN raster colormap.
        */
        if (!AllocateImageColormap(image,image->colors))
          ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,
                               image);
        sun_colormap=MagickAllocateMemory(unsigned char *,sun_info.maplength);
        if (sun_colormap == (unsigned char *) NULL)
          ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,
            image);
        if (ReadBlob(image,sun_info.maplength,(char *) sun_colormap) !=
            sun_info.maplength)
          status = MagickFail;
        MagickFreeMemory(sun_colormap);
        if (MagickFail == status)
          ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
        break;
      }
      default:
        ThrowReaderException(CoderError,ColormapTypeNotSupported,image)
    } 
    image->matte=(sun_info.depth == 32);
    image->columns=sun_info.width;
    image->rows=sun_info.height;
    image->depth=8;
    if (sun_info.depth < 8)
      image->depth=sun_info.depth;

    /*
      Compute bytes per line and bytes per image for an unencoded
      image.

      "The width of a scan line is always 16-bits, padded when necessary."
    */
    bytes_per_line=MagickArraySize(sun_info.width,sun_info.depth)/8;
    if ((bytes_per_line != 0) && (sun_info.depth == 1))
      bytes_per_line += sun_info.width % 8 ? 1 : 0;
    if (bytes_per_line != 0)
      bytes_per_line=RoundUpToAlignment(bytes_per_line,2);

    bytes_per_image=MagickArraySize(sun_info.height,bytes_per_line);

    if (bytes_per_line == 0)
      ThrowReaderException(CorruptImageError,ImproperImageHeader,image);

    if (bytes_per_image == 0)
      ThrowReaderException(CorruptImageError,ImproperImageHeader,image);

    if ((sun_info.type == RT_STANDARD) || (sun_info.type == RT_FORMAT_RGB))
      if (bytes_per_image > sun_info.length)
        ThrowReaderException(CorruptImageError,ImproperImageHeader,image);

    if (image_info->ping)
      {
        CloseBlob(image);
        return(image);
      }
    if (sun_info.type == RT_ENCODED)
      sun_data_length=(size_t) sun_info.length;
    else
      sun_data_length=bytes_per_image;
    sun_data=MagickAllocateMemory(unsigned char *,sun_data_length);
    if (sun_data == (unsigned char *) NULL)
      ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,image);
    if ((count=ReadBlob(image,sun_data_length,(char *) sun_data))
        != sun_data_length)
      {
        MagickFreeMemory(sun_data);
        ThrowReaderException(CorruptImageError,UnableToReadImageData,image);
      }
    sun_pixels=sun_data;
    if (sun_info.type == RT_ENCODED)
      {
        /*
          Read run-length encoded raster pixels (padded to 16-bit boundary).
        */
        sun_pixels=MagickAllocateMemory(unsigned char *,bytes_per_image);
        if (sun_pixels == (unsigned char *) NULL)
          ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,
            image);
        status &= DecodeImage(sun_data,sun_data_length,sun_pixels,bytes_per_image);
        MagickFreeMemory(sun_data);
        if (status != MagickPass)
          {
            MagickFreeMemory(sun_pixels);
            ThrowReaderException(CorruptImageError,UnableToRunlengthDecodeImage,image);
          }
      }
    /*
      Convert SUN raster image to pixel packets.
    */
    p=sun_pixels;
    if (sun_info.depth == 1)
      /*
        Bilevel
      */
      for (y=0; y < (long) image->rows; y++)
      {
        q=SetImagePixels(image,0,y,image->columns,1);
        if (q == (PixelPacket *) NULL)
          break;
        indexes=AccessMutableIndexes(image);
        for (x=0; x < ((long) image->columns-7); x+=8)
        {
          for (bit=7; bit >= 0; bit--)
            {
              index=((*p) & (0x01 << bit) ? 0x01 : 0x00);
              indexes[x+7-bit]=index;
              q[x+7-bit]=image->colormap[index];
            }
          p++;
        }
        if ((image->columns % 8) != 0)
          {
            for (bit=7; bit >= (long) (8-(image->columns % 8)); bit--)
              {
                index=((*p) & (0x01 << bit) ? 0x01 : 0x00);
                indexes[x+7-bit]=index;
                q[x+7-bit]=image->colormap[index];
              }
            p++;
          }
        if ((((image->columns/8)+(image->columns % 8 ? 1 : 0)) % 2) != 0)
          p++;
        if (!SyncImagePixels(image))
          break;
        if (image->previous == (Image *) NULL)
          if (QuantumTick(y,image->rows))
            if (!MagickMonitorFormatted(y,image->rows,exception,
                                        LoadImageText,image->filename,
					image->columns,image->rows))
              break;
      }
    else
      if (image->storage_class == PseudoClass)
        {
          /*
            Colormapped
          */
          for (y=0; y < (long) image->rows; y++)
          {
            q=SetImagePixels(image,0,y,image->columns,1);
            if (q == (PixelPacket *) NULL)
              break;
            indexes=AccessMutableIndexes(image);
            for (x=0; x < (long) image->columns; x++)
              {
                index=(*p++);
                VerifyColormapIndex(image,index);
                indexes[x]=index;
                q[x]=image->colormap[index];
              }
            if ((image->columns % 2) != 0)
              p++;
            if (!SyncImagePixels(image))
              break;
            if (image->previous == (Image *) NULL)
              if (QuantumTick(y,image->rows))
                if (!MagickMonitorFormatted(y,image->rows,exception,
                                            LoadImageText,image->filename,
					    image->columns,image->rows))
                  break;
          }
	}
      else
        {
          /*
            (A)BGR or (A)RGB
          */
          for (y=0; y < (long) image->rows; y++)
          {
            q=SetImagePixels(image,0,y,image->columns,1);
            if (q == (PixelPacket *) NULL)
              break;
            for (x=0; x < (long) image->columns; x++)
            {
              if (image->matte)
                q->opacity=(Quantum) (MaxRGB-ScaleCharToQuantum(*p++));
              if (sun_info.type == RT_STANDARD)
                {
                  q->blue=ScaleCharToQuantum(*p++);
                  q->green=ScaleCharToQuantum(*p++);
                  q->red=ScaleCharToQuantum(*p++);
                }
              else
                {
                  q->red=ScaleCharToQuantum(*p++);
                  q->green=ScaleCharToQuantum(*p++);
                  q->blue=ScaleCharToQuantum(*p++);
                }
              if (image->colors != 0)
                {
                  q->red=image->colormap[q->red].red;
                  q->green=image->colormap[q->green].green;
                  q->blue=image->colormap[q->blue].blue;
                }
              q++;
            }
            if (((image->columns % 2) != 0) && (image->matte == False))
              p++;
            if (!SyncImagePixels(image))
              break;
            if (image->previous == (Image *) NULL)
              if (QuantumTick(y,image->rows))
                if (!MagickMonitorFormatted(y,image->rows,exception,
                                            LoadImageText,image->filename,
					    image->columns,image->rows))
                  break;
          }
	}
    MagickFreeMemory(sun_pixels);
    if (EOFBlob(image))
      {
        ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,
          image->filename);
        break;
      }
    /*
      Proceed to next image.
    */
    if (image_info->subrange != 0)
      if (image->scene >= (image_info->subimage+image_info->subrange-1))
        break;
    sun_info.magic=ReadBlobMSBLong(image);
    if (sun_info.magic == 0x59a66a95)
      {
        /*
          Allocate next image structure.
        */
        AllocateNextImage(image_info,image);
        if (image->next == (Image *) NULL)
          {
            DestroyImageList(image);
            return((Image *) NULL);
          }
        image=SyncNextImageInList(image);
        if (!MagickMonitorFormatted(TellBlob(image),GetBlobSize(image),
                                    exception,LoadImagesText,
                                    image->filename))
          break;
      }
  } while (sun_info.magic == 0x59a66a95);