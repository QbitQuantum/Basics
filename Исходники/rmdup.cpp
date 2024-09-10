std::string parseDupHits(const StringVector& hitsFilenames, const std::string& out_prefix)
{
    // Load the suffix array index and the reverse suffix array index
    // Note these are not the full suffix arrays
    SuffixArray* pFwdSAI = new SuffixArray(opt::prefix + SAI_EXT);
    SuffixArray* pRevSAI = new SuffixArray(opt::prefix + RSAI_EXT);

    // Load the read table to look up the lengths of the reads and their ids.
    // When rmduping a set of reads, the ReadInfoTable can actually be larger than the
    // BWT if the names of the reads are very long. Previously, when two reads
    // are duplicated, the read with the lexographically lower read name was chosen
    // to be kept. To save memory here, we break ties using the index in the ReadInfoTable
    // instead. This allows us to avoid loading the read names.
    ReadInfoTable* pRIT = new ReadInfoTable(opt::readsFile, pFwdSAI->getNumStrings(), RIO_NUMERICID);

    std::string outFile = out_prefix + ".fa";
    std::string dupFile = out_prefix + ".dups.fa";
    std::ostream* pWriter = createWriter(outFile);
    std::ostream* pDupWriter = createWriter(dupFile);

    size_t substringRemoved = 0;
    size_t identicalRemoved = 0;
    size_t kept = 0;
    size_t buffer_size = SequenceProcessFramework::BUFFER_SIZE;

    // The reads must be output in their original ordering.
    // The hits are in the blocks of buffer_size items. We read
    // buffer_size items from the first hits file, then buffer_size
    // from the second and so on until all the hits have been processed.
    size_t num_files = hitsFilenames.size();
    std::vector<std::istream*> reader_vec(num_files, 0);

    for(size_t i = 0; i < num_files; ++i)
    {
        std::cout << "Opening " << hitsFilenames[i] << "\n";
        reader_vec[i] = createReader(hitsFilenames[i]);
    }

    bool done = false;
    size_t currReaderIdx = 0;
    size_t numRead = 0;
    size_t numReadersDone = 0;
    std::string line;

    while(!done)
    {
        // Parse a line from the current file
        bool valid = getline(*reader_vec[currReaderIdx], line);
        ++numRead;
        // Deal with switching the active reader and the end of files
        if(!valid || numRead == buffer_size)
        {
            // Switch the reader
            currReaderIdx = (currReaderIdx + 1) % num_files;
            numRead = 0;

            // Break once all the readers are invalid
            if(!valid)
            {
                ++numReadersDone;
                if(numReadersDone == num_files)
                {
                    done = true;
                    break;
                }
            }
        }

        // Parse the data
        if(valid)
        {
            std::string id;
            std::string sequence;
            std::string hitsStr;
            size_t readIdx;
            size_t numCopies;
            bool isSubstring;

            std::stringstream parser(line);
            parser >> id;
            parser >> sequence;
            getline(parser, hitsStr);

            OverlapVector ov;
            OverlapCommon::parseHitsString(hitsStr, pRIT, pRIT, pFwdSAI, pRevSAI, true, readIdx, numCopies, ov, isSubstring);
            
            bool isContained = false;
            if(isSubstring)
            {
                ++substringRemoved;
                isContained = true;
            }
            else
            {
                for(OverlapVector::iterator iter = ov.begin(); iter != ov.end(); ++iter)
                {
                    if(iter->isContainment() && iter->getContainedIdx() == 0)
                    {
                        // This read is contained by some other read
                        ++identicalRemoved;
                        isContained = true;
                        break;
                    }
                }
            }

            SeqItem item = {id, sequence};
            std::stringstream meta;
            meta << id << " NumDuplicates=" << numCopies;

            if(isContained)
            {
                // The read's index in the sequence data base
                // is needed when removing it from the FM-index.
                // In the output fasta, we set the reads ID to be the index
                // and record its old id in the fasta header.
                std::stringstream newID;
                newID << item.id << ",seqrank=" << readIdx;
                item.id = newID.str();

                // Write some metadata with the fasta record
                item.write(*pDupWriter, meta.str());
            }
            else
            {
                ++kept;
                // Write the read
                item.write(*pWriter, meta.str());
            }
        }
    }

    for(size_t i = 0; i < num_files; ++i)
    {
        delete reader_vec[i];
        unlink(hitsFilenames[i].c_str());
    }

    
    printf("[%s] Removed %zu substring reads\n", PROGRAM_IDENT, substringRemoved);
    printf("[%s] Removed %zu identical reads\n", PROGRAM_IDENT, identicalRemoved);
    printf("[%s] Kept %zu reads\n", PROGRAM_IDENT, kept);

    // Delete allocated data
    delete pFwdSAI;
    delete pRevSAI;
    delete pRIT;
    delete pWriter;
    delete pDupWriter;

    return dupFile;
}