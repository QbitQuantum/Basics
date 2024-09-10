OggFile::OggFile(UsageEnvironment& env, char const* fileName,
                 onCreationFunc* onCreation, void* onCreationClientData)
    : Medium(env),
      fFileName(strDup(fileName)),
      fOnCreation(onCreation), fOnCreationClientData(onCreationClientData) {
    fTrackTable = new OggTrackTable;
    fDemuxesTable = HashTable::create(ONE_WORD_HASH_KEYS);

    FramedSource* inputSource = ByteStreamFileSource::createNew(envir(), fileName);
    if (inputSource == NULL) {
        // The specified input file does not exist!
        fParserForInitialization = NULL;
        handleEndOfBosPageParsing(); // we have no file, and thus no tracks, but we still need to signal this
    } else {
        // Initialize ourselves by parsing the file's headers:
        fParserForInitialization
            = new OggFileParser(*this, inputSource, handleEndOfBosPageParsing, this);
    }
}