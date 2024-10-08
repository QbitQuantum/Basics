void string_reader(CL_FORM *base)
{
    LOAD_NIL(ARG(2));
    LOAD_FIXNUM(ARG(3), 0, ARG(3));
    COPY(SYMVAL(Slisp, 448), ARG(4));	/* *TOKEN* */
    Fset_fill_pointer(ARG(3));
M1_1:
    ;
    COPY(ARG(0), ARG(3));
    COPY(ARG(3), ARG(2));
    LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(3));	/* T */
    LOAD_NIL(ARG(4));
    LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(5));	/* T */
    read_char1(ARG(2));
    COPY(SYMVAL(Slisp, 454), ARG(3));	/* *READTABLE* */
    readtable_syntax(ARG(3));
    if(CL_CHARP(ARG(2)))
    {
    }
    else
    {
        COPY(SYMVAL(Slisp, 58), ARG(4));	/* WRONG_TYPE */
        COPY(ARG(2), ARG(5));
        LOAD_SYMBOL(SYMBOL(Slisp, 18), ARG(6));	/* CHARACTER */
        Ferror(ARG(4), 3);
    }
    COPY(ARG(2), ARG(4));
    rt_char_code(ARG(4));
    LOAD_BOOL(CL_SMVECP(ARG(3)), ARG(5));
    if(CL_TRUEP(ARG(5)))
    {
        goto THEN1;
    }
    else
    {
        COPY(ARG(3), ARG(6));
        LOAD_SYMBOL(SYMBOL(Slisp, 150), ARG(7));	/* COMPLEX-VECTOR */
        rt_struct_typep(ARG(6));
    }
    if(CL_TRUEP(ARG(6)))
    {
THEN1:
        ;
    }
    else
    {
        COPY(SYMVAL(Slisp, 58), ARG(5));	/* WRONG_TYPE */
        COPY(ARG(3), ARG(6));
        LOAD_SYMBOL(SYMBOL(Slisp, 47), ARG(7));	/* VECTOR */
        Ferror(ARG(5), 3);
    }
    Frow_major_aref(ARG(3));
    if(CL_SYMBOLP(ARG(3)) && GET_SYMBOL(ARG(3)) == SYMBOL(Slisp, 463))	/* SINGLE-ESCAPE */
    {
        COPY(ARG(0), ARG(3));
        COPY(ARG(3), ARG(2));
        LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(3));	/* T */
        LOAD_NIL(ARG(4));
        LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(5));	/* T */
        read_char1(ARG(2));
        COPY(ARG(2), ARG(3));
        COPY(SYMVAL(Slisp, 448), ARG(4));	/* *TOKEN* */
        LOAD_NIL(ARG(5));
        vector_push_extend1(ARG(3));
    }
    else
    {
        if(EQL(ARG(1), ARG(2)))
        {
            COPY(SYMVAL(Slisp, 448), ARG(0));	/* *TOKEN* */
            LOAD_FIXNUM(ARG(1), 0, ARG(1));
            LOAD_NIL(ARG(2));
            subseq1(ARG(0));
            goto RETURN1;
        }
        else
        {
            COPY(ARG(2), ARG(3));
            COPY(SYMVAL(Slisp, 448), ARG(4));	/* *TOKEN* */
            LOAD_NIL(ARG(5));
            vector_push_extend1(ARG(3));
        }
    }
    goto M1_1;
RETURN1:
    ;
}