  void SaPFactory<Scalar, LocalOrdinal, GlobalOrdinal, Node>::BuildP(Level &fineLevel, Level &coarseLevel) const {
    FactoryMonitor m(*this, "Prolongator smoothing", coarseLevel);
    std::ostringstream levelstr;
    levelstr << coarseLevel.GetLevelID();

    typedef typename Teuchos::ScalarTraits<SC>::magnitudeType Magnitude;

    // Get default tentative prolongator factory
    // Getting it that way ensure that the same factory instance will be used for both SaPFactory and NullspaceFactory.
    // -- Warning: Do not use directly initialPFact_. Use initialPFact instead everywhere!
    RCP<const FactoryBase> initialPFact = GetFactory("P");
    if (initialPFact == Teuchos::null) { initialPFact = coarseLevel.GetFactoryManager()->GetFactory("Ptent"); }

    // Level Get
    RCP<Matrix> A     = Get< RCP<Matrix> >(fineLevel, "A");
    RCP<Matrix> Ptent = coarseLevel.Get< RCP<Matrix> >("P", initialPFact.get());

    if(restrictionMode_) {
      SubFactoryMonitor m2(*this, "Transpose A", coarseLevel);
      A = Utils2::Transpose(*A, true); // build transpose of A explicitely
    }

    //Build final prolongator
    RCP<Matrix> finalP; // output

    const ParameterList & pL = GetParameterList();
    Scalar dampingFactor = as<Scalar>(pL.get<double>("sa: damping factor"));
    LO maxEigenIterations = as<LO>(pL.get<int>("sa: eigenvalue estimate num iterations"));
    bool estimateMaxEigen = pL.get<bool>("sa: calculate eigenvalue estimate");
    if (dampingFactor != Teuchos::ScalarTraits<Scalar>::zero()) {

      Scalar lambdaMax;
      {
        SubFactoryMonitor m2(*this, "Eigenvalue estimate", coarseLevel);
        lambdaMax = A->GetMaxEigenvalueEstimate();
        if (lambdaMax == -Teuchos::ScalarTraits<SC>::one() || estimateMaxEigen) {
          GetOStream(Statistics1) << "Calculating max eigenvalue estimate now (max iters = "<< maxEigenIterations << ")" << std::endl;
          Magnitude stopTol = 1e-4;
          lambdaMax = Utils::PowerMethod(*A, true, maxEigenIterations, stopTol);
          A->SetMaxEigenvalueEstimate(lambdaMax);
        } else {
          GetOStream(Statistics1) << "Using cached max eigenvalue estimate" << std::endl;
        }
        GetOStream(Statistics0) << "Prolongator damping factor = " << dampingFactor/lambdaMax << " (" << dampingFactor << " / " << lambdaMax << ")" << std::endl;
      }

      {
        SubFactoryMonitor m2(*this, "Fused (I-omega*D^{-1} A)*Ptent", coarseLevel);
        Teuchos::RCP<Vector> invDiag = Utils::GetMatrixDiagonalInverse(*A);

        SC omega = dampingFactor / lambdaMax;

        // finalP = Ptent + (I - \omega D^{-1}A) Ptent
        finalP = Utils::Jacobi(omega, *invDiag, *A, *Ptent, finalP, GetOStream(Statistics2),std::string("MueLu::SaP-")+levelstr.str());
      }

    } else {
      finalP = Ptent;
    }

    // Level Set
    if (!restrictionMode_) {
      // prolongation factory is in prolongation mode
      Set(coarseLevel, "P", finalP);

      // NOTE: EXPERIMENTAL
      if (Ptent->IsView("stridedMaps"))
        finalP->CreateView("stridedMaps", Ptent);

    } else {
      // prolongation factory is in restriction mode
      RCP<Matrix> R = Utils2::Transpose(*finalP, true); // use Utils2 -> specialization for double
      Set(coarseLevel, "R", R);

      // NOTE: EXPERIMENTAL
      if (Ptent->IsView("stridedMaps"))
        R->CreateView("stridedMaps", Ptent, true);
    }

    if (IsPrint(Statistics1)) {
      RCP<ParameterList> params = rcp(new ParameterList());
      params->set("printLoadBalancingInfo", true);
      params->set("printCommInfo",          true);
      GetOStream(Statistics1) << PerfUtils::PrintMatrixInfo(*finalP, (!restrictionMode_ ? "P" : "R"), params);
    }

  } //Build()