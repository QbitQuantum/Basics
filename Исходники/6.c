char* convert(char* s, int numRows) {
    int len = strlen(s), unitSize = numRows == 1 ? 1 : numRows-1 << 1, unitCount = CEIL(len, unitSize), i, j;
    char* res = (char*)malloc(sizeof(char)*(len + 1)), *p =  res;
    for(i = 0; i < numRows; i++) {
        for(j = 0; j < unitCount; j++) {
            if(i == 0 || i == numRows - 1) {
                PUT_IF_EXISTS(p, s, len, j*unitSize + i);
            } else {
                PUT_IF_EXISTS(p, s, len, j*unitSize + i);
                PUT_IF_EXISTS(p, s, len, (j + 1)*unitSize - i);
            }
        }
    }
    *p = '\0';
    return res;
}