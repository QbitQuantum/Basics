PoissonFormulation::PoissonFormulation(int spaceDim, bool useConformingTraces, PoissonFormulationChoice formulationChoice)
{
  _spaceDim = spaceDim;

  if (formulationChoice == ULTRAWEAK)
  {
    Space tauSpace = (spaceDim > 1) ? HDIV : HGRAD;
    Space phi_hat_space = useConformingTraces ? HGRAD : L2;
    Space psiSpace = (spaceDim > 1) ? VECTOR_L2 : L2;

    // fields
    VarPtr phi;
    VarPtr psi;

    // traces
    VarPtr phi_hat, psi_n_hat;

    // tests
    VarPtr q;
    VarPtr tau;

    VarFactoryPtr vf = VarFactory::varFactory();
    phi = vf->fieldVar(S_PHI);
    psi = vf->fieldVar(S_PSI, psiSpace);

    TFunctionPtr<double> parity = TFunction<double>::sideParity();
    
    if (spaceDim > 1)
      phi_hat = vf->traceVar(S_PHI_HAT, phi, phi_hat_space);
    else
      phi_hat = vf->fluxVar(S_PHI_HAT, phi * (Function::normal_1D() * parity), phi_hat_space); // for spaceDim==1, the "normal" component is in the flux-ness of phi_hat (it's a plus or minus 1)

    TFunctionPtr<double> n = TFunction<double>::normal();

    if (spaceDim > 1)
      psi_n_hat = vf->fluxVar(S_PSI_N_HAT, psi * (n * parity));
    else
      psi_n_hat = vf->fluxVar(S_PSI_N_HAT, psi * (Function::normal_1D() * parity));

    q = vf->testVar(S_Q, HGRAD);
    tau = vf->testVar(S_TAU, tauSpace);

    _poissonBF = Teuchos::rcp( new BF(vf) );

    if (spaceDim==1)
    {
      // for spaceDim==1, the "normal" component is in the flux-ness of phi_hat (it's a plus or minus 1)
      _poissonBF->addTerm(phi, tau->dx());
      _poissonBF->addTerm(psi, tau);
      _poissonBF->addTerm(-phi_hat, tau);

      _poissonBF->addTerm(-psi, q->dx());
      _poissonBF->addTerm(psi_n_hat, q);
    }
    else
    {
      _poissonBF->addTerm(phi, tau->div());
      _poissonBF->addTerm(psi, tau);
      _poissonBF->addTerm(-phi_hat, tau->dot_normal());

      _poissonBF->addTerm(-psi, q->grad());
      _poissonBF->addTerm(psi_n_hat, q);
    }
  }
  else if ((formulationChoice == PRIMAL) || (formulationChoice == CONTINUOUS_GALERKIN))
  {
    // field
    VarPtr phi;
    
    // flux
    VarPtr psi_n_hat;
    
    // tests
    VarPtr q;
    
    VarFactoryPtr vf = VarFactory::varFactory();
    phi = vf->fieldVar(S_PHI, HGRAD);
    
    TFunctionPtr<double> parity = TFunction<double>::sideParity();
    TFunctionPtr<double> n = TFunction<double>::normal();
    
    if (formulationChoice == PRIMAL)
    {
      if (spaceDim > 1)
        psi_n_hat = vf->fluxVar(S_PSI_N_HAT, phi->grad() * (n * parity));
      else
        psi_n_hat = vf->fluxVar(S_PSI_N_HAT, phi->dx() * (Function::normal_1D() * parity));
    }
    q = vf->testVar(S_Q, HGRAD);
    
    _poissonBF = BF::bf(vf);
    _poissonBF->addTerm(-phi->grad(), q->grad());

    if (formulationChoice == CONTINUOUS_GALERKIN)
    {
      FunctionPtr boundaryIndicator = Function::meshBoundaryCharacteristic();
      _poissonBF->addTerm(phi->grad() * n, boundaryIndicator * q);
    }
    else // primal
    {
      _poissonBF->addTerm(psi_n_hat, q);
    }
  }
  else
  {
    TEUCHOS_TEST_FOR_EXCEPTION(true, std::invalid_argument, "Unsupported PoissonFormulationChoice");
  }
}