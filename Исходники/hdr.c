static MagickBooleanType WriteHDRImage(const ImageInfo *image_info,Image *image)
{
  char
    header[MaxTextExtent];

  const char
    *property;

  MagickBooleanType
    status;

  register const PixelPacket
    *p;

  register ssize_t
    i,
    x;

  size_t
    length;

  ssize_t
    count,
    y;

  unsigned char
    pixel[4],
    *pixels;

  /*
    Open output image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == MagickFalse)
    return(status);
  if (IsRGBColorspace(image->colorspace) == MagickFalse)
    (void) TransformImageColorspace(image,sRGBColorspace);
  /*
    Write header.
  */
  (void) ResetMagickMemory(header,' ',MaxTextExtent);
  length=CopyMagickString(header,"#?RGBE\n",MaxTextExtent);
  (void) WriteBlob(image,length,(unsigned char *) header);
  property=GetImageProperty(image,"comment");
  if ((property != (const char *) NULL) &&
      (strchr(property,'\n') == (char *) NULL))
    {
      count=FormatLocaleString(header,MaxTextExtent,"#%s\n",property);
      (void) WriteBlob(image,(size_t) count,(unsigned char *) header);
    }
  property=GetImageProperty(image,"hdr:exposure");
  if (property != (const char *) NULL)
    {
      count=FormatLocaleString(header,MaxTextExtent,"EXPOSURE=%g\n",
        atof(property));
      (void) WriteBlob(image,(size_t) count,(unsigned char *) header);
    }
  if (image->gamma != 0.0)
    {
      count=FormatLocaleString(header,MaxTextExtent,"GAMMA=%g\n",image->gamma);
      (void) WriteBlob(image,(size_t) count,(unsigned char *) header);
    }
  count=FormatLocaleString(header,MaxTextExtent,
    "PRIMARIES=%g %g %g %g %g %g %g %g\n",
    image->chromaticity.red_primary.x,image->chromaticity.red_primary.y,
    image->chromaticity.green_primary.x,image->chromaticity.green_primary.y,
    image->chromaticity.blue_primary.x,image->chromaticity.blue_primary.y,
    image->chromaticity.white_point.x,image->chromaticity.white_point.y);
  (void) WriteBlob(image,(size_t) count,(unsigned char *) header);
  length=CopyMagickString(header,"FORMAT=32-bit_rle_rgbe\n\n",MaxTextExtent);
  (void) WriteBlob(image,length,(unsigned char *) header);
  count=FormatLocaleString(header,MaxTextExtent,"-Y %.20g +X %.20g\n",
    (double) image->rows,(double) image->columns);
  (void) WriteBlob(image,(size_t) count,(unsigned char *) header);
  /*
    Write HDR pixels.
  */
  pixels=(unsigned char *) AcquireQuantumMemory(image->columns,4*
    sizeof(*pixels));
  if (pixels == (unsigned char *) NULL)
    ThrowWriterException(ResourceLimitError,"MemoryAllocationFailed");
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    p=GetVirtualPixels(image,0,y,image->columns,1,&image->exception);
    if (p == (const PixelPacket *) NULL)
      break;
    if ((image->columns >= 8) && (image->columns <= 0x7ffff))
      {
        pixel[0]=2;
        pixel[1]=2;
        pixel[2]=(unsigned char) (image->columns >> 8);
        pixel[3]=(unsigned char) (image->columns & 0xff);
        count=WriteBlob(image,4*sizeof(*pixel),pixel);
        if (count != (ssize_t) (4*sizeof(*pixel)))
          break;
      }
    i=0;
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      double
        gamma;

      pixel[0]=0;
      pixel[1]=0;
      pixel[2]=0;
      pixel[3]=0;
      gamma=QuantumScale*GetPixelRed(p);
      if ((QuantumScale*GetPixelGreen(p)) > gamma)
        gamma=QuantumScale*GetPixelGreen(p);
      if ((QuantumScale*GetPixelBlue(p)) > gamma)
        gamma=QuantumScale*GetPixelBlue(p);
      if (gamma > MagickEpsilon)
        {
          int
            exponent;

          gamma=frexp(gamma,&exponent)*256.0/gamma;
          pixel[0]=(unsigned char) (gamma*QuantumScale*GetPixelRed(p));
          pixel[1]=(unsigned char) (gamma*QuantumScale*GetPixelGreen(p));
          pixel[2]=(unsigned char) (gamma*QuantumScale*GetPixelBlue(p));
          pixel[3]=(unsigned char) (exponent+128);
        }
      if ((image->columns >= 8) && (image->columns <= 0x7ffff))
        {
          pixels[x]=pixel[0];
          pixels[x+image->columns]=pixel[1];
          pixels[x+2*image->columns]=pixel[2];
          pixels[x+3*image->columns]=pixel[3];
        }
      else
        {
          pixels[i++]=pixel[0];
          pixels[i++]=pixel[1];
          pixels[i++]=pixel[2];
          pixels[i++]=pixel[3];
        }
      p++;
    }
    if ((image->columns >= 8) && (image->columns <= 0x7ffff))
      {
        for (i=0; i < 4; i++)
          length=HDRWriteRunlengthPixels(image,&pixels[i*image->columns]);
      }
    else
      {
        count=WriteBlob(image,4*image->columns*sizeof(*pixel),pixel);
        if (count != (ssize_t) (4*image->columns*sizeof(*pixel)))
          break;
      }
    status=SetImageProgress(image,SaveImageTag,(MagickOffsetType) y,
      image->rows);
    if (status == MagickFalse)
      break;
  }