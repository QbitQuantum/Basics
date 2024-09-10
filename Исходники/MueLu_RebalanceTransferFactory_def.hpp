  void RebalanceTransferFactory<Scalar, LocalOrdinal, GlobalOrdinal, Node, LocalMatOps>::Build(Level& fineLevel, Level& coarseLevel) const {
    FactoryMonitor m(*this, "Build", coarseLevel);

    const ParameterList& pL = GetParameterList();

    int implicit   = !pL.get<bool>("repartition: rebalance P and R");
    int writeStart = pL.get<int> ("write start");
    int writeEnd   = pL.get<int> ("write end");

    if (writeStart == 0 && fineLevel.GetLevelID() == 0 && writeStart <= writeEnd && IsAvailable(fineLevel, "Coordinates")) {
      std::string fileName = "coordinates_level_0.m";
      RCP<MultiVector> fineCoords = fineLevel.Get< RCP<MultiVector> >("Coordinates");
      if (fineCoords != Teuchos::null)
        Utils::Write(fileName, *fineCoords);
    }

    RCP<const Import> importer = Get<RCP<const Import> >(coarseLevel, "Importer");
    if (implicit) {
      // Save the importer, we'll need it for solve
      coarseLevel.Set("Importer", importer, NoFactory::get());
    }

    RCP<ParameterList> params = rcp(new ParameterList());;
    params->set("printLoadBalancingInfo", true);
    params->set("printCommInfo",          true);

    std::string transferType = pL.get<std::string>("type");
    if (transferType == "Interpolation") {
      RCP<Matrix> originalP = Get< RCP<Matrix> >(coarseLevel, "P");

      {
        // This line must be after the Get call
        SubFactoryMonitor m1(*this, "Rebalancing prolongator", coarseLevel);

        if (implicit || importer.is_null()) {
          GetOStream(Runtime0) << "Using original prolongator" << std::endl;
          Set(coarseLevel, "P", originalP);

        } else {
          // P is the transfer operator from the coarse grid to the fine grid.
          // P must transfer the data from the newly reordered coarse A to the
          // (unchanged) fine A.  This means that the domain map (coarse) of P
          // must be changed according to the new partition. The range map
          // (fine) is kept unchanged.
          //
          // The domain map of P must match the range map of R.  See also note
          // below about domain/range map of R and its implications for P.
          //
          // To change the domain map of P, P needs to be fillCompleted again
          // with the new domain map.  To achieve this, P is copied into a new
          // matrix that is not fill-completed.  The doImport() operation is
          // just used here to make a copy of P: the importer is trivial and
          // there is no data movement involved.  The reordering actually
          // happens during the fillComplete() with domainMap == importer->getTargetMap().
          RCP<Matrix> rebalancedP = originalP;
          RCP<const CrsMatrixWrap> crsOp = rcp_dynamic_cast<const CrsMatrixWrap>(originalP);
          TEUCHOS_TEST_FOR_EXCEPTION(crsOp == Teuchos::null, Exceptions::BadCast, "Cast from Xpetra::Matrix to Xpetra::CrsMatrixWrap failed");

          RCP<CrsMatrix> rebalancedP2 = crsOp->getCrsMatrix();
          TEUCHOS_TEST_FOR_EXCEPTION(rebalancedP2 == Teuchos::null, std::runtime_error, "Xpetra::CrsMatrixWrap doesn't have a CrsMatrix");

          {
            SubFactoryMonitor subM(*this, "Rebalancing prolongator -- fast map replacement", coarseLevel);

            RCP<const Import> newImporter = ImportFactory::Build(importer->getTargetMap(), rebalancedP->getColMap());
            rebalancedP2->replaceDomainMapAndImporter(importer->getTargetMap(), newImporter);
          }

          ///////////////////////// EXPERIMENTAL
          // TODO FIXME somehow we have to transfer the striding information of the permuted domain/range maps.
          // That is probably something for an external permutation factory
          //   if (originalP->IsView("stridedMaps"))
          //     rebalancedP->CreateView("stridedMaps", originalP);
          ///////////////////////// EXPERIMENTAL

          Set(coarseLevel, "P", rebalancedP);

          if (IsPrint(Statistics1))
            GetOStream(Statistics1) << PerfUtils::PrintMatrixInfo(*rebalancedP, "P (rebalanced)", params);
        }
      }

      if (importer.is_null()) {
        if (IsAvailable(coarseLevel, "Nullspace"))
          Set(coarseLevel, "Nullspace", Get<RCP<MultiVector> >(coarseLevel, "Nullspace"));

        if (pL.isParameter("Coordinates") && pL.get< RCP<const FactoryBase> >("Coordinates") != Teuchos::null)
          if (IsAvailable(coarseLevel, "Coordinates"))
            Set(coarseLevel, "Coordinates", Get< RCP<MultiVector> >(coarseLevel, "Coordinates"));

        return;
      }

      if (pL.isParameter("Coordinates") &&
          pL.get< RCP<const FactoryBase> >("Coordinates") != Teuchos::null &&
          IsAvailable(coarseLevel, "Coordinates")) {
        RCP<MultiVector> coords = Get<RCP<MultiVector> >(coarseLevel, "Coordinates");

        // This line must be after the Get call
        SubFactoryMonitor subM(*this, "Rebalancing coordinates", coarseLevel);

        LO nodeNumElts = coords->getMap()->getNodeNumElements();

        // If a process has no matrix rows, then we can't calculate blocksize using the formula below.
        LO myBlkSize = 0, blkSize = 0;
        if (nodeNumElts > 0)
          myBlkSize = importer->getSourceMap()->getNodeNumElements() / nodeNumElts;
        maxAll(coords->getMap()->getComm(), myBlkSize, blkSize);

        RCP<const Import> coordImporter;
        if (blkSize == 1) {
          coordImporter = importer;

        } else {
          // NOTE: there is an implicit assumption here: we assume that dof any node are enumerated consequently
          // Proper fix would require using decomposition similar to how we construct importer in the
          // RepartitionFactory
          RCP<const Map> origMap   = coords->getMap();
          GO             indexBase = origMap->getIndexBase();

          ArrayView<const GO> OEntries   = importer->getTargetMap()->getNodeElementList();
          LO                  numEntries = OEntries.size()/blkSize;
          ArrayRCP<GO> Entries(numEntries);
          for (LO i = 0; i < numEntries; i++)
            Entries[i] = (OEntries[i*blkSize]-indexBase)/blkSize + indexBase;

          RCP<const Map> targetMap = MapFactory::Build(origMap->lib(), origMap->getGlobalNumElements(), Entries(), indexBase, origMap->getComm());
          coordImporter = ImportFactory::Build(origMap, targetMap);
        }

        RCP<MultiVector> permutedCoords  = MultiVectorFactory::Build(coordImporter->getTargetMap(), coords->getNumVectors());
        permutedCoords->doImport(*coords, *coordImporter, Xpetra::INSERT);

        if (pL.get<bool>("useSubcomm") == true)
          permutedCoords->replaceMap(permutedCoords->getMap()->removeEmptyProcesses());

        Set(coarseLevel, "Coordinates", permutedCoords);

        std::string fileName = "rebalanced_coordinates_level_" + toString(coarseLevel.GetLevelID()) + ".m";
        if (writeStart <= coarseLevel.GetLevelID() && coarseLevel.GetLevelID() <= writeEnd && permutedCoords->getMap() != Teuchos::null)
          Utils::Write(fileName, *permutedCoords);
      }

      if (IsAvailable(coarseLevel, "Nullspace")) {
        RCP<MultiVector> nullspace = Get< RCP<MultiVector> >(coarseLevel, "Nullspace");

        // This line must be after the Get call
        SubFactoryMonitor subM(*this, "Rebalancing nullspace", coarseLevel);

        RCP<MultiVector> permutedNullspace = MultiVectorFactory::Build(importer->getTargetMap(), nullspace->getNumVectors());
        permutedNullspace->doImport(*nullspace, *importer, Xpetra::INSERT);

        if (pL.get<bool>("useSubcomm") == true)
          permutedNullspace->replaceMap(permutedNullspace->getMap()->removeEmptyProcesses());

        Set(coarseLevel, "Nullspace", permutedNullspace);
      }

    } else {
      if (pL.get<bool>("transpose: use implicit") == false) {
        RCP<Matrix> originalR = Get< RCP<Matrix> >(coarseLevel, "R");

        SubFactoryMonitor m2(*this, "Rebalancing restriction", coarseLevel);

        if (implicit || importer.is_null()) {
          GetOStream(Runtime0) << "Using original restrictor" << std::endl;
          Set(coarseLevel, "R", originalR);

        } else {
          RCP<Matrix> rebalancedR;
          {
            SubFactoryMonitor subM(*this, "Rebalancing restriction -- fusedImport", coarseLevel);

            RCP<Map> dummy;         // meaning: use originalR's domain map.
            rebalancedR = MatrixFactory::Build(originalR, *importer, dummy, importer->getTargetMap());
          }
          Set(coarseLevel, "R", rebalancedR);

          ///////////////////////// EXPERIMENTAL
          // TODO FIXME somehow we have to transfer the striding information of the permuted domain/range maps.
          // That is probably something for an external permutation factory
          // if (originalR->IsView("stridedMaps"))
          //   rebalancedR->CreateView("stridedMaps", originalR);
          ///////////////////////// EXPERIMENTAL

          if (IsPrint(Statistics1))
            GetOStream(Statistics1) << PerfUtils::PrintMatrixInfo(*rebalancedR, "R (rebalanced)", params);
        }
      }
    }
  }