  void ToFNrrdImageWriter::ConvertStreamToNrrdFormat( std::string fileName )
  {
    int CaptureWidth = 0;
    int CaptureHeight = 0;
    int PixelNumber = 0;
    int ImageSizeInBytes = 0;
    if (fileName==this->m_RGBImageFileName)
    {
        CaptureWidth = this->m_RGBCaptureWidth;
        CaptureHeight = this->m_RGBCaptureHeight;
        PixelNumber = this->m_RGBPixelNumber;
        ImageSizeInBytes = this->m_RGBImageSizeInBytes;
    } else
    {
        CaptureWidth = this->m_ToFCaptureWidth;
        CaptureHeight = this->m_ToFCaptureHeight;
        PixelNumber = this->m_ToFPixelNumber;
        ImageSizeInBytes = this->m_ToFImageSizeInBytes;
    }
    Image::Pointer imageTemplate = Image::New();
    int dimension ;
    unsigned int* dimensions;
    if(m_ToFImageType == ToFImageType2DPlusT)
    {
      dimension = 4;
      dimensions = new unsigned int[dimension];
      dimensions[0] = CaptureWidth;
      dimensions[1] = CaptureHeight;
      dimensions[2] = 1;
      dimensions[3] = this->m_NumOfFrames;
    }
    else if( m_ToFImageType == ToFImageType3D)
    {
      dimension = 3;
      dimensions = new unsigned int[dimension];
      dimensions[0] = CaptureWidth;
      dimensions[1] = CaptureHeight;
      dimensions[2] = this->m_NumOfFrames;
    }
    else
    {
      throw std::logic_error("No image type set, please choose between 2D+t and 3D!");
    }
    float* floatData;
    unsigned char* rgbData;
    if (fileName==this->m_RGBImageFileName)
    {
      rgbData = new unsigned char[PixelNumber*3];
      for(int i=0; i<PixelNumber*3; i++)
      {
        rgbData[i] = i + 0.0;
      }
      mitk::PixelType RGBType = MakePixelType<unsigned char, itk::RGBPixel<unsigned char>, 3>();
      imageTemplate->Initialize( RGBType,dimension, dimensions, 1);
      imageTemplate->SetSlice(rgbData, 0, 0, 0);
    }
    else
    {
      floatData = new float[PixelNumber];
      for(int i=0; i<PixelNumber; i++)
      {
        floatData[i] = i + 0.0;
      }
      mitk::PixelType FloatType = MakeScalarPixelType<float>();
      imageTemplate->Initialize( FloatType,dimension, dimensions, 1);
      imageTemplate->SetSlice(floatData, 0, 0, 0);
    }

    itk::NrrdImageIO::Pointer nrrdWriter = itk::NrrdImageIO::New();
    nrrdWriter->SetNumberOfDimensions(dimension);
    nrrdWriter->SetPixelType( imageTemplate->GetPixelType().GetPixelType());
    nrrdWriter->SetComponentType( (itk::ImageIOBase::IOComponentType) imageTemplate->GetPixelType().GetComponentType());
    if(imageTemplate->GetPixelType().GetNumberOfComponents() > 1)
    {
      nrrdWriter->SetNumberOfComponents(imageTemplate->GetPixelType().GetNumberOfComponents());
    }

    itk::ImageIORegion ioRegion( dimension );
    mitk::Vector3D spacing = imageTemplate->GetGeometry()->GetSpacing();
    mitk::Point3D origin = imageTemplate->GetGeometry()->GetOrigin();

    for(unsigned int i = 0; i < dimension; i++)
    {
      nrrdWriter->SetDimensions(i,dimensions[i]);
      nrrdWriter->SetSpacing(i,spacing[i]);
      nrrdWriter->SetOrigin(i,origin[i]);

      mitk::Vector3D direction;
      direction.Set_vnl_vector(imageTemplate->GetGeometry()->GetIndexToWorldTransform()->GetMatrix().GetVnlMatrix().get_column(i));
      vnl_vector< double > axisDirection(dimension);

      for(unsigned int j = 0; j < dimension; j++)
      {
        axisDirection[j] = direction[j]/spacing[i];
      }
      nrrdWriter->SetDirection( i, axisDirection );

      ioRegion.SetSize(i, imageTemplate->GetLargestPossibleRegion().GetSize(i) );
      ioRegion.SetIndex(i, imageTemplate->GetLargestPossibleRegion().GetIndex(i) );
    }

    nrrdWriter->SetIORegion(ioRegion);
    nrrdWriter->SetFileName(fileName);
    nrrdWriter->SetUseStreamedWriting(true);

    std::ifstream stream(fileName.c_str(), std::ifstream::binary);
    if (fileName==m_RGBImageFileName)
    {
      unsigned int size = PixelNumber*3 * this->m_NumOfFrames;
      unsigned int sizeInBytes = size * sizeof(unsigned char);
      unsigned char* data = new unsigned char[size];
      stream.read((char*)data, sizeInBytes);
      nrrdWriter->Write(data);
      stream.close();
      delete[] data;
    }
    else
    {
      unsigned int size = PixelNumber * this->m_NumOfFrames;
      unsigned int sizeInBytes = size * sizeof(float);
      float* data = new float[size];
      stream.read((char*)data, sizeInBytes);
      try
      {
        nrrdWriter->Write(data);
      }
      catch (itk::ExceptionObject* e)
      {
        MITK_ERROR<< e->what();
        return;
      }

      stream.close();
      delete[] data;
    }

    delete[] dimensions;
    if (fileName==m_RGBImageFileName)
    {
      delete[] rgbData;
    }
    else
    {
      delete[] floatData;
    }
  }