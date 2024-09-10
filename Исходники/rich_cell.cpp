void 
rich_cell::
update_texture( ImageType::Pointer image )
{
  // Compute the gradient magnitude
  GradMagFilterType::Pointer gmFilter = GradMagFilterType::New();
  gmFilter->SetInput( image );
  try {
    gmFilter->Update();
  }
  catch (itk::ExceptionObject & e) {
      std::cerr << "Exception in SubFilter: " << e << std::endl;
      exit(0);
  }
  FloatImageType::Pointer gmImage = gmFilter->GetOutput();

  // Compute the texture as the average gradient of the first portion
  // of the sorted gradient magnitudes.

  std::cout<<"class = "<<class_type_<<std::endl;
  double interior_grad = 0;
  std::vector< float > grad_magnitudes;
  grad_magnitudes.reserve(interior_points_.size());
  FloatImageType::IndexType ind;
  for (unsigned int i = 0; i<interior_points_.size(); i++) {
    ind[0] = interior_points_[i][0];
    ind[1] = interior_points_[i][1];
    ind[2] = interior_points_[i][2];
    //interior_grad += gmImage->GetPixel( ind );
    //std::cout<<interior_points_[i]<<", grad_mag = "<<gmImage->GetPixel( ind )<<std::endl;
    grad_magnitudes.push_back(gmImage->GetPixel( ind ));
  }
  
  /*
  std::vector<float>::iterator loc = grad_magnitudes.begin()+interior_points_.size()/2;
  std::nth_element(grad_magnitudes.begin(), loc, grad_magnitudes.end());
  //texture_ = interior_grad/(double)interior_points_.size();
  */
  std::vector<float>::iterator loc = grad_magnitudes.begin()+grad_magnitudes.size()/2;
  std::partial_sort(grad_magnitudes.begin(), loc, grad_magnitudes.end());
  for (std::vector<float>::iterator itr=grad_magnitudes.begin(); itr<loc; itr++) {
    interior_grad += *itr;
  }
  texture_ = interior_grad/grad_magnitudes.size()*2;
  //std::cout<<"texture = "<<texture_<<std::endl;

  /*
  image->SetRequestedRegion( bounding_box_ );
  
  int radius = 1; //for both median filtering and structuring element

  //set neighborhood
  ImageType::SizeType miIndexRadius;
  
  miIndexRadius[0] = radius; // radius along x
  miIndexRadius[1] = radius; // radius along y
  miIndexRadius[2] = 0;	// radius along z
  MedianFilterType::Pointer f_med = MedianFilterType::New();
  
  //set radius and input
  f_med->SetRadius( miIndexRadius );
  f_med->SetInput( image );
  
  OpenFilterType::Pointer f_open = OpenFilterType::New();
  ErodeFilterType::Pointer  f_erode  = ErodeFilterType::New();
  DilateFilterType::Pointer f_dilate = DilateFilterType::New();
  SubFilterType::Pointer f_sub = SubFilterType::New();
  
  StructuringElementType  structuringElement;
  structuringElement.SetRadius( radius );
  structuringElement.CreateStructuringElement();
  
  f_open->SetKernel( structuringElement );
  f_erode->SetKernel(  structuringElement );
  f_dilate->SetKernel( structuringElement );

  //connect open to medium filter
  f_open->SetInput( f_med->GetOutput() );
  f_erode->SetInput(  f_open->GetOutput() );
  f_dilate->SetInput( f_open->GetOutput() ); 

  //set inputs of substract filter for morphological gradient
  //(dilation-erosion=morphological gradient)
  f_sub->SetInput1( f_dilate->GetOutput() );
  f_sub->SetInput2( f_erode->GetOutput() );

  try
    {
      f_sub->Update();
    }
  catch (itk::ExceptionObject & e)
    {
      std::cerr << "Exception in SubFilter: " << e << std::endl;
      exit(0);
    }

  // Now we can compute the gradient values!
  ImageType::Pointer morph_image = f_sub->GetOutput();
  double interior_grad = 0;
  ImageType::IndexType ind;
  for (unsigned int i = 0; i<interior_points_.size(); i++) {
    ind[0] = interior_points_[i][0];
    ind[1] = interior_points_[i][1];
    ind[2] = interior_points_[i][2];
    interior_grad += morph_image->GetPixel( ind );
  }
  texture_ = interior_grad/(double)interior_points_.size();
  */

  /*
  double bdry_grad = 0;
  for (unsigned int i = 0; i<cell->boundary_points_.size(); i++) {
    ind[0] = cell->interior_points_[i][0];
    ind[1] = cell->interior_points_[i][1];
    ind[2] = cell->interior_points_[i][2];
    bdry_grad += morph_image->GetPixel( ind );
  }
  cell->ave_bound_gradient_ = vol_grad/(double)cell->boundary_points_.size();
  */
}