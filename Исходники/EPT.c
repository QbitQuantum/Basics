/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e E P T I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WriteEPTImage writes an image in the Adobe Encapsulated Postscript
%  format with a TIFF preview.
%
%  The format of the WriteEPTImage method is:
%
%      unsigned int WriteEPTImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WriteEPTImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to an ImageInfo structure.
%
%    o image:  A pointer to a Image structure.
%
%
*/
Export unsigned int WriteEPTImage(const ImageInfo *image_info,Image *image)
{
  char
    filename[MaxTextExtent];

  FILE
    *ps_file,
    *tiff_file;

  int
    c;

  unsigned int
    status;

  unsigned long
    eps_length,
    tiff_length;

  ps_file=(FILE *) NULL;
  if (Latin1Compare(image_info->magick,"PS") == 0)
    ps_file=fopen(image->magick_filename,ReadBinaryType);
  if (ps_file != (FILE *) NULL)
    {
      struct stat
        attributes;

      /*
        Read existing Encapsulated Postscript.
      */
      eps_length=
        fstat(fileno(ps_file),&attributes) < 0 ? 0 : attributes.st_size;
    }
  else
    {
      /*
        Write image as Encapsulated Postscript to a temporary file.
      */
      (void) strcpy(filename,image->filename);
      TemporaryFilename(image->filename);
      status=WritePSImage(image_info,image);
      if (status == False)
        return(status);
      status=OpenBlob(image_info,image,ReadBinaryType);
      if (status == False)
        WriterExit(FileOpenWarning,"Unable to open file",image);
      (void) remove(image->filename);
      eps_length=image->filesize;
      ps_file=image->file;
      image->file=(FILE *) NULL;
    }
  /*
    Write image as TIFF to a temporary file.
  */
  TemporaryFilename(image->filename);
  status=WriteTIFFImage(image_info,image);
  if (status == False)
    return(status);
  status=OpenBlob(image_info,image,ReadBinaryType);
  if (status == False)
    WriterExit(FileOpenWarning,"Unable to open file",image);
  (void) remove(image->filename);
  tiff_length=image->filesize;
  tiff_file=image->file;
  image->file=(FILE *) NULL;
  /*
    Write EPT image.
  */
  (void) strcpy(image->filename,filename);
  status=OpenBlob(image_info,image,WriteBinaryType);
  if (status == False)
    WriterExit(FileOpenWarning,"Unable to open file",image);
  LSBFirstWriteLong(image,0xc6d3d0c5ul);
  LSBFirstWriteLong(image,30);
  LSBFirstWriteLong(image,eps_length);
  LSBFirstWriteLong(image,0);
  LSBFirstWriteLong(image,0);
  LSBFirstWriteLong(image,eps_length+30);
  LSBFirstWriteLong(image,tiff_length);
  LSBFirstWriteShort(image,0xffff);
  for (c=fgetc(ps_file); c != EOF; c=fgetc(ps_file))
    (void) WriteByte(image,(char) c);
  for (c=fgetc(tiff_file); c != EOF; c=fgetc(tiff_file))
    (void) WriteByte(image,(char) c);
  (void) fclose(tiff_file);
  CloseBlob(image);
  return(True);
}