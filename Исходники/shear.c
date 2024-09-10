/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S h e a r I m a g e                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ShearImage() creates a new image that is a shear_image copy of an existing
%  one.  Shearing slides one edge of an image along the X or Y axis, creating
%  a parallelogram.  An X direction shear slides an edge along the X axis,
%  while a Y direction shear slides an edge along the Y axis.  The amount of
%  the shear is controlled by a shear angle.  For X direction shears, x_shear
%  is measured relative to the Y axis, and similarly, for Y direction shears
%  y_shear is measured relative to the X axis.  Empty triangles left over from
%  shearing the image are filled with the background color defined by member
%  'background_color' of the image..  ShearImage() allocates the memory
%  necessary for the new Image structure and returns a pointer to the new image.
%
%  ShearImage() is based on the paper "A Fast Algorithm for General Raster
%  Rotatation" by Alan W. Paeth.
%
%  The format of the ShearImage method is:
%
%      Image *ShearImage(const Image *image,const double x_shear,
%        const double y_shear,ExceptionInfo *exception)
%
%  A description of each parameter follows.
%
%    o image: The image.
%
%    o x_shear, y_shear: Specifies the number of degrees to shear the image.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
MagickExport Image *ShearImage(const Image *image,const double x_shear,
  const double y_shear,ExceptionInfo *exception)
{
  Image
    *integral_image,
    *shear_image;

  long
    x_offset,
    y_offset;

  PointInfo
    shear;

  RectangleInfo
    border_info;

  unsigned long
    y_width;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  if ((x_shear != 0.0) && (fmod(x_shear,90.0) == 0.0))
    ThrowImageException(ImageError,"AngleIsDiscontinuous");
  if ((y_shear != 0.0) && (fmod(y_shear,90.0) == 0.0))
    ThrowImageException(ImageError,"AngleIsDiscontinuous");
  /*
    Initialize shear angle.
  */
  integral_image=CloneImage(image,0,0,MagickTrue,exception);
  if (integral_image == (Image *) NULL)
    ThrowImageException(ResourceLimitError,"MemoryAllocationFailed");
  shear.x=(-tan(DegreesToRadians(x_shear)));
  shear.y=tan(DegreesToRadians(y_shear));
  if ((shear.x == 0.0) && (shear.y == 0.0))
    return(integral_image);
  integral_image->storage_class=DirectClass;
  if (integral_image->matte == MagickFalse)
    SetImageOpacity(integral_image,OpaqueOpacity);
  /*
    Compute image size.
  */
  x_offset=(long) (fabs((double) image->rows*shear.x)+0.5);
  y_width=(unsigned long)
    (fabs((double) image->rows*shear.x)+image->columns+0.5);
  y_offset=(long) (fabs((double) y_width*shear.y)+0.5);
  /*
    Surround image with border.
  */
  integral_image->border_color=integral_image->background_color;
  border_info.width=(unsigned long) x_offset;
  border_info.height=(unsigned long) y_offset;
  shear_image=BorderImage(integral_image,&border_info,exception);
  if (shear_image == (Image *) NULL)
    ThrowImageException(ResourceLimitError,"MemoryAllocationFailed");
  integral_image=DestroyImage(integral_image);
  /*
    Shear the image.
  */
  if (shear_image->matte == MagickFalse)
    SetImageOpacity(shear_image,OpaqueOpacity);
  XShearImage(shear_image,shear.x,image->columns,image->rows,x_offset,
    ((long) shear_image->rows-image->rows)/2);
  YShearImage(shear_image,shear.y,y_width,image->rows,
    ((long) shear_image->columns-y_width)/2,y_offset);
  CropToFitImage(&shear_image,shear.x,shear.y,(MagickRealType) image->columns,
    (MagickRealType) image->rows,MagickFalse,exception);
  shear_image->page.width=0;
  shear_image->page.height=0;
  return(shear_image);
}