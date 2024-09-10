std::vector<BaseData::Pointer> ItkImageIO::Read()
{
  std::vector<BaseData::Pointer> result;

  const std::string& locale = "C";
  const std::string& currLocale = setlocale( LC_ALL, NULL );

  if ( locale.compare(currLocale)!=0 )
  {
    try
    {
      setlocale(LC_ALL, locale.c_str());
    }
    catch(...)
    {
      MITK_INFO << "Could not set locale " << locale;
    }
  }

  Image::Pointer image = Image::New();

  const unsigned int MINDIM = 2;
  const unsigned int MAXDIM = 4;

  const std::string path = this->GetLocalFileName();

  MITK_INFO << "loading " << path << " via itk::ImageIOFactory... " << std::endl;

  // Check to see if we can read the file given the name or prefix
  if (path.empty())
  {
    mitkThrow() << "Empty filename in mitk::ItkImageIO ";
  }

  // Got to allocate space for the image. Determine the characteristics of
  // the image.
  m_ImageIO->SetFileName( path );
  m_ImageIO->ReadImageInformation();

  unsigned int ndim = m_ImageIO->GetNumberOfDimensions();
  if ( ndim < MINDIM || ndim > MAXDIM )
  {
    MITK_WARN << "Sorry, only dimensions 2, 3 and 4 are supported. The given file has " << ndim << " dimensions! Reading as 4D.";
    ndim = MAXDIM;
  }

  itk::ImageIORegion ioRegion( ndim );
  itk::ImageIORegion::SizeType ioSize = ioRegion.GetSize();
  itk::ImageIORegion::IndexType ioStart = ioRegion.GetIndex();

  unsigned int dimensions[ MAXDIM ];
  dimensions[ 0 ] = 0;
  dimensions[ 1 ] = 0;
  dimensions[ 2 ] = 0;
  dimensions[ 3 ] = 0;

  ScalarType spacing[ MAXDIM ];
  spacing[ 0 ] = 1.0f;
  spacing[ 1 ] = 1.0f;
  spacing[ 2 ] = 1.0f;
  spacing[ 3 ] = 1.0f;

  Point3D origin;
  origin.Fill(0);

  unsigned int i;
  for ( i = 0; i < ndim ; ++i )
  {
    ioStart[ i ] = 0;
    ioSize[ i ] = m_ImageIO->GetDimensions( i );
    if(i<MAXDIM)
    {
      dimensions[ i ] = m_ImageIO->GetDimensions( i );
      spacing[ i ] = m_ImageIO->GetSpacing( i );
      if(spacing[ i ] <= 0)
        spacing[ i ] = 1.0f;
    }
    if(i<3)
    {
      origin[ i ] = m_ImageIO->GetOrigin( i );
    }
  }

  ioRegion.SetSize( ioSize );
  ioRegion.SetIndex( ioStart );

  MITK_INFO << "ioRegion: " << ioRegion << std::endl;
  m_ImageIO->SetIORegion( ioRegion );
  void* buffer = new unsigned char[m_ImageIO->GetImageSizeInBytes()];
  m_ImageIO->Read( buffer );

  image->Initialize( MakePixelType(m_ImageIO), ndim, dimensions );
  image->SetImportChannel( buffer, 0, Image::ManageMemory );

  // access direction of itk::Image and include spacing
  mitk::Matrix3D matrix;
  matrix.SetIdentity();
  unsigned int j, itkDimMax3 = (ndim >= 3? 3 : ndim);
  for ( i=0; i < itkDimMax3; ++i)
    for( j=0; j < itkDimMax3; ++j )
      matrix[i][j] = m_ImageIO->GetDirection(j)[i];

  // re-initialize PlaneGeometry with origin and direction
  PlaneGeometry* planeGeometry = image->GetSlicedGeometry(0)->GetPlaneGeometry(0);
  planeGeometry->SetOrigin(origin);
  planeGeometry->GetIndexToWorldTransform()->SetMatrix(matrix);

  // re-initialize SlicedGeometry3D
  SlicedGeometry3D* slicedGeometry = image->GetSlicedGeometry(0);
  slicedGeometry->InitializeEvenlySpaced(planeGeometry, image->GetDimension(2));
  slicedGeometry->SetSpacing(spacing);

  MITK_INFO << slicedGeometry->GetCornerPoint(false,false,false);
  MITK_INFO << slicedGeometry->GetCornerPoint(true,true,true);

  // re-initialize TimeGeometry
  ProportionalTimeGeometry::Pointer timeGeometry = ProportionalTimeGeometry::New();
  timeGeometry->Initialize(slicedGeometry, image->GetDimension(3));
  image->SetTimeGeometry(timeGeometry);

  buffer = NULL;
  MITK_INFO << "number of image components: "<< image->GetPixelType().GetNumberOfComponents() << std::endl;

  const itk::MetaDataDictionary& dictionary = m_ImageIO->GetMetaDataDictionary();
  for (itk::MetaDataDictionary::ConstIterator iter = dictionary.Begin(), iterEnd = dictionary.End();
       iter != iterEnd; ++iter)
  {
    std::string key = std::string("meta.") + iter->first;
    if (iter->second->GetMetaDataObjectTypeInfo() == typeid(std::string))
    {
      std::string value = dynamic_cast<itk::MetaDataObject<std::string>*>(iter->second.GetPointer())->GetMetaDataObjectValue();
      image->SetProperty(key.c_str(), mitk::StringProperty::New(value));
    }
  }

  MITK_INFO << "...finished!" << std::endl;

  try
  {
    setlocale(LC_ALL, currLocale.c_str());
  }
  catch(...)
  {
    MITK_INFO << "Could not reset locale " << currLocale;
  }

  result.push_back(image.GetPointer());
  return result;
}