MagickExport MagickBooleanType IdentifyImage(Image *image,FILE *file,
  const MagickBooleanType verbose)
{
#define IdentifyFormat "    %s:\n      min: " QuantumFormat  \
  " (%g)\n      max: " QuantumFormat " (%g)\n"  \
  "      mean: %g (%g)\n      standard deviation: %g (%g)\n"  \
  "      kurtosis: %g\n      skewness: %g\n"

  char
    color[MaxTextExtent],
    format[MaxTextExtent],
    key[MaxTextExtent];

  ColorspaceType
    colorspace;

  const char
    *artifact,
    *name,
    *property,
    *registry,
    *value;

  const MagickInfo
    *magick_info;

  const PixelPacket
    *pixels;

  double
    elapsed_time,
    user_time;

  ExceptionInfo
    *exception;

  ImageType
    type;

  long
    y;

  MagickBooleanType
    ping;

  register long
    i,
    x;

  unsigned long
    scale;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  if (file == (FILE *) NULL)
    file=stdout;
  *format='\0';
  elapsed_time=GetElapsedTime(&image->timer);
  user_time=GetUserTime(&image->timer);
  GetTimerInfo(&image->timer);
  if (verbose == MagickFalse)
    {
      /*
        Display summary info about the image.
      */
      if (*image->magick_filename != '\0')
        if (LocaleCompare(image->magick_filename,image->filename) != 0)
          (void) fprintf(file,"%s=>",image->magick_filename);
       if ((GetPreviousImageInList(image) == (Image *) NULL) &&
           (GetNextImageInList(image) == (Image *) NULL) && (image->scene == 0))
        (void) fprintf(file,"%s ",image->filename);
      else
        (void) fprintf(file,"%s[%lu] ",image->filename,image->scene);
      (void) fprintf(file,"%s ",image->magick);
      if ((image->magick_columns != 0) || (image->magick_rows != 0))
        if ((image->magick_columns != image->columns) ||
            (image->magick_rows != image->rows))
          (void) fprintf(file,"%lux%lu=>",image->magick_columns,
            image->magick_rows);
      (void) fprintf(file,"%lux%lu ",image->columns,image->rows);
      if ((image->page.width != 0) || (image->page.height != 0) ||
          (image->page.x != 0) || (image->page.y != 0))
        (void) fprintf(file,"%lux%lu%+ld%+ld ",image->page.width,
          image->page.height,image->page.x,image->page.y);
      (void) fprintf(file,"%lu-bit ",image->depth);
      if (image->type != UndefinedType)
        (void) fprintf(file,"%s ",MagickOptionToMnemonic(MagickTypeOptions,
          (long) image->type));
      if (image->storage_class == DirectClass)
        {
          (void) fprintf(file,"DirectClass ");
          if (image->total_colors != 0)
            {
              (void) FormatMagickSize(image->total_colors,MagickFalse,format);
              (void) fprintf(file,"%s ",format);
            }
        }
      else
        if (image->total_colors <= image->colors)
          (void) fprintf(file,"PseudoClass %luc ",image->colors);
        else
          (void) fprintf(file,"PseudoClass %lu=>%luc ",image->total_colors,
            image->colors);
      if (image->error.mean_error_per_pixel != 0.0)
        (void) fprintf(file,"%ld/%f/%fdb ",(long)
          (image->error.mean_error_per_pixel+0.5),
          image->error.normalized_mean_error,
          image->error.normalized_maximum_error);
      if (GetBlobSize(image) != 0)
        {
          (void) FormatMagickSize(GetBlobSize(image),MagickFalse,format);
          (void) fprintf(file,"%s ",format);
        }
      (void) fprintf(file,"%0.3fu %ld:%02ld.%03ld",user_time,(long)
        (elapsed_time/60.0),(long) floor(fmod(elapsed_time,60.0)),
        (long) (1000.0*(elapsed_time-floor(elapsed_time))));
      (void) fprintf(file,"\n");
      (void) fflush(file);
      return(ferror(file) != 0 ? MagickFalse : MagickTrue);
    }
  /*
    Display verbose info about the image.
  */
  exception=AcquireExceptionInfo();
  pixels=GetVirtualPixels(image,0,0,1,1,exception);
  exception=DestroyExceptionInfo(exception);
  ping=pixels == (const PixelPacket *) NULL ? MagickTrue : MagickFalse;
  type=GetImageType(image,&image->exception);
  (void) SignatureImage(image);
  (void) fprintf(file,"Image: %s\n",image->filename);
  if (*image->magick_filename != '\0')
    if (LocaleCompare(image->magick_filename,image->filename) != 0)
      {
        char
          filename[MaxTextExtent];

        GetPathComponent(image->magick_filename,TailPath,filename);
        (void) fprintf(file,"  Base filename: %s\n",filename);
      }
  magick_info=GetMagickInfo(image->magick,&image->exception);
  if ((magick_info == (const MagickInfo *) NULL) ||
      (*GetMagickDescription(magick_info) == '\0'))
    (void) fprintf(file,"  Format: %s\n",image->magick);
  else
    (void) fprintf(file,"  Format: %s (%s)\n",image->magick,
      GetMagickDescription(magick_info));
  (void) fprintf(file,"  Class: %s\n",MagickOptionToMnemonic(MagickClassOptions,
    (long) image->storage_class));
  (void) fprintf(file,"  Geometry: %lux%lu%+ld%+ld\n",image->columns,
    image->rows,image->tile_offset.x,image->tile_offset.y);
  if ((image->magick_columns != 0) || (image->magick_rows != 0))
    if ((image->magick_columns != image->columns) ||
        (image->magick_rows != image->rows))
      (void) fprintf(file,"  Base geometry: %lux%lu\n",image->magick_columns,
        image->magick_rows);
  if ((image->x_resolution != 0.0) && (image->y_resolution != 0.0))
    {
      (void) fprintf(file,"  Resolution: %gx%g\n",image->x_resolution,
        image->y_resolution);
      (void) fprintf(file,"  Print size: %gx%g\n",(double) image->columns/
        image->x_resolution,(double) image->rows/image->y_resolution);
    }
  (void) fprintf(file,"  Units: %s\n",MagickOptionToMnemonic(
    MagickResolutionOptions,(long) image->units));
  (void) fprintf(file,"  Type: %s\n",MagickOptionToMnemonic(MagickTypeOptions,
    (long) type));
  if (image->type != UndefinedType)
    (void) fprintf(file,"  Base type: %s\n",MagickOptionToMnemonic(
      MagickTypeOptions,(long) image->type));
  (void) fprintf(file,"  Endianess: %s\n",MagickOptionToMnemonic(
    MagickEndianOptions,(long) image->endian));
  /*
    Detail channel depth and extrema.
  */
  (void) fprintf(file,"  Colorspace: %s\n",MagickOptionToMnemonic(
    MagickColorspaceOptions,(long) image->colorspace));
  if (ping == MagickFalse)
    {
      ChannelStatistics
        *channel_statistics;

      unsigned long
        depth;

      depth=GetImageDepth(image,&image->exception);
      if (image->depth == depth)
        (void) fprintf(file,"  Depth: %lu-bit\n",image->depth);
      else
        (void) fprintf(file,"  Depth: %lu/%lu-bit\n",image->depth,depth);
      channel_statistics=GetImageChannelStatistics(image,&image->exception);
      (void) fprintf(file,"  Channel depth:\n");
      colorspace=image->colorspace;
      if (IsGrayImage(image,&image->exception) != MagickFalse)
        colorspace=GRAYColorspace;
      switch (colorspace)
      {
        case RGBColorspace:
        default:
        {
          (void) fprintf(file,"    red: %lu-bit\n",
            channel_statistics[RedChannel].depth);
          (void) fprintf(file,"    green: %lu-bit\n",
            channel_statistics[GreenChannel].depth);
          (void) fprintf(file,"    blue: %lu-bit\n",
            channel_statistics[BlueChannel].depth);
          if (image->matte != MagickFalse)
            (void) fprintf(file,"    alpha: %lu-bit\n",
              channel_statistics[OpacityChannel].depth);
          break;
        }
        case CMYKColorspace:
        {
          (void) fprintf(file,"    cyan: %lu-bit\n",
            channel_statistics[CyanChannel].depth);
          (void) fprintf(file,"    magenta: %lu-bit\n",
            channel_statistics[MagentaChannel].depth);
          (void) fprintf(file,"    yellow: %lu-bit\n",
            channel_statistics[YellowChannel].depth);
          (void) fprintf(file,"    black: %lu-bit\n",
            channel_statistics[BlackChannel].depth);
          if (image->matte != MagickFalse)
            (void) fprintf(file,"    alpha: %lu-bit\n",
              channel_statistics[OpacityChannel].depth);
          break;
        }
        case GRAYColorspace:
        {
          (void) fprintf(file,"    gray: %lu-bit\n",
            channel_statistics[GrayChannel].depth);
          if (image->matte != MagickFalse)
            (void) fprintf(file,"    alpha: %lu-bit\n",
              channel_statistics[OpacityChannel].depth);
          break;
        }
      }
      scale=1;
      if (image->depth <= MAGICKCORE_QUANTUM_DEPTH)
        scale=QuantumRange/((unsigned long) QuantumRange >> ((unsigned long)
          MAGICKCORE_QUANTUM_DEPTH-image->depth));
      (void) fprintf(file,"  Channel statistics:\n");
      switch (colorspace)
      {
        case RGBColorspace:
        default:
        {
          (void) fprintf(file,IdentifyFormat,"red",(Quantum)
            (channel_statistics[RedChannel].minima/scale),(double)
            channel_statistics[RedChannel].minima/(double) QuantumRange,
            (Quantum) (channel_statistics[RedChannel].maxima/scale),(double)
            channel_statistics[RedChannel].maxima/(double) QuantumRange,
            channel_statistics[RedChannel].mean/(double) scale,
            channel_statistics[RedChannel].mean/(double) QuantumRange,
            channel_statistics[RedChannel].standard_deviation/(double) scale,
            channel_statistics[RedChannel].standard_deviation/(double)
            QuantumRange,channel_statistics[RedChannel].kurtosis,
            channel_statistics[RedChannel].skewness);
          (void) fprintf(file,IdentifyFormat,"green",(Quantum)
            (channel_statistics[GreenChannel].minima/scale),(double)
            channel_statistics[GreenChannel].minima/(double) QuantumRange,
            (Quantum) (channel_statistics[GreenChannel].maxima/scale),(double)
            channel_statistics[GreenChannel].maxima/(double) QuantumRange,
            channel_statistics[GreenChannel].mean/(double) scale,
            channel_statistics[GreenChannel].mean/(double) QuantumRange,
            channel_statistics[GreenChannel].standard_deviation/(double) scale,
            channel_statistics[GreenChannel].standard_deviation/(double)
            QuantumRange,
            channel_statistics[GreenChannel].kurtosis,
            channel_statistics[GreenChannel].skewness);
          (void) fprintf(file,IdentifyFormat,"blue",(Quantum)
            (channel_statistics[BlueChannel].minima/scale),(double)
            channel_statistics[BlueChannel].minima/(double) QuantumRange,
            (Quantum) (channel_statistics[BlueChannel].maxima/scale),(double)
            channel_statistics[BlueChannel].maxima/(double) QuantumRange,
            channel_statistics[BlueChannel].mean/(double) scale,
            channel_statistics[BlueChannel].mean/(double) QuantumRange,
            channel_statistics[BlueChannel].standard_deviation/(double) scale,
            channel_statistics[BlueChannel].standard_deviation/(double)
            QuantumRange,channel_statistics[BlueChannel].kurtosis,
            channel_statistics[BlueChannel].skewness);
          break;
        }
        case CMYKColorspace:
        {
          (void) fprintf(file,IdentifyFormat,"cyan",(Quantum)
            (channel_statistics[CyanChannel].minima/scale),(double)
            channel_statistics[CyanChannel].minima/(double) QuantumRange,
            (Quantum) (channel_statistics[CyanChannel].maxima/scale),(double)
            channel_statistics[CyanChannel].maxima/(double) QuantumRange,
            channel_statistics[CyanChannel].mean/(double) scale,
            channel_statistics[CyanChannel].mean/(double) QuantumRange,
            channel_statistics[CyanChannel].standard_deviation/(double) scale,
            channel_statistics[CyanChannel].standard_deviation/(double)
            QuantumRange,channel_statistics[CyanChannel].kurtosis,
            channel_statistics[CyanChannel].skewness);
          (void) fprintf(file,IdentifyFormat,"magenta",(Quantum)
            (channel_statistics[MagentaChannel].minima/scale),(double)
            channel_statistics[MagentaChannel].minima/(double) QuantumRange,
            (Quantum) (channel_statistics[MagentaChannel].maxima/scale),(double)
            channel_statistics[MagentaChannel].maxima/(double) QuantumRange,
            channel_statistics[MagentaChannel].mean/(double) scale,
            channel_statistics[MagentaChannel].mean/(double) QuantumRange,
            channel_statistics[MagentaChannel].standard_deviation/(double)
            scale,channel_statistics[MagentaChannel].standard_deviation/(double)
            QuantumRange,channel_statistics[MagentaChannel].kurtosis,
            channel_statistics[MagentaChannel].skewness);
          (void) fprintf(file,IdentifyFormat,"yellow",(Quantum)
            (channel_statistics[YellowChannel].minima/scale),(double)
            channel_statistics[YellowChannel].minima/(double) QuantumRange,
            (Quantum) (channel_statistics[YellowChannel].maxima/scale),(double)
            channel_statistics[YellowChannel].maxima/(double) QuantumRange,
            channel_statistics[YellowChannel].mean/(double) scale,
            channel_statistics[YellowChannel].mean/(double) QuantumRange,
            channel_statistics[YellowChannel].standard_deviation/(double) scale,
            channel_statistics[YellowChannel].standard_deviation/(double)
            QuantumRange,channel_statistics[YellowChannel].kurtosis,
            channel_statistics[YellowChannel].skewness);
          (void) fprintf(file,IdentifyFormat,"black",(Quantum)
            (channel_statistics[BlackChannel].minima/scale),(double)
            channel_statistics[BlackChannel].minima/(double) QuantumRange,
            (Quantum) (channel_statistics[BlackChannel].maxima/scale),(double)
            channel_statistics[BlackChannel].maxima/(double) QuantumRange,
            channel_statistics[BlackChannel].mean/(double) scale,
            channel_statistics[BlackChannel].mean/(double) QuantumRange,
            channel_statistics[BlackChannel].standard_deviation/(double) scale,
            channel_statistics[BlackChannel].standard_deviation/(double)
            QuantumRange,channel_statistics[BlackChannel].kurtosis,
            channel_statistics[BlackChannel].skewness);
          break;
        }
        case GRAYColorspace:
        {
          (void) fprintf(file,IdentifyFormat,"gray",(Quantum)
            (channel_statistics[GrayChannel].minima/scale),(double)
            channel_statistics[GrayChannel].minima/(double) QuantumRange,
            (Quantum) (channel_statistics[GrayChannel].maxima/scale),(double)
            channel_statistics[GrayChannel].maxima/(double) QuantumRange,
            channel_statistics[GrayChannel].mean/(double) scale,
            channel_statistics[GrayChannel].mean/(double) QuantumRange,
            channel_statistics[GrayChannel].standard_deviation/(double) scale,
            channel_statistics[GrayChannel].standard_deviation/(double)
            QuantumRange,channel_statistics[GrayChannel].kurtosis,
            channel_statistics[GrayChannel].skewness);
          break;
        }
      }
      if (image->matte != MagickFalse)
        (void) fprintf(file,IdentifyFormat,"alpha",(Quantum)
          ((QuantumRange-channel_statistics[AlphaChannel].maxima)/scale),
          (double) (QuantumRange-channel_statistics[AlphaChannel].maxima)/
          (double) QuantumRange, (Quantum) ((QuantumRange-
          channel_statistics[AlphaChannel].minima)/scale),(double)
          (QuantumRange-channel_statistics[AlphaChannel].minima)/(double)
          QuantumRange,(QuantumRange-channel_statistics[AlphaChannel].mean)/
          (double) scale,(QuantumRange-channel_statistics[AlphaChannel].mean)/
          (double) QuantumRange,
          channel_statistics[AlphaChannel].standard_deviation/(double) scale,
          channel_statistics[AlphaChannel].standard_deviation/(double)
          QuantumRange,channel_statistics[AlphaChannel].kurtosis,
          channel_statistics[AlphaChannel].skewness);
      if (colorspace != GRAYColorspace)
        {
          (void) fprintf(file,"  Image statistics:\n");
          (void) fprintf(file,IdentifyFormat,"Overall",(Quantum)
            (channel_statistics[AllChannels].minima/scale),(double)
            channel_statistics[AllChannels].minima/(double) QuantumRange,
            (Quantum) (channel_statistics[AllChannels].maxima/scale),(double)
            channel_statistics[AllChannels].maxima/(double) QuantumRange,
            channel_statistics[AllChannels].mean/(double) scale,
            channel_statistics[AllChannels].mean/(double) QuantumRange,
            channel_statistics[AllChannels].standard_deviation/(double) scale,
            channel_statistics[AllChannels].standard_deviation/(double)
            QuantumRange,channel_statistics[AllChannels].kurtosis,
            channel_statistics[AllChannels].skewness);
        }
      channel_statistics=(ChannelStatistics *) RelinquishMagickMemory(
        channel_statistics);
      if (image->colorspace == CMYKColorspace)
        (void) fprintf(file,"  Total ink density: %.0f%%\n",100.0*
          GetImageTotalInkDensity(image)/(double) QuantumRange);
      x=0;
      if (image->matte != MagickFalse)
        {
          register const IndexPacket
            *indexes;

          register const PixelPacket
            *p;

          p=(PixelPacket *) NULL;
          indexes=(IndexPacket *) NULL;
          for (y=0; y < (long) image->rows; y++)
          {
            p=GetVirtualPixels(image,0,y,image->columns,1,exception);
            if (p == (const PixelPacket *) NULL)
              break;
            indexes=GetVirtualIndexQueue(image);
            for (x=0; x < (long) image->columns; x++)
            {
              if (p->opacity == (Quantum) TransparentOpacity)
                break;
              p++;
            }
            if (x < (long) image->columns)
              break;
          }
          if ((x < (long) image->columns) || (y < (long) image->rows))
            {
              char
                tuple[MaxTextExtent];

              MagickPixelPacket
                pixel;

              GetMagickPixelPacket(image,&pixel);
              SetMagickPixelPacket(image,p,indexes+x,&pixel);
              (void) QueryMagickColorname(image,&pixel,SVGCompliance,tuple,
                &image->exception);
              (void) fprintf(file,"  Alpha: %s ",tuple);
              GetColorTuple(&pixel,MagickTrue,tuple);
              (void) fprintf(file,"  %s\n",tuple);
            }
        }
      if (ping == MagickFalse)
        {
          artifact=GetImageArtifact(image,"identify:unique");
          if ((artifact != (const char *) NULL) &&
              (IsMagickTrue(artifact) != MagickFalse))
            (void) fprintf(file,"  Colors: %lu\n",GetNumberColors(image,
              (FILE *) NULL,&image->exception));
          if (IsHistogramImage(image,&image->exception) != MagickFalse)
            {
              (void) fprintf(file,"  Histogram:\n");
              (void) GetNumberColors(image,file,&image->exception);
            }
        }
    }