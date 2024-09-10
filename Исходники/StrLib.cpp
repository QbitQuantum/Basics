void SaveStr(char *param) {
    if ( (posBytesLeft <= 3) || !posSave)
        return;

    posBytesLeft -= 3;  // subtract 3 for the 2 quotation marks and the space

    if (*posSave == 0)
        *posSave++ = ' ';

    int len = lstrlen(param);

    *posSave++ = '"';
    len += Escape(posSave, param, '"');
    posSave += len;

    *posSave++ = '"';
    *posSave   = 0;
    posBytesLeft -= len;
}