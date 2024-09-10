//
// Main
//
int overlapLongMain(int argc, char** argv)
{
    parseOverlapLongOptions(argc, argv);

    // Open output file
    std::ostream* pASQGWriter = createWriter(opt::outFile);

    // Build and write the ASQG header
    ASQG::HeaderRecord headerRecord;
    headerRecord.setOverlapTag(opt::minOverlap);
    headerRecord.setErrorRateTag(opt::errorRate);
    headerRecord.setInputFileTag(opt::readsFile);
    headerRecord.setTransitiveTag(true);
    headerRecord.write(*pASQGWriter);

    // Determine which index files to use. If a target file was provided,
    // use the index of the target reads
    std::string indexPrefix;
    if(!opt::targetFile.empty())
        indexPrefix = stripFilename(opt::targetFile);
    else
        indexPrefix = stripFilename(opt::readsFile);

    BWT* pBWT = new BWT(indexPrefix + BWT_EXT, opt::sampleRate);
    SampledSuffixArray* pSSA = new SampledSuffixArray(indexPrefix + SAI_EXT, SSA_FT_SAI);
    
    Timer* pTimer = new Timer(PROGRAM_IDENT);
    pBWT->printInfo();

    // Read the sequence file and write vertex records for each
    // Also store the read names in a vector of strings
    ReadTable reads;
    
    SeqReader* pReader = new SeqReader(opt::readsFile, SRF_NO_VALIDATION);
    SeqRecord record;
    while(pReader->get(record))
    {
        reads.addRead(record.toSeqItem());
        ASQG::VertexRecord vr(record.id, record.seq.toString());
        vr.write(*pASQGWriter);

        if(reads.getCount() % 100000 == 0)
            printf("Read %zu sequences\n", reads.getCount());
    }

    delete pReader;
    pReader = NULL;

    BWTIndexSet index;
    index.pBWT = pBWT;
    index.pSSA = pSSA;
    index.pReadTable = &reads;

    // Make a prefix for the temporary hits files
    size_t n_reads = reads.getCount();

    omp_set_num_threads(opt::numThreads);

#pragma omp parallel for
    for(size_t read_idx = 0; read_idx < n_reads; ++read_idx)
    {
        const SeqItem& curr_read = reads.getRead(read_idx);

        printf("read %s %zubp\n", curr_read.id.c_str(), curr_read.seq.length());
        SequenceOverlapPairVector sopv = 
            KmerOverlaps::retrieveMatches(curr_read.seq.toString(),
                                          opt::seedLength,
                                          opt::minOverlap,
                                          1 - opt::errorRate,
                                          100,
                                          index);

        printf("Found %zu matches\n", sopv.size());
        for(size_t i = 0; i < sopv.size(); ++i)
        {
            std::string match_id = reads.getRead(sopv[i].match_idx).id;

            // We only want to output each edge once so skip this overlap
            // if the matched read has a lexicographically lower ID
            if(curr_read.id > match_id)
                continue;

            std::string ao = ascii_overlap(sopv[i].sequence[0], sopv[i].sequence[1], sopv[i].overlap, 50);
            printf("\t%s\t[%d %d] ID=%s OL=%d PI:%.2lf C=%s\n", ao.c_str(),
                                                                sopv[i].overlap.match[0].start,
                                                                sopv[i].overlap.match[0].end,
                                                                match_id.c_str(),
                                                                sopv[i].overlap.getOverlapLength(),
                                                                sopv[i].overlap.getPercentIdentity(),
                                                                sopv[i].overlap.cigar.c_str());

            // Convert to ASQG
            SeqCoord sc1(sopv[i].overlap.match[0].start, sopv[i].overlap.match[0].end, sopv[i].overlap.length[0]);
            SeqCoord sc2(sopv[i].overlap.match[1].start, sopv[i].overlap.match[1].end, sopv[i].overlap.length[1]);
            
            // KmerOverlaps returns the coordinates of the overlap after flipping the reads
            // to ensure the strand matches. The ASQG file wants the coordinate of the original
            // sequencing strand. Flip here if necessary
            if(sopv[i].is_reversed)
                sc2.flip();

            // Convert the SequenceOverlap the ASQG's overlap format
            Overlap ovr(curr_read.id, sc1, match_id,  sc2, sopv[i].is_reversed, -1);

            ASQG::EdgeRecord er(ovr);
            er.setCigarTag(sopv[i].overlap.cigar);
            er.setPercentIdentityTag(sopv[i].overlap.getPercentIdentity());

#pragma omp critical
            {
                er.write(*pASQGWriter);
            }
        }
    }

    // Cleanup
    delete pReader;
    delete pBWT; 
    delete pSSA;
    
    delete pASQGWriter;
    delete pTimer;
    if(opt::numThreads > 1)
        pthread_exit(NULL);

    return 0;
}