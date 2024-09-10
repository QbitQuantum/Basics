std::string toLower(std::string s) {
    int i;
    for (i = 0; i < s.length(); ++i) {
        if (isUpper(s[i])) {
            s[i] += ASCII_DELTA;
        }
    }
    return s;
}