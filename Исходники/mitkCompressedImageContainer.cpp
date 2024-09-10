mitk::Image::Pointer mitk::CompressedImageContainer::GetImage()
{
  if (m_ByteBuffers.empty())
    return nullptr;

  // uncompress image data, create an Image
  Image::Pointer image = Image::New();
  unsigned int dims[20]; // more than 20 dimensions and bang
  for (unsigned int dim = 0; dim < m_ImageDimension; ++dim)
    dims[dim] = m_ImageDimensions[dim];

  image->Initialize(*m_PixelType, m_ImageDimension, dims); // this IS needed, right ?? But it does allocate memory ->
                                                           // does create one big lump of memory (also in windows)

  unsigned int timeStep(0);
  for (auto iter = m_ByteBuffers.begin(); iter != m_ByteBuffers.end(); ++iter, ++timeStep)
  {
    ImageReadAccessor imgAcc(image, image->GetVolumeData(timeStep));
    auto *dest((unsigned char *)imgAcc.GetData());
    ::uLongf destLen(m_OneTimeStepImageSizeInBytes);
    ::Bytef *source(iter->first);
    ::uLongf sourceLen(iter->second);
    int zlibRetVal = ::uncompress(dest, &destLen, source, sourceLen);
    if (itk::Object::GetDebug())
    {
      if (zlibRetVal == Z_OK)
      {
        MITK_INFO << "Success, destLen now " << destLen << " bytes" << std::endl;
      }
      else
      {
        switch (zlibRetVal)
        {
          case Z_DATA_ERROR:
            MITK_ERROR << "compressed data corrupted" << std::endl;
            break;
          case Z_MEM_ERROR:
            MITK_ERROR << "not enough memory" << std::endl;
            break;
          case Z_BUF_ERROR:
            MITK_ERROR << "output buffer too small" << std::endl;
            break;
          default:
            MITK_ERROR << "other, unspecified error" << std::endl;
            break;
        }
      }
    }
  }

  image->SetGeometry(m_ImageGeometry);
  image->Modified();

  return image;
}