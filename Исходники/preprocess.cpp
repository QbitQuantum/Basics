//
// Main
//
int preprocessMain(int argc, char** argv)
{
    Timer* pTimer = new Timer("sga preprocess");
    parsePreprocessOptions(argc, argv);

    std::cerr << "Parameters:\n";
    std::cerr << "QualTrim: " << opt::qualityTrim << "\n";

    if(opt::qualityFilter >= 0)
        std::cerr << "QualFilter: at most " << opt::qualityFilter << " low quality bases\n";
    else
        std::cerr << "QualFilter: no filtering\n";

    std::cerr << "HardClip: " << opt::hardClip << "\n";
    std::cerr << "Min length: " << opt::minLength << "\n";
    std::cerr << "Sample freq: " << opt::sampleFreq << "\n";
    std::cerr << "PE Mode: " << opt::peMode << "\n";
    std::cerr << "Quality scaling: " << opt::qualityScale << "\n";
    std::cerr << "MinGC: " << opt::minGC << "\n";
    std::cerr << "MaxGC: " << opt::maxGC << "\n";
    std::cerr << "Outfile: " << (opt::outFile.empty() ? "stdout" : opt::outFile) << "\n";
    std::cerr << "Orphan file: " << (opt::orphanFile.empty() ? "none" : opt::orphanFile) << "\n";
    if(opt::bDiscardAmbiguous)
        std::cerr << "Discarding sequences with ambiguous bases\n";
    if(opt::bDustFilter)
        std::cerr << "Dust threshold: " << opt::dustThreshold << "\n";
    if(!opt::suffix.empty())
        std::cerr << "Suffix: " << opt::suffix << "\n";

    if(opt::adapterF.length() && opt::adapterR.length())
    {
        std::cerr << "Adapter sequence fwd: " << opt::adapterF << "\n";
        std::cerr << "Adapter sequence rev: " << opt::adapterR << "\n";
    }

    // Seed the RNG
    srand(time(NULL));

    std::ostream* pWriter;
    if(opt::outFile.empty())
    {
        pWriter = &std::cout;
    }
    else
    {
        std::ostream* pFile = createWriter(opt::outFile);
        pWriter = pFile;
    }

    // Create a filehandle to write orphaned reads to, if necessary
    std::ostream* pOrphanWriter = NULL;
    if(!opt::orphanFile.empty())
        pOrphanWriter = createWriter(opt::orphanFile);

    if(opt::peMode == 0)
    {
        // Treat files as SE data
        while(optind < argc)
        {
            std::string filename = argv[optind++];
            std::cerr << "Processing " << filename << "\n\n";
            SeqReader reader(filename, SRF_NO_VALIDATION);
            SeqRecord record;

            while(reader.get(record))
            {
                bool passed = processRead(record);
                if(passed && samplePass())
                {
                    if(!opt::suffix.empty())
                        record.id.append(opt::suffix);

                    record.write(*pWriter);
                    ++s_numReadsKept;
                    s_numBasesKept += record.seq.length();
                }
            }
        }
    }
    else
    {
        assert(opt::peMode == 1 || opt::peMode == 2);
        int numFiles = argc - optind;
        if(opt::peMode == 1 && numFiles % 2 == 1)
        {
            std::cerr << "Error: An even number of files must be given for pe-mode 1\n";
            exit(EXIT_FAILURE);
        }

        while(optind < argc)
        {
            SeqReader* pReader1;
            SeqReader* pReader2;

            if(opt::peMode == 1)
            {
                // Read from separate files
                std::string filename1 = argv[optind++];
                std::string filename2 = argv[optind++];

                pReader1 = new SeqReader(filename1, SRF_NO_VALIDATION);
                pReader2 = new SeqReader(filename2, SRF_NO_VALIDATION);

                std::cerr << "Processing pe files " << filename1 << ", " << filename2 << "\n";

            }
            else
            {
                // Read from a single file
                std::string filename = argv[optind++];
                pReader1 = new SeqReader(filename, SRF_NO_VALIDATION);
                pReader2 = pReader1;
                std::cerr << "Processing interleaved pe file " << filename << "\n";
            }

            SeqRecord record1;
            SeqRecord record2;
            while(pReader1->get(record1) && pReader2->get(record2))
            {
                // If the names of the records are the same, append a /1 and /2 to them
                if(record1.id == record2.id)
                {
                    if(!opt::suffix.empty())
                    {
                        record1.id.append(opt::suffix);
                        record2.id.append(opt::suffix);
                    }

                    record1.id.append("/1");
                    record2.id.append("/2");
                }

                // Ensure the read names are sensible
                std::string expectedID2 = getPairID(record1.id);
                std::string expectedID1 = getPairID(record2.id);

                if(expectedID1 != record1.id || expectedID2 != record2.id)
                {
                    std::cerr << "Warning: Pair IDs do not match (expected format /1,/2 or /A,/B)\n";
                    std::cerr << "Read1 ID: " << record1.id << "\n";
                    std::cerr << "Read2 ID: " << record2.id << "\n";
                    s_numInvalidPE += 2;
                }

                bool passed1 = processRead(record1);
                bool passed2 = processRead(record2);

                if(!samplePass())
                    continue;

                if(passed1 && passed2)
                {
                    record1.write(*pWriter);
                    record2.write(*pWriter);
                    s_numReadsKept += 2;
                    s_numBasesKept += record1.seq.length();
                    s_numBasesKept += record2.seq.length();
                }
                else if(passed1 && pOrphanWriter != NULL)
                {
                    record1.write(*pOrphanWriter);
                }
                else if(passed2 && pOrphanWriter != NULL)
                {
                    record2.write(*pOrphanWriter);
                }
            }

            if(pReader2 != pReader1)
            {
                // only delete reader2 if it is a distinct pointer
                delete pReader2;
                pReader2 = NULL;
            }
            delete pReader1;
            pReader1 = NULL;

        }

    }

    if(pWriter != &std::cout)
        delete pWriter;
    if(pOrphanWriter != NULL)
        delete pOrphanWriter;

    std::cerr << "\nPreprocess stats:\n";
    std::cerr << "Reads parsed:\t" << s_numReadsRead << "\n";
    std::cerr << "Reads kept:\t" << s_numReadsKept << " (" << (double)s_numReadsKept / (double)s_numReadsRead << ")\n";
    std::cerr << "Reads failed primer screen:\t" << s_numReadsPrimer << " (" << (double)s_numReadsPrimer / (double)s_numReadsRead << ")\n";
    std::cerr << "Bases parsed:\t" << s_numBasesRead << "\n";
    std::cerr << "Bases kept:\t" << s_numBasesKept << " (" << (double)s_numBasesKept / (double)s_numBasesRead << ")\n";
    std::cerr << "Number of incorrectly paired reads that were discarded: " << s_numInvalidPE << "\n";
    if(opt::bDustFilter)
        std::cerr << "Number of reads failed dust filter: " << s_numFailedDust << "\n";
    delete pTimer;
    return 0;
}