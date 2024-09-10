  void RepartitionFactory<Scalar, LocalOrdinal, GlobalOrdinal, Node>::Build(Level& currentLevel) const {
    FactoryMonitor m(*this, "Build", currentLevel);

    const Teuchos::ParameterList & pL = GetParameterList();
    // Access parameters here to make sure that we set the parameter entry flag to "used" even in case of short-circuit evaluation.
    // TODO (JG): I don't really know if we want to do this.
    const int    startLevel          = pL.get<int>   ("repartition: start level");
    const LO     minRowsPerProcessor = pL.get<LO>    ("repartition: min rows per proc");
    const double nonzeroImbalance    = pL.get<double>("repartition: max imbalance");
    const bool   remapPartitions     = pL.get<bool>  ("repartition: remap parts");

    // TODO: We only need a CrsGraph. This class does not have to be templated on Scalar types.
    RCP<Matrix> A = Get< RCP<Matrix> >(currentLevel, "A");

    // ======================================================================================================
    // Determine whether partitioning is needed
    // ======================================================================================================
    // NOTE: most tests include some global communication, which is why we currently only do tests until we make
    // a decision on whether to repartition. However, there is value in knowing how "close" we are to having to
    // rebalance an operator. So, it would probably be beneficial to do and report *all* tests.

    // Test1: skip repartitioning if current level is less than the specified minimum level for repartitioning
    if (currentLevel.GetLevelID() < startLevel) {
      GetOStream(Statistics0) << "Repartitioning?  NO:" <<
          "\n  current level = " << Teuchos::toString(currentLevel.GetLevelID()) <<
          ", first level where repartitioning can happen is " + Teuchos::toString(startLevel) << std::endl;

      Set<RCP<const Import> >(currentLevel, "Importer", Teuchos::null);
      return;
    }

    RCP<const Map> rowMap = A->getRowMap();

    // NOTE: Teuchos::MPIComm::duplicate() calls MPI_Bcast inside, so this is
    // a synchronization point. However, as we do MueLu_sumAll afterwards anyway, it
    // does not matter.
    RCP<const Teuchos::Comm<int> > origComm = rowMap->getComm();
    RCP<const Teuchos::Comm<int> > comm     = origComm->duplicate();

    // Test 2: check whether A is actually distributed, i.e. more than one processor owns part of A
    // TODO: this global communication can be avoided if we store the information with the matrix (it is known when matrix is created)
    // TODO: further improvements could be achieved when we use subcommunicator for the active set. Then we only need to check its size
    {
      int numActiveProcesses = 0;
      MueLu_sumAll(comm, Teuchos::as<int>((A->getNodeNumRows() > 0) ? 1 : 0), numActiveProcesses);

      if (numActiveProcesses == 1) {
        GetOStream(Statistics0) << "Repartitioning?  NO:" <<
            "\n  # processes with rows = " << Teuchos::toString(numActiveProcesses) << std::endl;

        Set<RCP<const Import> >(currentLevel, "Importer", Teuchos::null);
        return;
      }
    }

    bool test3 = false, test4 = false;
    std::string msg3, msg4;

    // Test3: check whether number of rows on any processor satisfies the minimum number of rows requirement
    // NOTE: Test2 ensures that repartitionning is not done when there is only one processor (it may or may not satisfy Test3)
    if (minRowsPerProcessor > 0) {
      LO numMyRows = Teuchos::as<LO>(A->getNodeNumRows()), minNumRows, LOMAX = Teuchos::OrdinalTraits<LO>::max();
      LO haveFewRows = (numMyRows < minRowsPerProcessor ? 1 : 0), numWithFewRows = 0;
      MueLu_sumAll(comm, haveFewRows, numWithFewRows);
      MueLu_minAll(comm, (numMyRows > 0 ? numMyRows : LOMAX), minNumRows);

      // TODO: we could change it to repartition only if the number of processors with numRows < minNumRows is larger than some
      // percentage of the total number. This way, we won't repartition if 2 out of 1000 processors don't have enough elements.
      // I'm thinking maybe 20% threshold. To implement, simply add " && numWithFewRows < .2*numProcs" to the if statement.
      if (numWithFewRows > 0)
        test3 = true;

      msg3 = "\n  min # rows per proc = " + Teuchos::toString(minNumRows) + ", min allowable = " + Teuchos::toString(minRowsPerProcessor);
    }

    // Test4: check whether the balance in the number of nonzeros per processor is greater than threshold
    if (!test3) {
      GO minNnz, maxNnz, numMyNnz = Teuchos::as<GO>(A->getNodeNumEntries());
      MueLu_maxAll(comm, numMyNnz,                           maxNnz);
      MueLu_minAll(comm, (numMyNnz > 0 ? numMyNnz : maxNnz), minNnz); // min nnz over all active processors
      double imbalance = Teuchos::as<double>(maxNnz)/minNnz;

      if (imbalance > nonzeroImbalance)
        test4 = true;

      msg4 = "\n  nonzero imbalance = " + Teuchos::toString(imbalance) + ", max allowable = " + Teuchos::toString(nonzeroImbalance);
    }

    if (!test3 && !test4) {
      GetOStream(Statistics0) << "Repartitioning?  NO:" << msg3 + msg4 << std::endl;

      Set<RCP<const Import> >(currentLevel, "Importer", Teuchos::null);
      return;
    }

    GetOStream(Statistics0) << "Repartitioning? YES:" << msg3 + msg4 << std::endl;

    GO                     indexBase = rowMap->getIndexBase();
    Xpetra::UnderlyingLib  lib       = rowMap->lib();
    int myRank   = comm->getRank();
    int numProcs = comm->getSize();

    RCP<const Teuchos::MpiComm<int> > tmpic = rcp_dynamic_cast<const Teuchos::MpiComm<int> >(comm);
    TEUCHOS_TEST_FOR_EXCEPTION(tmpic == Teuchos::null, Exceptions::RuntimeError, "Cannot cast base Teuchos::Comm to Teuchos::MpiComm object.");
    RCP<const Teuchos::OpaqueWrapper<MPI_Comm> > rawMpiComm = tmpic->getRawMpiComm();

    // ======================================================================================================
    // Calculate number of partitions
    // ======================================================================================================
    // FIXME Quick way to figure out how many partitions there should be (same algorithm as ML)
    // FIXME Should take into account nnz? Perhaps only when user is using min #nnz per row threshold.
    GO numPartitions;
    if (currentLevel.IsAvailable("number of partitions")) {
      numPartitions = currentLevel.Get<GO>("number of partitions");
      GetOStream(Warnings0) << "Using user-provided \"number of partitions\", the performance is unknown" << std::endl;

    } else {
      if (Teuchos::as<GO>(A->getGlobalNumRows()) < minRowsPerProcessor) {
        // System is too small, migrate it to a single processor
        numPartitions = 1;

      } else {
        // Make sure that each processor has approximately minRowsPerProcessor
        numPartitions = A->getGlobalNumRows() / minRowsPerProcessor;
      }
      numPartitions = std::min(numPartitions, Teuchos::as<GO>(numProcs));

      currentLevel.Set("number of partitions", numPartitions, NoFactory::get());
    }
    GetOStream(Statistics0) << "Number of partitions to use = " << numPartitions << std::endl;

    // ======================================================================================================
    // Construct decomposition vector
    // ======================================================================================================
    RCP<GOVector> decomposition;
    if (numPartitions == 1) {
      // Trivial case: decomposition is the trivial one, all zeros. We skip the call to Zoltan_Interface
      // (this is mostly done to avoid extra output messages, as even if we didn't skip there is a shortcut
      // in Zoltan[12]Interface).
      // TODO: We can probably skip more work in this case (like building all extra data structures)
      GetOStream(Warnings0) << "Only one partition: Skip call to the repartitioner." << std::endl;
      decomposition = Xpetra::VectorFactory<GO, LO, GO, NO>::Build(A->getRowMap(), true);

    } else {
      decomposition = Get<RCP<GOVector> >(currentLevel, "Partition");

      if (decomposition.is_null()) {
        GetOStream(Warnings0) << "No repartitioning necessary: partitions were left unchanged by the repartitioner" << std::endl;
        Set<RCP<const Import> >(currentLevel, "Importer", Teuchos::null);
        return;
      }
    }

    // ======================================================================================================
    // Remap if necessary
    // ======================================================================================================
    // From a user perspective, we want user to not care about remapping, thinking of it as only a performance feature.
    // There are two problems, however.
    // (1) Next level aggregation depends on the order of GIDs in the vector, if one uses "natural" or "random" orderings.
    //     This also means that remapping affects next level aggregation, despite the fact that the _set_ of GIDs for
    //     each partition is the same.
    // (2) Even with the fixed order of GIDs, the remapping may influence the aggregation for the next-next level.
    //     Let us consider the following example. Lets assume that when we don't do remapping, processor 0 would have
    //     GIDs {0,1,2}, and processor 1 GIDs {3,4,5}, and if we do remapping processor 0 would contain {3,4,5} and
    //     processor 1 {0,1,2}. Now, when we run repartitioning algorithm on the next level (say Zoltan1 RCB), it may
    //     be dependent on whether whether it is [{0,1,2}, {3,4,5}] or [{3,4,5}, {0,1,2}]. Specifically, the tie-breaking
    //     algorithm can resolve these differently. For instance, running
    //         mpirun -np 5 ./MueLu_ScalingTestParamList.exe --xml=easy_sa.xml --nx=12 --ny=12 --nz=12
    //     with
    //         <ParameterList name="MueLu">
    //           <Parameter name="coarse: max size"                type="int"      value="1"/>
    //           <Parameter name="repartition: enable"             type="bool"     value="true"/>
    //           <Parameter name="repartition: min rows per proc"  type="int"      value="2"/>
    //           <ParameterList name="level 1">
    //             <Parameter name="repartition: remap parts"      type="bool"     value="false/true"/>
    //           </ParameterList>
    //         </ParameterList>
    //     produces different repartitioning for level 2.
    //     This different repartitioning may then escalate into different aggregation for the next level.
    //
    // We fix (1) by fixing the order of GIDs in a vector by sorting the resulting vector.
    // Fixing (2) is more complicated.
    // FIXME: Fixing (2) in Zoltan may not be enough, as we may use some arbitration in MueLu,
    // for instance with CoupledAggregation. What we really need to do is to use the same order of processors containing
    // the same order of GIDs. To achieve that, the newly created subcommunicator must be conforming with the order. For
    // instance, if we have [{0,1,2}, {3,4,5}], we create a subcommunicator where processor 0 gets rank 0, and processor 1
    // gets rank 1. If, on the other hand, we have [{3,4,5}, {0,1,2}], we assign rank 1 to processor 0, and rank 0 to processor 1.
    // This rank permutation requires help from Epetra/Tpetra, both of which have no such API in place.
    // One should also be concerned that if we had such API in place, rank 0 in subcommunicator may no longer be rank 0 in
    // MPI_COMM_WORLD, which may lead to issues for logging.
    if (remapPartitions) {
      SubFactoryMonitor m1(*this, "DeterminePartitionPlacement", currentLevel);

      DeterminePartitionPlacement(*A, *decomposition, numPartitions);
    }

    // ======================================================================================================
    // Construct importer
    // ======================================================================================================
    // At this point, the following is true:
    //  * Each processors owns 0 or 1 partitions
    //  * If a processor owns a partition, that partition number is equal to the processor rank
    //  * The decomposition vector contains the partitions ids that the corresponding GID belongs to

    ArrayRCP<const GO> decompEntries;
    if (decomposition->getLocalLength() > 0)
      decompEntries = decomposition->getData(0);

#ifdef HAVE_MUELU_DEBUG
    // Test range of partition ids
    int incorrectRank = -1;
    for (int i = 0; i < decompEntries.size(); i++)
      if (decompEntries[i] >= numProcs || decompEntries[i] < 0) {
        incorrectRank = myRank;
        break;
      }

    int incorrectGlobalRank = -1;
    MueLu_maxAll(comm, incorrectRank, incorrectGlobalRank);
    TEUCHOS_TEST_FOR_EXCEPTION(incorrectGlobalRank >- 1, Exceptions::RuntimeError, "pid " + Teuchos::toString(incorrectGlobalRank) + " encountered a partition number is that out-of-range");
#endif

    Array<GO> myGIDs;
    myGIDs.reserve(decomposition->getLocalLength());

    // Step 0: Construct mapping
    //    part number -> GIDs I own which belong to this part
    // NOTE: my own part GIDs are not part of the map
    typedef std::map<GO, Array<GO> > map_type;
    map_type sendMap;
    for (LO i = 0; i < decompEntries.size(); i++) {
      GO id  = decompEntries[i];
      GO GID = rowMap->getGlobalElement(i);

      if (id == myRank)
        myGIDs     .push_back(GID);
      else
        sendMap[id].push_back(GID);
    }
    decompEntries = Teuchos::null;

    if (IsPrint(Statistics2)) {
      GO numLocalKept = myGIDs.size(), numGlobalKept, numGlobalRows = A->getGlobalNumRows();
      MueLu_sumAll(comm,numLocalKept, numGlobalKept);
      GetOStream(Statistics2) << "Unmoved rows: " << numGlobalKept << " / " << numGlobalRows << " (" << 100*Teuchos::as<double>(numGlobalKept)/numGlobalRows << "%)" << std::endl;
    }

    int numSend = sendMap.size(), numRecv;

    // Arrayify map keys
    Array<GO> myParts(numSend), myPart(1);
    int cnt = 0;
    myPart[0] = myRank;
    for (typename map_type::const_iterator it = sendMap.begin(); it != sendMap.end(); it++)
      myParts[cnt++] = it->first;

    // Step 1: Find out how many processors send me data
    // partsIndexBase starts from zero, as the processors ids start from zero
    GO partsIndexBase = 0;
    RCP<Map>    partsIHave  = MapFactory   ::Build(lib, Teuchos::OrdinalTraits<Xpetra::global_size_t>::invalid(), myParts(), partsIndexBase, comm);
    RCP<Map>    partsIOwn   = MapFactory   ::Build(lib,                                                 numProcs,  myPart(), partsIndexBase, comm);
    RCP<Export> partsExport = ExportFactory::Build(partsIHave, partsIOwn);

    RCP<GOVector> partsISend    = Xpetra::VectorFactory<GO, LO, GO, NO>::Build(partsIHave);
    RCP<GOVector> numPartsIRecv = Xpetra::VectorFactory<GO, LO, GO, NO>::Build(partsIOwn);
    if (numSend) {
      ArrayRCP<GO> partsISendData = partsISend->getDataNonConst(0);
      for (int i = 0; i < numSend; i++)
        partsISendData[i] = 1;
    }
    (numPartsIRecv->getDataNonConst(0))[0] = 0;

    numPartsIRecv->doExport(*partsISend, *partsExport, Xpetra::ADD);
    numRecv = (numPartsIRecv->getData(0))[0];

    // Step 2: Get my GIDs from everybody else
    MPI_Datatype MpiType = MpiTypeTraits<GO>::getType();
    int msgTag = 12345;  // TODO: use Comm::dup for all internal messaging

    // Post sends
    Array<MPI_Request> sendReqs(numSend);
    cnt = 0;
    for (typename map_type::iterator it = sendMap.begin(); it != sendMap.end(); it++)
      MPI_Isend(static_cast<void*>(it->second.getRawPtr()), it->second.size(), MpiType, Teuchos::as<GO>(it->first), msgTag, *rawMpiComm, &sendReqs[cnt++]);

    map_type recvMap;
    size_t totalGIDs = myGIDs.size();
    for (int i = 0; i < numRecv; i++) {
      MPI_Status status;
      MPI_Probe(MPI_ANY_SOURCE, msgTag, *rawMpiComm, &status);

      // Get rank and number of elements from status
      int fromRank = status.MPI_SOURCE, count;
      MPI_Get_count(&status, MpiType, &count);

      recvMap[fromRank].resize(count);
      MPI_Recv(static_cast<void*>(recvMap[fromRank].getRawPtr()), count, MpiType, fromRank, msgTag, *rawMpiComm, &status);

      totalGIDs += count;
    }

    // Do waits on send requests
    if (numSend) {
      Array<MPI_Status> sendStatuses(numSend);
      MPI_Waitall(numSend, sendReqs.getRawPtr(), sendStatuses.getRawPtr());
    }

    // Merge GIDs
    myGIDs.reserve(totalGIDs);
    for (typename map_type::const_iterator it = recvMap.begin(); it != recvMap.end(); it++) {
      int offset = myGIDs.size(), len = it->second.size();
      if (len) {
        myGIDs.resize(offset + len);
        memcpy(myGIDs.getRawPtr() + offset, it->second.getRawPtr(), len*sizeof(GO));
      }
    }
    // NOTE 2: The general sorting algorithm could be sped up by using the knowledge that original myGIDs and all received chunks
    // (i.e. it->second) are sorted. Therefore, a merge sort would work well in this situation.
    std::sort(myGIDs.begin(), myGIDs.end());

    // Step 3: Construct importer
    RCP<Map>          newRowMap      = MapFactory   ::Build(lib, rowMap->getGlobalNumElements(), myGIDs(), indexBase, origComm);
    RCP<const Import> rowMapImporter;
    {
      SubFactoryMonitor m1(*this, "Import construction", currentLevel);
      rowMapImporter = ImportFactory::Build(rowMap, newRowMap);
    }

    Set(currentLevel, "Importer", rowMapImporter);

    // ======================================================================================================
    // Print some data
    // ======================================================================================================
    if (pL.get<bool>("repartition: print partition distribution") && IsPrint(Statistics2)) {
      // Print the grid of processors
      GetOStream(Statistics2) << "Partition distribution over cores (ownership is indicated by '+')" << std::endl;

      char amActive = (myGIDs.size() ? 1 : 0);
      std::vector<char> areActive(numProcs, 0);
      MPI_Gather(&amActive, 1, MPI_CHAR, &areActive[0], 1, MPI_CHAR, 0, *rawMpiComm);

      int rowWidth = std::min(Teuchos::as<int>(ceil(sqrt(numProcs))), 100);
      for (int proc = 0; proc < numProcs; proc += rowWidth) {
        for (int j = 0; j < rowWidth; j++)
          if (proc + j < numProcs)
            GetOStream(Statistics2) << (areActive[proc + j] ? "+" : ".");
          else
          GetOStream(Statistics2) << " ";

        GetOStream(Statistics2) << "      " << proc << ":" << std::min(proc + rowWidth, numProcs) - 1 << std::endl;
      }
    }

  } // Build