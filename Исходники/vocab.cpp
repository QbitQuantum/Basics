NetInt32 Vocab::encode(const ConstString& str) {
    char a = '\0';
    char b = '\0';
    char c = '\0';
    char d = '\0';
    if (str.length()>=1) {
        a = str[0];
        if (str.length()>=2) {
            b = str[1];
            if (str.length()>=3) {
                c = str[2];
                if (str.length()>=4) {
                    d = str[3];
                }
            }
        }
    }
    return VOCAB(a,b,c,d);
}