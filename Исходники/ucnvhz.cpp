static void  U_CALLCONV
_HZClose(UConverter *cnv){
    if(cnv->extraInfo != NULL) {
        ucnv_close (((UConverterDataHZ *) (cnv->extraInfo))->gbConverter);
        if(!cnv->isExtraLocal) {
            uprv_free(cnv->extraInfo);
        }
        cnv->extraInfo = NULL;
    }
}