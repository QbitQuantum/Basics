//
// Main
//
int FMindexWalkMain(int argc, char** argv)
{
    parseFMWalkOptions(argc, argv);

    // Set the error correction parameters
    FMIndexWalkParameters ecParams;
	BWT *pBWT, *pRBWT;
	SampledSuffixArray* pSSA;

    // Load indices
	#pragma omp parallel
	{
		#pragma omp single nowait
		{	//Initialization of large BWT takes some time, pass the disk to next job
			std::cout << std::endl << "Loading BWT: " << opt::prefix + BWT_EXT << "\n";
			pBWT = new BWT(opt::prefix + BWT_EXT, opt::sampleRate);
		}
		#pragma omp single nowait
		{
			std::cout << "Loading RBWT: " << opt::prefix + RBWT_EXT << "\n";
			pRBWT = new BWT(opt::prefix + RBWT_EXT, opt::sampleRate);
		}
		#pragma omp single nowait
		{
			std::cout << "Loading Sampled Suffix Array: " << opt::prefix + SAI_EXT << "\n";
			pSSA = new SampledSuffixArray(opt::prefix + SAI_EXT, SSA_FT_SAI);
		}
	}

    BWTIndexSet indexSet;
    indexSet.pBWT = pBWT;
    indexSet.pRBWT = pRBWT;
    indexSet.pSSA = pSSA;
    ecParams.indices = indexSet;

	// Sample 100000 kmer counts into KmerDistribution from reverse BWT 
	// Don't sample from forward BWT as Illumina reads are bad at the 3' end
	ecParams.kd = BWTAlgorithms::sampleKmerCounts(opt::minOverlap, 100000, pRBWT);
	ecParams.kd.computeKDAttributes();
	// const size_t RepeatKmerFreq = ecParams.kd.getCutoffForProportion(0.95); 
	std::cout << "Median kmer frequency: " <<ecParams.kd.getMedian() << "\t Std: " <<  ecParams.kd.getSdv() 
					<<"\t 95% kmer frequency: " << ecParams.kd.getCutoffForProportion(0.95)
					<< "\t Repeat frequency cutoff: " << ecParams.kd.getRepeatKmerCutoff() << "\n";
	
    // Open outfiles and start a timer
    std::ostream* pWriter = createWriter(opt::outFile);
    std::ostream* pDiscardWriter = (!opt::discardFile.empty() ? createWriter(opt::discardFile) : NULL);
    Timer* pTimer = new Timer(PROGRAM_IDENT);

    ecParams.algorithm = opt::algorithm;
    ecParams.kmerLength = opt::kmerLength;
    ecParams.printOverlaps = opt::verbose > 0;
	ecParams.maxLeaves = opt::maxLeaves;
	ecParams.maxInsertSize = opt::maxInsertSize;
    ecParams.minOverlap = opt::minOverlap;
    ecParams.maxOverlap = opt::maxOverlap;
	
    // Setup post-processor
    FMIndexWalkPostProcess postProcessor(pWriter, pDiscardWriter, ecParams);

    std::cout << "Merge paired end reads into long reads for " << opt::readsFile << " using \n" 
				<< "min overlap=" <<  ecParams.minOverlap << "\t"
				<< "max overlap=" <<  ecParams.maxOverlap << "\t"
				<< "max leaves=" << opt::maxLeaves << "\t"
				<< "max Insert size=" << opt::maxInsertSize << "\t"
				<< "kmer size=" << opt::kmerLength << "\n\n";

    if(opt::numThreads <= 1)
    {
        // Serial mode
        FMIndexWalkProcess processor(ecParams);

		if (ecParams.algorithm == FMW_HYBRID || ecParams.algorithm == FMW_MERGE)
        SequenceProcessFramework::processSequencesSerial<SequenceWorkItemPair,
                                                         FMIndexWalkResult,
                                                         FMIndexWalkProcess,
                                                         FMIndexWalkPostProcess>(opt::readsFile, &processor, &postProcessor);

		else
        SequenceProcessFramework::processSequencesSerial<SequenceWorkItem,
                                                         FMIndexWalkResult,
                                                         FMIndexWalkProcess,
                                                         FMIndexWalkPostProcess>(opt::readsFile, &processor, &postProcessor);
    }
    else
    {
        // Parallel mode
        std::vector<FMIndexWalkProcess*> processorVector;
        for(int i = 0; i < opt::numThreads; ++i)
        {
            FMIndexWalkProcess* pProcessor = new FMIndexWalkProcess(ecParams);
            processorVector.push_back(pProcessor);
        }

		if (ecParams.algorithm == FMW_HYBRID || ecParams.algorithm == FMW_MERGE)
        SequenceProcessFramework::processSequencesParallel<SequenceWorkItemPair,
                                                           FMIndexWalkResult,
                                                           FMIndexWalkProcess,
                                                           FMIndexWalkPostProcess>(opt::readsFile, processorVector, &postProcessor);

		else
        SequenceProcessFramework::processSequencesParallel<SequenceWorkItem,
                                                           FMIndexWalkResult,
                                                           FMIndexWalkProcess,
                                                           FMIndexWalkPostProcess>(opt::readsFile, processorVector, &postProcessor);

        for(int i = 0; i < opt::numThreads; ++i)
        {
            delete processorVector[i];
        }
    }

    delete pBWT;
    if(pRBWT != NULL)
        delete pRBWT;

    if(pSSA != NULL)
        delete pSSA;

    delete pTimer;

    delete pWriter;
    if(pDiscardWriter != NULL)
        delete pDiscardWriter;
	
    return 0;
}