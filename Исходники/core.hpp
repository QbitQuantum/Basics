bool string::readfile(const string &filename) {
    assign("");

#if !defined(_WIN32)
    FILE *fp = fopen(filename, "rb");
#else
    FILE *fp = _wfopen(utf16_t(filename), L"rb");
#endif
    if(!fp) return false;

    fseek(fp, 0, SEEK_END);
    unsigned size = ftell(fp);
    rewind(fp);
    char *fdata = new char[size + 1];
    unsigned unused = fread(fdata, 1, size, fp);
    fclose(fp);
    fdata[size] = 0;
    assign(fdata);
    delete[] fdata;

    return true;
}