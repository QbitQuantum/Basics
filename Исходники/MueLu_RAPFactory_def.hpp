  void RAPFactory<Scalar, LocalOrdinal, GlobalOrdinal, Node>::Build(Level& fineLevel, Level& coarseLevel) const {
    {
      FactoryMonitor m(*this, "Computing Ac", coarseLevel);
      std::ostringstream levelstr;
      levelstr << coarseLevel.GetLevelID();

      TEUCHOS_TEST_FOR_EXCEPTION(hasDeclaredInput_==false, Exceptions::RuntimeError,
                                 "MueLu::RAPFactory::Build(): CallDeclareInput has not been called before Build!");

      // Set "Keeps" from params
      const Teuchos::ParameterList& pL = GetParameterList();
      if (pL.get<bool>("Keep AP Pattern"))
        coarseLevel.Keep("AP Pattern",  this);
      if (pL.get<bool>("Keep RAP Pattern"))
        coarseLevel.Keep("RAP Pattern", this);

      RCP<Matrix> A = Get< RCP<Matrix> >(fineLevel,   "A");
      RCP<Matrix> P = Get< RCP<Matrix> >(coarseLevel, "P"), AP, Ac;

      // Reuse pattern if available (multiple solve)
      if (coarseLevel.IsAvailable("AP Pattern", this)) {
        GetOStream(Runtime0) << "Ac: Using previous AP pattern" << std::endl;

        AP = Get< RCP<Matrix> >(coarseLevel, "AP Pattern");
      }

      {
        SubFactoryMonitor subM(*this, "MxM: A x P", coarseLevel);

        AP = Utils::Multiply(*A, false, *P, false, AP, GetOStream(Statistics2),true,true,std::string("MueLu::A*P-")+levelstr.str());
      }
      if (pL.get<bool>("Keep AP Pattern"))
        Set(coarseLevel, "AP Pattern", AP);

      // Reuse coarse matrix memory if available (multiple solve)
      if (coarseLevel.IsAvailable("RAP Pattern", this)) {
        GetOStream(Runtime0) << "Ac: Using previous RAP pattern" << std::endl;

        Ac = Get< RCP<Matrix> >(coarseLevel, "RAP Pattern");
        // Some eigenvalue may have been cached with the matrix in the previous run.
        // As the matrix values will be updated, we need to reset the eigenvalue.
        Ac->SetMaxEigenvalueEstimate(-Teuchos::ScalarTraits<SC>::one());
      }

      // If we do not modify matrix later, allow optimization of storage.
      // This is necessary for new faster Epetra MM kernels.
      bool doOptimizeStorage = !pL.get<bool>("RepairMainDiagonal");

      const bool doTranspose    = true;
      const bool doFillComplete = true;
      if (pL.get<bool>("transpose: use implicit") == true) {
        SubFactoryMonitor m2(*this, "MxM: P' x (AP) (implicit)", coarseLevel);
        Ac = Utils::Multiply(*P,  doTranspose, *AP, !doTranspose, Ac, GetOStream(Statistics2), doFillComplete, doOptimizeStorage,std::string("MueLu::R*(AP)-implicit-")+levelstr.str());

      } else {
        RCP<Matrix> R = Get< RCP<Matrix> >(coarseLevel, "R");

        SubFactoryMonitor m2(*this, "MxM: R x (AP) (explicit)", coarseLevel);
        Ac = Utils::Multiply(*R, !doTranspose, *AP, !doTranspose, Ac, GetOStream(Statistics2), doFillComplete, doOptimizeStorage,std::string("MueLu::R*(AP)-explicit-")+levelstr.str());
      }

      CheckRepairMainDiagonal(Ac);

      if (IsPrint(Statistics1)) {
        RCP<ParameterList> params = rcp(new ParameterList());;
        params->set("printLoadBalancingInfo", true);
        params->set("printCommInfo",          true);
        GetOStream(Statistics1) << PerfUtils::PrintMatrixInfo(*Ac, "Ac", params);
      }

      Set(coarseLevel, "A",           Ac);
      if (pL.get<bool>("Keep RAP Pattern"))
        Set(coarseLevel, "RAP Pattern", Ac);
    }

    if (transferFacts_.begin() != transferFacts_.end()) {
      SubFactoryMonitor m(*this, "Projections", coarseLevel);

      // call Build of all user-given transfer factories
      for (std::vector<RCP<const FactoryBase> >::const_iterator it = transferFacts_.begin(); it != transferFacts_.end(); ++it) {
        RCP<const FactoryBase> fac = *it;
        GetOStream(Runtime0) << "RAPFactory: call transfer factory: " << fac->description() << std::endl;
        fac->CallBuild(coarseLevel);
        // Coordinates transfer is marginally different from all other operations
        // because it is *optional*, and not required. For instance, we may need
        // coordinates only on level 4 if we start repartitioning from that level,
        // but we don't need them on level 1,2,3. As our current Hierarchy setup
        // assumes propagation of dependencies only through three levels, this
        // means that we need to rely on other methods to propagate optional data.
        //
        // The method currently used is through RAP transfer factories, which are
        // simply factories which are called at the end of RAP with a single goal:
        // transfer some fine data to coarser level. Because these factories are
        // kind of outside of the mainline factories, they behave different. In
        // particular, we call their Build method explicitly, rather than through
        // Get calls. This difference is significant, as the Get call is smart
        // enough to know when to release all factory dependencies, and Build is
        // dumb. This led to the following CoordinatesTransferFactory sequence:
        // 1. Request level 0
        // 2. Request level 1
        // 3. Request level 0
        // 4. Release level 0
        // 5. Release level 1
        //
        // The problem is missing "6. Release level 0". Because it was missing,
        // we had outstanding request on "Coordinates", "Aggregates" and
        // "CoarseMap" on level 0.
        //
        // This was fixed by explicitly calling Release on transfer factories in
        // RAPFactory. I am still unsure how exactly it works, but now we have
        // clear data requests for all levels.
        coarseLevel.Release(*fac);
      }
    }

  }