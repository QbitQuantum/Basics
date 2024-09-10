SEXP sccanCppHelper(
  NumericMatrix X,
  NumericMatrix Y,
  SEXP r_maskx,
  SEXP r_masky,
  RealType sparsenessx,
  RealType sparsenessy,
  IntType nvecs,
  IntType its,
  IntType cthreshx,
  IntType cthreshy,
  RealType z,
  RealType smooth,
  Rcpp::List initializationListx,
  Rcpp::List initializationListy,
  IntType covering,
  RealType ell1,
  IntType verbose,
  RealType priorWeight )
{
  enum { Dimension = ImageType::ImageDimension };
  typename ImageType::RegionType region;
  typedef typename ImageType::PixelType PixelType;
  typedef typename ImageType::Pointer ImagePointerType;
  typedef double                                        Scalar;
  typedef itk::ants::antsSCCANObject<ImageType, Scalar> SCCANType;
  typedef typename SCCANType::MatrixType                vMatrix;
  typename SCCANType::Pointer sccanobj = SCCANType::New();

  typename ImageType::Pointer maskx = Rcpp::as<ImagePointerType>( r_maskx );
  typename ImageType::Pointer masky = Rcpp::as<ImagePointerType>( r_masky );

  bool maskxisnull = maskx.IsNull();
  bool maskyisnull = masky.IsNull();
// deal with the initializationList, if any
  unsigned int nImagesx = initializationListx.size();
  if ( ( nImagesx > 0 ) && ( !maskxisnull ) )
    {
    itk::ImageRegionIteratorWithIndex<ImageType> it( maskx,
      maskx->GetLargestPossibleRegion() );
    vMatrix priorROIMatx( nImagesx , X.cols() );
    priorROIMatx.fill( 0 );
    for ( unsigned int i = 0; i < nImagesx; i++ )
      {
      typename ImageType::Pointer init =
        Rcpp::as<ImagePointerType>( initializationListx[i] );
      unsigned long ct = 0;
      it.GoToBegin();
      while ( !it.IsAtEnd() )
        {
        PixelType pix = it.Get();
        if ( pix >= 0.5 )
          {
          pix = init->GetPixel( it.GetIndex() );
          priorROIMatx( i, ct ) = pix;
          ct++;
          }
        ++it;
        }
      }
    sccanobj->SetMatrixPriorROI( priorROIMatx );
    nvecs = nImagesx;
    }
  unsigned int nImagesy = initializationListy.size();
  if ( ( nImagesy > 0 ) && ( !maskyisnull ) )
    {
    itk::ImageRegionIteratorWithIndex<ImageType> it( masky,
      masky->GetLargestPossibleRegion() );
    vMatrix priorROIMaty( nImagesy , Y.cols() );
    priorROIMaty.fill( 0 );
    for ( unsigned int i = 0; i < nImagesy; i++ )
      {
      typename ImageType::Pointer init =
        Rcpp::as<ImagePointerType>( initializationListy[i] );
      unsigned long ct = 0;
      it.GoToBegin();
      while ( !it.IsAtEnd() )
        {
        PixelType pix = it.Get();
        if ( pix >= 0.5 )
          {
          pix = init->GetPixel( it.GetIndex() );
          priorROIMaty( i, ct ) = pix;
          ct++;
          }
        ++it;
        }
      }
    sccanobj->SetMatrixPriorROI2( priorROIMaty );
    nvecs = nImagesy;
    }

  sccanobj->SetPriorWeight( priorWeight );
  sccanobj->SetLambda( priorWeight );
// cast hack from Rcpp type to sccan type
  std::vector<double> xdat =
      Rcpp::as< std::vector<double> >( X );
  const double* _xdata = &xdat[0];
  vMatrix vnlX( _xdata , X.cols(), X.rows()  );
  vnlX = vnlX.transpose();
  std::vector<double> ydat =
      Rcpp::as< std::vector<double> >( Y );
  const double* _ydata = &ydat[0];
  vMatrix vnlY( _ydata , Y.cols(), Y.rows()  );
  vnlY = vnlY.transpose();
// cast hack done
  sccanobj->SetGetSmall( false  );
  sccanobj->SetCovering( covering );
  sccanobj->SetSilent(  ! verbose  );
  if( ell1 > 0 )
    {
    sccanobj->SetUseL1( true );
    }
  else
    {
    sccanobj->SetUseL1( false );
    }
  sccanobj->SetGradStep( vnl_math_abs( ell1 ) );
  sccanobj->SetMaximumNumberOfIterations( its );
  sccanobj->SetRowSparseness( z );
  sccanobj->SetSmoother( smooth );
  if ( sparsenessx < 0 ) sccanobj->SetKeepPositiveP(false);
  if ( sparsenessy < 0 ) sccanobj->SetKeepPositiveQ(false);
  sccanobj->SetSCCANFormulation(  SCCANType::PQ );
  sccanobj->SetFractionNonZeroP( fabs( sparsenessx ) );
  sccanobj->SetFractionNonZeroQ( fabs( sparsenessy ) );
  sccanobj->SetMinClusterSizeP( cthreshx );
  sccanobj->SetMinClusterSizeQ( cthreshy );
  sccanobj->SetMatrixP( vnlX );
  sccanobj->SetMatrixQ( vnlY );
//  sccanobj->SetMatrixR( r ); // FIXME
  sccanobj->SetMaskImageP( maskx );
  sccanobj->SetMaskImageQ( masky );
  sccanobj->SparsePartialArnoldiCCA( nvecs );

  // FIXME - should not copy, should map memory
  vMatrix solP = sccanobj->GetVariatesP();
  NumericMatrix eanatMatp( solP.cols(), solP.rows() );
  unsigned long rows = solP.rows();
  for( unsigned long c = 0; c < solP.cols(); c++ )
    {
    for( unsigned int r = 0; r < rows; r++ )
      {
      eanatMatp( c, r ) = solP( r, c );
      }
    }

  vMatrix solQ = sccanobj->GetVariatesQ();
  NumericMatrix eanatMatq( solQ.cols(), solQ.rows() );
  rows = solQ.rows();
  for( unsigned long c = 0; c < solQ.cols(); c++ )
    {
    for( unsigned int r = 0; r < rows; r++ )
      {
      eanatMatq( c, r ) = solQ( r, c );
      }
    }

  return(
      Rcpp::List::create(
        Rcpp::Named("eig1") = eanatMatp,
        Rcpp::Named("eig2") = eanatMatq )
      );
}