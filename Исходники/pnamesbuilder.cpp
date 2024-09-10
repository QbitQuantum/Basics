void
PNamesBuilderImpl::writeBinaryData(const char *path, UBool withCopyright, UErrorCode &errorCode) {
    if(U_FAILURE(errorCode)) { return; }
    UNewDataMemory *pdata=udata_create(path, PNAME_DATA_TYPE, PNAME_DATA_NAME, &dataInfo,
                                       withCopyright ? U_COPYRIGHT_STRING : 0, &errorCode);
    if(U_FAILURE(errorCode)) {
        fprintf(stderr, "genprops: udata_create(%s, pnames.icu) failed - %s\n",
                path, u_errorName(errorCode));
        return;
    }

    udata_writeBlock(pdata, indexes, PropNameData::IX_COUNT*4);
    udata_writeBlock(pdata, valueMaps.getBuffer(), valueMaps.size()*4);
    udata_writeBlock(pdata, bytesTries.data(), bytesTries.length());
    udata_writeBlock(pdata, nameGroups.data(), nameGroups.length());

    int32_t dataLength=(int32_t)udata_finish(pdata, &errorCode);
    if(dataLength!=indexes[PropNameData::IX_TOTAL_SIZE]) {
        fprintf(stderr,
                "udata_finish(pnames.icu) reports %ld bytes written but should be %ld\n",
                (long)dataLength, (long)indexes[PropNameData::IX_TOTAL_SIZE]);
        errorCode=U_INTERNAL_PROGRAM_ERROR;
    }
}