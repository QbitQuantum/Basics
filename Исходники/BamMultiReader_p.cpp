// returns BAM file pointers to beginning of alignment data
bool BamMultiReaderPrivate::RewindReaders()
{

    m_errorString.clear();
    bool errorsEncountered = false;

    // iterate over readers
    std::vector<MergeItem>::iterator readerIter = m_readers.begin();
    std::vector<MergeItem>::iterator readerEnd = m_readers.end();
    for (; readerIter != readerEnd; ++readerIter) {
        MergeItem& item = (*readerIter);
        BamReader* reader = item.Reader;
        if (reader == 0) continue;

        // attempt rewind on BamReader
        if (!reader->Rewind()) {
            m_errorString.append(1, '\t');
            m_errorString.append(reader->GetErrorString());
            m_errorString.append(1, '\n');
            errorsEncountered = true;
        }
    }

    return !errorsEncountered;
}