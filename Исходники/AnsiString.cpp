void AnsiString::operator=(char *value) {
    size_t len;

    if (Data)
        Data[0] = 0;
    _LENGTH = 0;
    if (value) {
        len     = strlen(value);
        _LENGTH = len;
        if (len) {
            if (len + 1 >= _DATA_SIZE) {
                /*if (Data)
                    delete[] Data;*/
                _DATA_SIZE = ((len + 1) / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
                //Data=new char[_DATA_SIZE];
                Data = (char *)realloc(Data, _DATA_SIZE);
            }
            // varianta 2:
            MEMCPY(Data, value, len + 1);// copiez si terminatorul
            // varianta 1:
            // strcpy(Data,value);
        }
    }
}