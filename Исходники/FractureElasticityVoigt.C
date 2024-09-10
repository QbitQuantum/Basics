bool FractureElasticityVoigt::evalStress (double lambda, double mu, double Gc,
                                          const SymmTensor& epsil, double* Phi,
                                          SymmTensor* sigma, Matrix* dSdE,
                                          bool postProc, bool printElm) const
{
  PROFILE3("FractureEl::evalStress");

  unsigned short int a = 0, b = 0;

  // Define a Lambda-function to set up the isotropic constitutive matrix
  auto&& setIsotropic = [this,a,b](Matrix& C, double lambda, double mu) mutable
  {
    for (a = 1; a <= C.rows(); a++)
      if (a > nsd)
        C(a,a) = mu;
      else
      {
        C(a,a) = 2.0*mu;
        for (b = 1; b <= nsd; b++)
          C(a,b) += lambda;
      }
  };

  // Define some material constants
  double trEps = epsil.trace();
  double C0 = trEps >= -epsZ ? Gc*lambda : lambda;
  double Cp = Gc*mu;

  if (trEps >= -epsZ && trEps <= epsZ)
  {
    // No strains, stress free configuration
    Phi[0] = 0.0;
    if (postProc)
      Phi[1] = Phi[2] = Phi[3] = 0.0;
    if (sigma)
      *sigma = 0.0;
    if (dSdE)
      setIsotropic(*dSdE,C0,Cp);
    return true;
  }

  // Calculate principal strains and the associated directions
  Vec3 eps;
  std::vector<SymmTensor> M(nsd,SymmTensor(nsd));
  {
    PROFILE4("Tensor::principal");
    if (!epsil.principal(eps,M.data()))
      return false;
  }

  // Split the strain tensor into positive and negative parts
  SymmTensor ePos(nsd), eNeg(nsd);
  for (a = 0; a < nsd; a++)
    if (eps[a] > 0.0)
      ePos += eps[a]*M[a];
    else if (eps[a] < 0.0)
      eNeg += eps[a]*M[a];

  if (sigma)
  {
    // Evaluate the stress tensor
    *sigma = C0*trEps;
    *sigma += 2.0*mu*(Gc*ePos + eNeg);
  }

  // Evaluate the tensile energy
  Phi[0] = mu*(ePos*ePos).trace();
  if (trEps > 0.0) Phi[0] += 0.5*lambda*trEps*trEps;
  if (postProc)
  {
    // Evaluate the compressive energy
    Phi[1] = mu*(eNeg*eNeg).trace();
    if (trEps < 0.0) Phi[1] += 0.5*lambda*trEps*trEps;
    // Evaluate the total strain energy
    Phi[2] = Gc*Phi[0] + Phi[1];
    // Evaluate the bulk energy
    Phi[3] = Gc*(Phi[0] + Phi[1]);
  }
  else if (sigmaC > 0.0) // Evaluate the crack driving function
    Phi[0] = this->MieheCrit56(eps,lambda,mu);

#if INT_DEBUG > 4
  std::cout <<"eps_p = "<< eps <<"\n";
  for (a = 0; a < nsd; a++)
    std::cout <<"M("<< 1+a <<") =\n"<< M[a];
  std::cout <<"ePos =\n"<< ePos <<"eNeg =\n"<< eNeg;
  if (sigma) std::cout <<"sigma =\n"<< *sigma;
  std::cout <<"Phi = "<< Phi[0];
  if (postProc) std::cout <<" "<< Phi[1] <<" "<< Phi[2] <<" "<< Phi[3];
  std::cout << std::endl;
#else
  if (printElm)
  {
    std::cout <<"g(c) = "<< Gc
              <<"\nepsilon =\n"<< epsil <<"eps_p = "<< eps
              <<"\nePos =\n"<< ePos <<"eNeg =\n"<< eNeg;
    if (sigma) std::cout <<"sigma =\n"<< *sigma;
    std::cout <<"Phi = "<< Phi[0];
    if (postProc) std::cout <<" "<< Phi[1] <<" "<< Phi[2] <<" "<< Phi[3];
    std::cout << std::endl;
  }
#endif

  if (!dSdE)
    return true;
  else if (eps[0] == eps[nsd-1])
  {
    // Hydrostatic pressure
    setIsotropic(*dSdE, C0, eps.x > 0.0 ? Cp : mu);
    return true;
  }

  typedef unsigned short int s_ind; // Convenience type definition

  // Define a Lambda-function to calculate (lower triangle of) the matrix Qa
  auto&& getQ = [this](Matrix& Q, const SymmTensor& Ma, double C)
  {
    if (C == 0.0) return;

    auto&& Mult = [Ma](s_ind i, s_ind j, s_ind k, s_ind l)
    {
      return Ma(i,j)*Ma(k,l);
    };

    s_ind i, j, k, l, is, js;

    // Normal stresses and strains
    for (i = 1; i <= nsd; i++)
      for (j = 1; j <= i; j++)
        Q(i,j) += C*Mult(i,i,j,j);

    is = nsd+1;
    for (i = 1; i < nsd; i++)
      for (j = i+1; j <= nsd; j++, is++)
      {
        // Shear stress coupled to normal strain
        for (k = 1; k <= nsd; k++)
          Q(is,k) += C*Mult(i,j,k,k);

        // Shear stress coupled to shear strain
        js = nsd+1;
        for (k = 1; k < nsd; k++)
          for (l = k+1; js <= is; l++, js++)
            Q(is,js) += C*Mult(i,j,k,l);
      }
  };

  // Define a Lambda-function to calculate (lower triangle of) the matrix Gab
  auto&& getG = [this](Matrix& G, const SymmTensor& Ma,
                       const SymmTensor& Mb, double C)
  {
    if (C == 0.0) return;

    auto&& Mult = [Ma,Mb](s_ind i, s_ind j, s_ind k, s_ind l)
    {
      return Ma(i,k)*Mb(j,l) + Ma(i,l)*Mb(j,k) +
             Mb(i,k)*Ma(j,l) + Mb(i,l)*Ma(j,k);
    };

    s_ind i, j, k, l, is, js;

    // Normal stresses and strains
    for (i = 1; i <= nsd; i++)
      for (j = 1; j <= i; j++)
        G(i,j) += C*Mult(i,i,j,j);

    is = nsd+1;
    for (i = 1; i < nsd; i++)
      for (j = i+1; j <= nsd; j++, is++)
      {
        // Shear stress coupled to normal strain
        for (k = 1; k <= nsd; k++)
          G(is,k) += C*Mult(i,j,k,k);

        // Shear stress coupled to shear strain
        js = nsd+1;
        for (k = 1; k < nsd; k++)
          for (l = k+1; js <= is; l++, js++)
            G(is,js) += C*Mult(i,j,k,l);
      }
  };

  // Evaluate the stress tangent assuming Voigt notation and symmetry
  for (a = 1; a <= nsd; a++)
    for (b = 1; b <= a; b++)
      (*dSdE)(a,b) = C0;

  for (a = 0; a < nsd; a++)
  {
    double C1 = eps[a] >= 0.0 ? Cp : mu;
    getQ(*dSdE, M[a], 2.0*C1);
    if (eps[a] != 0.0)
      for (b = 0; b < nsd; b++)
        if (a != b && eps[a] != eps[b])
          getG(*dSdE,M[a],M[b],C1/(1.0-eps[b]/eps[a]));
  }

  // Account for symmetry
  for (b = 2; b <= dSdE->rows(); b++)
    for (a = 1; a < b; a++)
      (*dSdE)(a,b) = (*dSdE)(b,a);

  return true;
}