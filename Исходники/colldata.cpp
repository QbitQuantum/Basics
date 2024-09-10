CEList::CEList(UCollator *coll, const UnicodeString &string, UErrorCode &status)
    : ces(NULL), listMax(CELIST_BUFFER_SIZE), listSize(0)
{
    UCollationElements *elems = ucol_openElements(coll, string.getBuffer(), string.length(), &status);
    UCollationStrength strength = ucol_getStrength(coll);
    UBool toShift = ucol_getAttribute(coll, UCOL_ALTERNATE_HANDLING, &status) ==  UCOL_SHIFTED;
    uint32_t variableTop = ucol_getVariableTop(coll, &status);
    uint32_t strengthMask = 0;
    int32_t order;

    if (U_FAILURE(status)) {
        return;
    }

    // **** only set flag if string has Han(gul) ****
    // ucol_forceHanImplicit(elems, &status); -- removed for ticket #10476

    switch (strength)
    {
    default:
        strengthMask |= UCOL_TERTIARYORDERMASK;
        U_FALLTHROUGH;
    case UCOL_SECONDARY:
        strengthMask |= UCOL_SECONDARYORDERMASK;
        U_FALLTHROUGH;
    case UCOL_PRIMARY:
        strengthMask |= UCOL_PRIMARYORDERMASK;
    }

    ces = ceBuffer;

    while ((order = ucol_next(elems, &status)) != UCOL_NULLORDER) {
        UBool cont = isContinuation(order);

        order &= strengthMask;

        if (toShift && variableTop > (uint32_t)order && (order & UCOL_PRIMARYORDERMASK) != 0) {
            if (strength >= UCOL_QUATERNARY) {
                order &= UCOL_PRIMARYORDERMASK;
            } else {
                order = UCOL_IGNORABLE;
            }
        }

        if (order == UCOL_IGNORABLE) {
            continue;
        }

        if (cont) {
            order |= UCOL_CONTINUATION_MARKER;
        }

        add(order, status);
    }

    ucol_closeElements(elems);
}