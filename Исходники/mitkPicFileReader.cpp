mitk::Image::Pointer mitk::PicFileReader::CreateImage()
{
  Image::Pointer output = Image::New();

  std::string fileName = this->GetLocalFileName();

  mitkIpPicDescriptor *header = mitkIpPicGetHeader(const_cast<char *>(fileName.c_str()), NULL);

  if (!header)
  {
    mitkThrow() << "File could not be read.";
  }

  header = mitkIpPicGetTags(const_cast<char *>(fileName.c_str()), header);

  int channels = 1;

  mitkIpPicTSV_t *tsv;
  if ((tsv = mitkIpPicQueryTag(header, "SOURCE HEADER")) != NULL)
  {
    if (tsv->n[0] > 1e+06)
    {
      mitkIpPicTSV_t *tsvSH;
      tsvSH = mitkIpPicDelTag(header, "SOURCE HEADER");
      mitkIpPicFreeTag(tsvSH);
    }
  }
  if ((tsv = mitkIpPicQueryTag(header, "ICON80x80")) != NULL)
  {
    mitkIpPicTSV_t *tsvSH;
    tsvSH = mitkIpPicDelTag(header, "ICON80x80");
    mitkIpPicFreeTag(tsvSH);
  }
  if ((tsv = mitkIpPicQueryTag(header, "VELOCITY")) != NULL)
  {
    ++channels;
    mitkIpPicDelTag(header, "VELOCITY");
  }

  if (header == NULL || header->bpe == 0)
  {
    mitkThrow() << " Could not read file " << fileName;
  }

  // if pic image only 2D, the n[2] value is not initialized
  unsigned int slices = 1;
  if (header->dim == 2)
  {
    header->n[2] = slices;
  }

  // First initialize the geometry of the output image by the pic-header
  SlicedGeometry3D::Pointer slicedGeometry = mitk::SlicedGeometry3D::New();
  PicHelper::InitializeEvenlySpaced(header, header->n[2], slicedGeometry);

  // if pic image only 3D, the n[3] value is not initialized
  unsigned int timesteps = 1;
  if (header->dim > 3)
  {
    timesteps = header->n[3];
  }

  slicedGeometry->ImageGeometryOn();
  ProportionalTimeGeometry::Pointer timeGeometry = ProportionalTimeGeometry::New();
  timeGeometry->Initialize(slicedGeometry, timesteps);

  // Cast the pic descriptor to ImageDescriptor and initialize the output

  output->Initialize(CastToImageDescriptor(header));
  output->SetTimeGeometry(timeGeometry);
  mitkIpPicFree(header);

  return output;
}