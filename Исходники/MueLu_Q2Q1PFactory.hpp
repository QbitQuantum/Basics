  void Q2Q1PFactory<Scalar, LocalOrdinal, GlobalOrdinal, Node>::BuildP(Level& fineLevel, Level& coarseLevel) const {
    FactoryMonitor m(*this, "Build", coarseLevel);

    RCP<Matrix> A = Get< RCP<Matrix> >(fineLevel, "A");

    RCP<const Map>        rowMap  = A->getRowMap();

    Xpetra::global_size_t N = rowMap->getGlobalNumElements();

    int V;
    size_t n = as<size_t>(sqrt(N));
    if (N == n*n) {
      // pressure mode
      V = 1;
      GetOStream(Runtime1) << "Pressure mode" << std::endl;

    } else {
      n = as<size_t>(sqrt(N/2));

      if (N == 2*n*n) {
        // velocity mode
        V = 2;
        GetOStream(Runtime1) << "Velocity mode" << std::endl;
      } else {
        throw Exceptions::RuntimeError("Matrix size (" + toString(N) + ") is incompatible with both velocity and pressure");
      }
    }

    const int             C = 4;
    Xpetra::global_size_t nc = (n-1)/C + 1;
    TEUCHOS_TEST_FOR_EXCEPTION(C*(nc-1)+1 != n, Exceptions::InvalidArgument, "Incorrect dim size: " << n);


    ArrayView<const GO> elementList = rowMap->getNodeElementList();
    GO indexBase = rowMap->getIndexBase();

    // Calculate offsets
    GO offset       = (V == 2 ? 0 : 2*(2*n -1)*(2*n -1));
    GO coarseOffset = (V == 2 ? 0 : 2*(2*nc-1)*(2*nc-1));

    GetOStream(Runtime1) << "offset = " << offset << ", coarseOffset = " << coarseOffset << std::endl;

    Array<GO> coarseList;
    for (LO k = 0; k < elementList.size(); k += V) {
      GO GID = elementList[k] - offset - indexBase;
      GO i = (GID / V) % n, ii = i/C;
      GO j = (GID / V) / n, jj = j/C;

      if (i % C == 0 && j % C == 0)
        for (int q = 0; q < V; q++)
          coarseList.push_back(V*(jj*nc + ii) + q + coarseOffset);
    }

    typedef Teuchos::ScalarTraits<SC> STS;
    SC one = STS::one();

    Xpetra::global_size_t INVALID = Teuchos::OrdinalTraits<Xpetra::global_size_t>::invalid();
    std::vector<size_t> stridingInfo(1,1);
    const int           stridedBlockId = -1;
    RCP<Map>         coarseMap       = StridedMapFactory ::Build(rowMap->lib(), INVALID, coarseList, indexBase, stridingInfo, rowMap->getComm(), stridedBlockId, coarseOffset);
    RCP<MultiVector> coarseNullspace = MultiVectorFactory::Build(coarseMap, 1);
    coarseNullspace->putScalar(one);

    int nnzEstimate = 4;
    RCP<Matrix> P = MatrixFactory::Build(rowMap, coarseMap, nnzEstimate);

    Array<GO> inds(nnzEstimate), inds1(nnzEstimate);
    Array<SC> vals(nnzEstimate, one);
    int sz;
    for (LO k = 0; k < elementList.size(); k += V) {
      GO GID = elementList[k] - offset - indexBase;
      GO i = (GID/V) % n, ii = i/C;
      GO j = (GID/V) / n, jj = j/C;

      if        (i % C == 0 && j % C == 0) {
        sz = 1;
        inds[0] =  jj   *nc + ii  ;

      } else if (i % C == 0 && j % C != 0) {
        sz = 2;
        inds[0] =  jj   *nc + ii  ;
        inds[1] = (jj+1)*nc + ii  ;

      } else if (i % C != 0 && j % C == 0) {
        sz = 2;
        inds[0] =  jj   *nc + ii  ;
        inds[1] =  jj   *nc + ii+1;

      } else {
        sz = 4;
        inds[0] =  jj   *nc + ii  ;
        inds[1] =  jj   *nc + ii+1;
        inds[2] = (jj+1)*nc + ii  ;
        inds[3] = (jj+1)*nc + ii+1;
      }

      for (int q = 0; q < V; q++) {
        for (int p = 0; p < sz; p++)
          inds1[p] = V*inds[p]+q + coarseOffset;

        P->insertGlobalValues(elementList[k]+q, inds1.view(0,sz), vals.view(0,sz));
      }
    }

    P->fillComplete(coarseMap, A->getDomainMap());

    // Level Set
    Set(coarseLevel, "Nullspace", coarseNullspace);
    Set(coarseLevel, "P",         P);
    Set(fineLevel,   "CoarseMap", coarseMap);

    if (IsPrint(Statistics1)) {
      RCP<ParameterList> params = rcp(new ParameterList());
      params->set("printLoadBalancingInfo", true);
      params->set("printCommInfo",          true);
      GetOStream(Statistics1) << PerfUtils::PrintMatrixInfo(*P, "P", params);
    }

  }