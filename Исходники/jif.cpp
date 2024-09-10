SEXP addNeighborhoodToImageHelper(
  SEXP r_antsimage,
  SEXP r_center,
  SEXP r_rad,
  SEXP r_vec)
{
  typedef typename ImageType::Pointer  ImagePointerType;
  const unsigned int ImageDimension = ImageType::ImageDimension;
  typedef float                        PixelType;
  typename ImageType::Pointer image =
    Rcpp::as< ImagePointerType >( r_antsimage );
  Rcpp::NumericVector center( r_center );
  Rcpp::NumericVector rad( r_rad );
  Rcpp::NumericVector intvec( r_vec );
  if ( center.size() != ImageDimension )
    Rcpp::stop("addNeighborhoodToImageHelper dim error.");
  typename itk::NeighborhoodIterator<ImageType>::SizeType nSize;
  typename ImageType::IndexType ind;
  ind.Fill( 0 );
  for ( unsigned int i=0; i<ImageDimension; i++ )
    {
    nSize[i] = rad[i];
    ind[i] = center[i]; // R coords to ITK
    }
  itk::NeighborhoodIterator<ImageType> nit( nSize, image,
    image->GetLargestPossibleRegion() ) ;
// for each location in nitSearch, compute the correlation
// of the intvec with the nit neighborhood
  nit.SetLocation( ind );
  for( unsigned int i = 0; i < nit.Size(); i++ )
    {
    typename ImageType::IndexType ind2 = nit.GetIndex(i);
    PixelType lval = image->GetPixel( ind2 );
    image->SetPixel( ind2, lval + intvec[i] );
    }
  return 0;
}