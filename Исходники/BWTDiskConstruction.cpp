// Merge two readsFiles together
void mergeReadFiles(const std::string& readsFile1, const std::string& readsFile2, const std::string& outPrefix)
{
    // If the outfile is the empty string, append the reads in readsFile2 into readsFile1
    // otherwise cat the files together
    std::ostream* pWriter;
    if(outPrefix.empty())
    {
        pWriter = createWriter(readsFile1, std::ios_base::out | std::ios_base::app);
    }
    else
    {
        pWriter = createWriter(makeFilename(outPrefix, ".fa"));

        // Copy reads1 to the outfile
        SeqReader reader(readsFile1);
        SeqRecord record;
        while(reader.get(record))
            record.write(*pWriter);
    }

    // Copy reads2 to writer
    SeqReader reader(readsFile2);
    SeqRecord record;
    while(reader.get(record))
        record.write(*pWriter);
    delete pWriter;
}