void mitk::WeightedPointTransform::WeightedPointRegister(vtkPoints *X,
                                                         vtkPoints *Y,
                                                         const CovarianceMatrixList &Sigma_X,
                                                         const CovarianceMatrixList &Sigma_Y,
                                                         double Threshold,
                                                         int MaxIterations,
                                                         Rotation &TransformationR,
                                                         Translation &TransformationT,
                                                         double &FRE,
                                                         int &n)
{
  double FRE_identity = 0.0;
  double FRE_isotropic_weighted = 0.0;
  double initialFRE = 0.0;
  // set config_change to infinite (max double) at start
  double config_change = std::numeric_limits<double>::max();
  Rotation initial_TransformationR;
  initial_TransformationR.SetIdentity();
  Translation initial_TransformationT;
  initial_TransformationT.Fill(0.0);
  // Weightmatrices
  Matrix3x3List W;
  vtkPoints *X_transformed = vtkPoints::New();
  vtkPoints *X_transformedNew = vtkPoints::New();
  vnl_vector<double> oldq;
  itk::VariableSizeMatrix<double> iA;
  vnl_vector<double> iB;

  // initialize memory
  W.resize(X->GetNumberOfPoints());
  X_transformed->SetNumberOfPoints(X->GetNumberOfPoints());
  X_transformedNew->SetNumberOfPoints(X->GetNumberOfPoints());
  iA.SetSize(3u * X->GetNumberOfPoints(), 6u);
  iB.set_size(3u * X->GetNumberOfPoints());

  // calculate FRE_0 with identity transform
  FRE_identity = ComputeWeightedFRE(
    X, Y, Sigma_X, Sigma_Y, m_FRENormalizationFactor, W, initial_TransformationR, initial_TransformationT);

  MITK_DEBUG << "FRE for identity transform: " << FRE_identity;

  // compute isotropic transformation as initial estimate
  IsotropicRegistration(X, Y, m_LandmarkTransform, initial_TransformationR, initial_TransformationT);

  // result of unweighted registration algorithm
  TransformationR = initial_TransformationR;
  TransformationT = initial_TransformationT;

  // calculate FRE_0 with isotropic transform
  FRE_isotropic_weighted =
    ComputeWeightedFRE(X, Y, Sigma_X, Sigma_Y, m_FRENormalizationFactor, W, TransformationR, TransformationT);
  MITK_DEBUG << "FRE for transform obtained with unweighted registration: " << FRE_isotropic_weighted;

  // if R,t is worse than the identity, use the identity as initial transform
  if (FRE_isotropic_weighted < FRE_identity)
  {
    initialFRE = FRE_isotropic_weighted;
  }
  else
  {
    initialFRE = FRE_identity;
    TransformationR.SetIdentity(); // set rotation to identity element
    TransformationT.Fill(0.0);     // set translation to identity element
    initial_TransformationR.SetIdentity();
    initial_TransformationT.Fill(0.0);
  }

  // apply transform to moving set:
  mitk::AnisotropicRegistrationCommon::TransformPoints(X, X_transformed, TransformationR, TransformationT);

  // start with iteration 0
  n = 0;

  do
  {
    n++;

    calculateWeightMatrices(Sigma_X, Sigma_Y, W, TransformationR);

    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // PROBLEM:  no square matrix but the backslash operator in matlab does solve the system anyway. How to convert this
    // to C++?
    //          good descriptons to the "backslash"-operator (in german):
    //          http://www.tm-mathe.de/Themen/html/matlab__zauberstab__backslash-.html
    //                                                                    http://www.tm-mathe.de/Themen/html/matlab__matrix-division__vorsi.html#HoheMatrixA
    //
    //          current method: treat the problem as a minimization problem, because this is what the
    //          "backslash"-operator also does with "high" matrices.
    //                          (and we will have those matrices in most cases)

    C_maker(X_transformed, W, iA);
    E_maker(X_transformed, Y, W, iB);

    vnl_matrix_inverse<double> myInverse(iA.GetVnlMatrix());
    vnl_vector<double> q = myInverse.pinverse(iB.size()) * iB;
    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

    if (n > 1)
      q = (q + oldq) / 2;
    oldq = q;

    itk::Vector<double, 3> delta_t;
    delta_t[0] = q[3];
    delta_t[1] = q[4];
    delta_t[2] = q[5];

    Matrix3x3 delta_theta;
    delta_theta[0][0] = 1;
    delta_theta[0][1] = -q[2];
    delta_theta[0][2] = q[1];
    delta_theta[1][0] = q[2];
    delta_theta[1][1] = 1;
    delta_theta[1][2] = -q[0];
    delta_theta[2][0] = -q[1];
    delta_theta[2][1] = q[0];
    delta_theta[2][2] = 1;

    vnl_svd<double> svd_delta_theta(delta_theta.GetVnlMatrix());

    // convert vnl matrices to itk matrices...
    Matrix3x3 U;
    Matrix3x3 V;

    for (int i = 0; i < 3; ++i)
    {
      for (int j = 0; j < 3; ++j)
      {
        U[i][j] = svd_delta_theta.U()[i][j];
        V[i][j] = svd_delta_theta.V()[i][j];
      }
    }

    Matrix3x3 delta_R = U * V.GetTranspose();

    // update rotation
    TransformationR = delta_R * TransformationR;

    // update translation
    TransformationT = delta_R * TransformationT + delta_t;

    // update moving points
    mitk::AnisotropicRegistrationCommon::TransformPoints(X, X_transformedNew, TransformationR, TransformationT);
    // calculate config change
    config_change = CalculateConfigChange(X_transformed, X_transformedNew);

    // swap the pointers the old set for the next iteration is
    // the new set of the last iteration
    vtkPoints *tmp = X_transformed;
    X_transformed = X_transformedNew;
    X_transformedNew = tmp;

  } while (config_change > Threshold && n < MaxIterations);

  // calculate FRE with current transform
  FRE = ComputeWeightedFRE(X, Y, Sigma_X, Sigma_Y, m_FRENormalizationFactor, W, TransformationR, TransformationT);

  MITK_DEBUG << "FRE after algorithm (prior to check with initial): " << FRE;

  // compare with FRE_initial
  if (initialFRE < FRE)
  {
    MITK_WARN << "FRE did not improve in anisotropic point registration function";
    TransformationR = initial_TransformationR;
    TransformationT = initial_TransformationT;
    FRE = initialFRE;
  }

  MITK_DEBUG << "FRE final: " << FRE;

  X_transformed->Delete();
  X_transformedNew->Delete();
}