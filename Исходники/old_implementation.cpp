FILE* tmf_freopen_t(const tmf_char16* filename, const tmf_char16* mode, FILE* current) {
    return _wfreopen(filename, mode, current);
}