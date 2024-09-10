void mitk::Image::Initialize(vtkImageData* vtkimagedata, int channels, int tDim, int sDim, int pDim)
{
  if(vtkimagedata==nullptr) return;

  m_Dimension=vtkimagedata->GetDataDimension();
  unsigned int i, *tmpDimensions=new unsigned int[m_Dimension>4?m_Dimension:4];
  for(i=0;i<m_Dimension;++i) tmpDimensions[i]=vtkimagedata->GetDimensions()[i];
  if(m_Dimension<4)
  {
    unsigned int *p;
    for(i=0,p=tmpDimensions+m_Dimension;i<4-m_Dimension;++i, ++p)
      *p=1;
  }

  if(pDim>=0)
  {
    tmpDimensions[1]=pDim;
    if(m_Dimension < 2)
      m_Dimension = 2;
  }
  if(sDim>=0)
  {
    tmpDimensions[2]=sDim;
    if(m_Dimension < 3)
      m_Dimension = 3;
  }
  if(tDim>=0)
  {
    tmpDimensions[3]=tDim;
    if(m_Dimension < 4)
      m_Dimension = 4;
  }

  mitk::PixelType pixelType(MakePixelType(vtkimagedata));
  Initialize(pixelType, m_Dimension, tmpDimensions, channels);

  const double *spacinglist = vtkimagedata->GetSpacing();
  Vector3D spacing;
  FillVector3D(spacing, spacinglist[0], 1.0, 1.0);
  if(m_Dimension>=2)
    spacing[1]=spacinglist[1];
  if(m_Dimension>=3)
    spacing[2]=spacinglist[2];

  // access origin of vtkImage
  Point3D origin;
  double vtkorigin[3];
  vtkimagedata->GetOrigin(vtkorigin);
  FillVector3D(origin, vtkorigin[0], 0.0, 0.0);
  if(m_Dimension>=2)
    origin[1]=vtkorigin[1];
  if(m_Dimension>=3)
    origin[2]=vtkorigin[2];

  SlicedGeometry3D* slicedGeometry = GetSlicedGeometry(0);

  // re-initialize PlaneGeometry with origin and direction
  PlaneGeometry* planeGeometry = static_cast<PlaneGeometry*>(slicedGeometry->GetPlaneGeometry(0));
  planeGeometry->SetOrigin(origin);

  // re-initialize SlicedGeometry3D
  slicedGeometry->SetOrigin(origin);
  slicedGeometry->SetSpacing(spacing);

  ProportionalTimeGeometry::Pointer timeGeometry = ProportionalTimeGeometry::New();
  timeGeometry->Initialize(slicedGeometry, m_Dimensions[3]);
  SetTimeGeometry(timeGeometry);

  delete [] tmpDimensions;
}