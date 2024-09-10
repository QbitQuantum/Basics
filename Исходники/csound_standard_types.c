void array_copy_value(void* csound, void* dest, void* src) {
    ARRAYDAT* aDest = (ARRAYDAT*)dest;
    ARRAYDAT* aSrc = (ARRAYDAT*)src;
    CSOUND* cs = (CSOUND*)csound;
    size_t j;
    int memMyfltSize;
    size_t arrayNumMembers;

    arrayNumMembers = array_get_num_members(aSrc);
    memMyfltSize = aSrc->arrayMemberSize / sizeof(MYFLT);

    if(aDest->data == NULL ||
       aSrc->arrayMemberSize != aDest->arrayMemberSize ||
       aSrc->dimensions != aDest->dimensions ||
       aSrc->arrayType != aDest->arrayType ||
       arrayNumMembers != array_get_num_members(aDest)) {

        aDest->arrayMemberSize = aSrc->arrayMemberSize;
        aDest->dimensions = aSrc->dimensions;
        if(aDest->sizes != NULL) {
            cs->Free(cs, aDest->sizes);
        }
        aDest->sizes = cs->Malloc(cs, sizeof(int) * aSrc->dimensions);
        memcpy(aDest->sizes, aSrc->sizes, sizeof(int) * aSrc->dimensions);
        aDest->arrayType = aSrc->arrayType;

        if(aDest->data != NULL) {
            cs->Free(cs, aDest->data);
        }
        aDest->data = cs->Calloc(cs, aSrc->arrayMemberSize * arrayNumMembers);
    }

    for (j = 0; j < arrayNumMembers; j++) {
        int index = j * memMyfltSize;
        aDest->arrayType->copyValue(csound,
                                    aDest->data + index, aSrc->data + index);
    }

}