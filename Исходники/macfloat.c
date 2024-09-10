Obj FuncMACFLOAT_STRING( Obj self, Obj s )
{

    while (!IsStringConv(s))
    {
        s = ErrorReturnObj("MACFLOAT_STRING: object to be converted must be a string not a %s",
                           (Int)(InfoBags[TNUM_OBJ(s)].name),0,"You can return a string to continue" );
    }
    char * endptr;
    UChar *sp = CHARS_STRING(s);
    Obj res= NEW_MACFLOAT((Double) STRTOD((char *)sp,&endptr));
    if ((UChar *)endptr != sp + GET_LEN_STRING(s))
        return Fail;
    return res;
}