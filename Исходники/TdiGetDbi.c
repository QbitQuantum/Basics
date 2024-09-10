int Tdi1GetDbi(int opcode, int narg, struct descriptor *list[],
               struct descriptor_xd *out_ptr)
{
    int status = 1;
    struct descriptor_d string = { 0, DTYPE_T, CLASS_D, 0 };
    struct descriptor_xd tmp = EMPTY_XD;
    struct item *key_ptr = 0;
    int index;
    DBI_ITM lst[] = { {sizeof(index), DbiINDEX, 0, 0}
    , EOL, EOL };
    lst[0].pointer = (unsigned char *)&index;
        /**********************
        String of item to find.
        **********************/
    status = TdiData(list[0], &tmp MDS_END_ARG);
    if (status & 1)
        status = TdiUpcase(&tmp, &string MDS_END_ARG);
    if (status & 1) {
        key_ptr =
            (struct item *)bsearch(&string, table, numtab, siztab,
                                   (int (*)(const void *, const void *))
                                   compare);
        if (key_ptr == 0)
            status = TdiBAD_INDEX;
    }
    StrFree1Dx(&string);
    MdsFree1Dx(&tmp, NULL);
        /**********************************
        Somebody might want others in pool.
        **********************************/
    if (status & 1 && narg > 1)
        status = TdiGetLong(list[1], &index);
    else
        index = 0;
        /***********************
        Get the item asked for.
        Fixed length or varying.
        ***********************/
    if (status & 1) {
        lst[1].code = key_ptr->item_code;
        if ((lst[1].buffer_length = key_ptr->item_length) != 0) {
            status =
                MdsGet1DxS((unsigned short *)&lst[1].buffer_length,
                           &key_ptr->item_dtype, out_ptr);
            if (status & 1) {
                lst[1].pointer = (unsigned char *)out_ptr->pointer->pointer;
                status = TreeGetDbi(lst);
            }
        } else {
            lst[1].buffer_length = 0;
            lst[1].pointer = NULL;
            status = TreeGetDbi(lst);
            if (status & 1) {
                struct descriptor ans = { 0, DTYPE_T, CLASS_S, 0 };
                if (lst[1].pointer) {
                    ans.length = strlen((char *)lst[1].pointer);
                    ans.pointer = (char *)lst[1].pointer;
                }
                status = MdsCopyDxXd(&ans, out_ptr);
                if (ans.pointer)
                    TreeFree(ans.pointer);
            }
        }
    }
    return status;
}