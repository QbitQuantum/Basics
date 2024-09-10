// returns BAM file pointers to beginning of alignment data
bool BamMultiReader::Rewind(void) { 
    bool result = true;
    for (vector<pair<BamReader*, BamAlignment*> >::iterator it = readers.begin(); it != readers.end(); ++it) {
        BamReader* reader = it->first;
        result &= reader->Rewind();
    }
    return result;
}