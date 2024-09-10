void cluster()
{
    BWT* pBWT = new BWT(opt::prefix + BWT_EXT);
    BWT* pRBWT = new BWT(opt::prefix + RBWT_EXT);
    OverlapAlgorithm* pOverlapper = new OverlapAlgorithm(pBWT, pRBWT,opt::errorRate, opt::seedLength, opt::seedStride, true);

    pOverlapper->setExactModeOverlap(opt::errorRate < 0.001f);
    pOverlapper->setExactModeIrreducible(opt::errorRate < 0.001f);

    BitVector markedReads(pBWT->getNumStrings());

    std::string preclustersFile = opt::outFile + ".preclusters";
    std::ostream* pPreWriter = createWriter(preclustersFile);
    ClusterPostProcess postProcessor(pPreWriter, opt::minSize, &markedReads);
    
    // Set the cluster parameters
    ClusterParameters parameters;
    parameters.pOverlapper = pOverlapper;
    parameters.minOverlap = opt::minOverlap;
    parameters.maxClusterSize = opt::maxSize;
    parameters.maxIterations = opt::maxIterations;
    parameters.pMarkedReads = &markedReads;

    // Read the limit kmer sequences, if provided
    std::set<std::string>* pLimitKmers = NULL;

    if(!opt::limitFile.empty())
    {
        // Read in the limit sequences
        pLimitKmers = new std::set<std::string>;
        readLimitKmers(pLimitKmers);
        parameters.pLimitKmers = pLimitKmers;
        parameters.limitK = opt::limitKmer;
    }
    else
    {
        parameters.pLimitKmers = NULL;
        parameters.limitK = 0;
    }

    // Make pre-clusters from the reads
    if(opt::numThreads <= 1)
    {
        printf("[%s] starting serial-mode read clustering\n", PROGRAM_IDENT);
        ClusterProcess processor(parameters);
        
        // If the extend file is empty, build new clusters
        if(opt::extendFile.empty())
        {
            PROCESS_CLUSTER_SERIAL(opt::readsFile, &processor, &postProcessor);
        }
        else
        {
            // Process a set of preexisting clusters
            ClusterReader clusterReader(opt::extendFile);
            PROCESS_EXTEND_SERIAL(clusterReader, &processor, &postProcessor);
        }
    }
    else
    {
        printf("[%s] starting parallel-mode read clustering computation with %d threads\n", PROGRAM_IDENT, opt::numThreads);
        
        std::vector<ClusterProcess*> processorVector;
        for(int i = 0; i < opt::numThreads; ++i)
        {
            ClusterProcess* pProcessor = new ClusterProcess(parameters);
            processorVector.push_back(pProcessor);
        }
        
        if(opt::extendFile.empty())
        {
            PROCESS_CLUSTER_PARALLEL(opt::readsFile, processorVector, &postProcessor);
        }
        else
        {
            ClusterReader clusterReader(opt::extendFile);
            PROCESS_EXTEND_PARALLEL(clusterReader, processorVector, &postProcessor);
        }
        
        for(size_t i = 0; i < processorVector.size(); ++i)
        {
            delete processorVector[i];
            processorVector[i] = NULL;
        }
    }
    delete pPreWriter;
    delete pBWT;
    delete pRBWT;
    delete pOverlapper;

    // Deallocate limit kmers
    if(pLimitKmers != NULL)
        delete pLimitKmers;

    // Open the preclusters file and convert them to read names
    SuffixArray* pFwdSAI = new SuffixArray(opt::prefix + SAI_EXT);
    ReadInfoTable* pRIT = new ReadInfoTable(opt::readsFile, pFwdSAI->getNumStrings());

    size_t seedIdx = 0;
    std::istream* pPreReader = createReader(preclustersFile);
    std::ostream* pClusterWriter = createWriter(opt::outFile);
    std::string line;
    while(getline(*pPreReader,line))
    {
        std::stringstream parser(line);
        std::string clusterName;
        std::string readSequence;
        size_t clusterSize;
        int64_t lowIdx;
        int64_t highIdx;
        parser >> clusterName >> clusterSize >> readSequence >> lowIdx >> highIdx;

        if(lowIdx > highIdx)
        {
            // This is an extra read that is not present in the FM-index
            // Output a record with a fake read ID
            *pClusterWriter << clusterName << "\t" << clusterSize << "\tseed-" << seedIdx++ << "\t" << readSequence << "\n";
        }
        else
        {
            for(int64_t i = lowIdx; i <= highIdx; ++i)
            {
                const ReadInfo& targetInfo = pRIT->getReadInfo(pFwdSAI->get(i).getID());
                std::string readName = targetInfo.id;
                *pClusterWriter << clusterName << "\t" << clusterSize << "\t" << readName << "\t" << readSequence << "\n";
            }
        }
    }
    unlink(preclustersFile.c_str());

    delete pFwdSAI;
    delete pRIT;
    delete pPreReader;
    delete pClusterWriter;
}