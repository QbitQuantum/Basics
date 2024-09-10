/* Checks if the Unicode character can be a Unicode identifier part other than starting the
 identifier.*/
U_CAPI UBool U_EXPORT2
u_isIDPart(UChar32 c) {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(
               (CAT_MASK(props)&
                (U_GC_ND_MASK|U_GC_NL_MASK|
                 U_GC_L_MASK|
                 U_GC_PC_MASK|U_GC_MC_MASK|U_GC_MN_MASK)
               )!=0 ||
               u_isIDIgnorable(c));
}