/*
 * Is this alias in this list?
 * alias and listOffset should be non-NULL.
 */
static U_INLINE UBool
isAliasInList(const char* alias, uint32_t listOffset) {
    if (listOffset) {
        uint32_t currAlias;
        uint32_t listCount = gMainTable.taggedAliasLists[listOffset];
        /* +1 to skip listCount */
        const uint16_t* currList = gMainTable.taggedAliasLists + listOffset + 1;
        for (currAlias = 0; currAlias < listCount; currAlias++) {
            if (currList[currAlias]
                && ucnv_compareNames(alias, GET_STRING(currList[currAlias])) == 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}