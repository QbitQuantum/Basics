inline bool
  pcl::PolynomialCalculationsT<real>::bivariatePolynomialApproximation (
      std::vector<Eigen::Matrix<real, 3, 1> >& samplePoints, unsigned int polynomial_degree,
      pcl::BivariatePolynomialT<real>& ret) const
{
  //MEASURE_FUNCTION_TIME;
  unsigned int parameters_size = BivariatePolynomialT<real>::getNoOfParametersFromDegree (polynomial_degree);
  //cout << PVARN (parameters_size);

  //cout << "Searching for the "<<parameters_size<<" parameters for the bivariate polynom of degree "
  //     << polynomial_degree<<" using "<<samplePoints.size ()<<" points.\n";
  
  if (parameters_size > samplePoints.size ()) // Too many parameters for this number of equations (points)?
  {
    return false;    
    // Reduce degree of polynomial
    //polynomial_degree = (unsigned int) (0.5f* (sqrtf (8*samplePoints.size ()+1) - 3));
    //parameters_size = BivariatePolynomialT<real>::getNoOfParametersFromDegree (polynomial_degree);
    //cout << "Not enough points, so degree of polynomial was decreased to "<<polynomial_degree
    //     << " ("<<samplePoints.size ()<<" points => "<<parameters_size<<" parameters)\n";
  }
  
  ret.setDegree (polynomial_degree);
  
  //double coeffStuffStartTime=-get_time ();
  Eigen::Matrix<real, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> A (parameters_size, parameters_size);
  A.setZero();
  Eigen::Matrix<real, Eigen::Dynamic, 1> b (parameters_size);
  b.setZero();
  real currentX, currentY, currentZ;
  real tmpX, tmpY;
  real *tmpC = new real[parameters_size];
  real* tmpCEndPtr = &tmpC[parameters_size-1];
  for (typename std::vector<Eigen::Matrix<real, 3, 1> >::const_iterator it=samplePoints.begin ();
       it!=samplePoints.end (); ++it)
  {
    currentX= (*it)[0]; currentY= (*it)[1]; currentZ= (*it)[2];
    //cout << "current point: "<<currentX<<","<<currentY<<" => "<<currentZ<<"\n";
    //unsigned int posInC = parameters_size-1;
    real* tmpCPtr = tmpCEndPtr;
    tmpX = 1.0;
    for (unsigned int xDegree=0; xDegree<=polynomial_degree; ++xDegree)
    {
      tmpY = 1.0;
      for (unsigned int yDegree=0; yDegree<=polynomial_degree-xDegree; ++yDegree)
      {
        * (tmpCPtr--) = tmpX*tmpY;
        //cout << "x="<<currentX<<", y="<<currentY<<", Pos "<<posInC--<<": "<<tmpX<<"*"<<tmpY<<"="<<tmpC[posInC]<<"\n";
        tmpY *= currentY;
      }
      tmpX *= currentX;
    }
    
    real* APtr = &A(0,0);
    real* bPtr = &b[0];
    real* tmpCPtr1=tmpC;
    for (unsigned int i=0; i<parameters_size; ++i)
    {
      * (bPtr++) += currentZ * *tmpCPtr1;
      
      real* tmpCPtr2=tmpC;
      for (unsigned int j=0; j<parameters_size; ++j)
      {
        * (APtr++) += *tmpCPtr1 * * (tmpCPtr2++);
      }
      
      ++tmpCPtr1;
    }
    //A += DMatrix<real>::outProd (tmpC);
    //b += currentZ * tmpC;
  }
  //cout << "Calculating matrix A and vector b (size "<<b.size ()<<") from "<<samplePoints.size ()<<" points took "
       //<< (coeffStuffStartTime+get_time ())*1000<<"ms using constant memory.\n";
    //cout << PVARC (A)<<PVARN (b);


  //double coeffStuffStartTime=-get_time ();
  //DMatrix<real> A (parameters_size, parameters_size);
  //DVector<real> b (parameters_size);
  //real currentX, currentY, currentZ;
  //unsigned int posInC;
  //real tmpX, tmpY;
  //DVector<real> tmpC (parameters_size);
  //for (typename std::vector<Eigen::Matrix<real, 3, 1> >::const_iterator it=samplePoints.begin ();
  //     it!=samplePoints.end (); ++it)
  //{
    //currentX= (*it)[0]; currentY= (*it)[1]; currentZ= (*it)[2];
    ////cout << "x="<<currentX<<", y="<<currentY<<"\n";
    //posInC = parameters_size-1;
    //tmpX = 1.0;
    //for (unsigned int xDegree=0; xDegree<=polynomial_degree; xDegree++)
    //{
      //tmpY = 1.0;
      //for (unsigned int yDegree=0; yDegree<=polynomial_degree-xDegree; yDegree++)
      //{
        //tmpC[posInC] = tmpX*tmpY;
        ////cout << "x="<<currentX<<", y="<<currentY<<", Pos "<<posInC<<": "<<tmpX<<"*"<<tmpY<<"="<<tmpC[posInC]<<"\n";
        //tmpY *= currentY;
        //posInC--;
      //}
      //tmpX *= currentX;
    //}
    //A += DMatrix<real>::outProd (tmpC);
    //b += currentZ * tmpC;
  //}
  //cout << "Calculating matrix A and vector b (size "<<b.size ()<<") from "<<samplePoints.size ()<<" points took "
       //<< (coeffStuffStartTime+get_time ())*1000<<"ms.\n";
  
  Eigen::Matrix<real, Eigen::Dynamic, 1> parameters;
  //double choleskyStartTime=-get_time ();
  //parameters = A.choleskySolve (b);
  //cout << "Cholesky took "<< (choleskyStartTime+get_time ())*1000<<"ms.\n";

  //double invStartTime=-get_time ();
  parameters = A.inverse () * b;
  //cout << "Inverse took "<< (invStartTime+get_time ())*1000<<"ms.\n";

  //cout << PVARC (A)<<PVARC (b)<<PVARN (parameters);
  
  real inversionCheckResult = (A*parameters - b).norm ();
  if (inversionCheckResult > 1e-5)
  {
    //cout << "Inversion result: "<< inversionCheckResult<<" for matrix "<<A<<"\n";
    return false;
  }
  
  for (unsigned int i=0; i<parameters_size; i++)
    ret.parameters[i] = parameters[i];
  
  //cout << "Resulting polynomial is "<<ret<<"\n";

  //Test of gradient: ret.calculateGradient ();

  delete [] tmpC;
  return true;
}