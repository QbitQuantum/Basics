GFile::~GFile() {
    FlushAll();
    if (Handle != NULL) delete Handle;
}