double StrToD(const char* b, char** se) {
    return StrToD(b, b + strlen(b), se);
}