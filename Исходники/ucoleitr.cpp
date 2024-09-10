uint64_t UCollationPCE::processCE(uint32_t ce)
{
    uint64_t primary = 0, secondary = 0, tertiary = 0, quaternary = 0;

    // This is clean, but somewhat slow...
    // We could apply the mask to ce and then
    // just get all three orders...
    switch(strength) {
    default:
        tertiary = ucol_tertiaryOrder(ce);
        U_FALLTHROUGH;

    case UCOL_SECONDARY:
        secondary = ucol_secondaryOrder(ce);
        U_FALLTHROUGH;

    case UCOL_PRIMARY:
        primary = ucol_primaryOrder(ce);
    }

    // **** This should probably handle continuations too.  ****
    // **** That means that we need 24 bits for the primary ****
    // **** instead of the 16 that we're currently using.   ****
    // **** So we can lay out the 64 bits as: 24.12.12.16.  ****
    // **** Another complication with continuations is that ****
    // **** the *second* CE is marked as a continuation, so ****
    // **** we always have to peek ahead to know how long   ****
    // **** the primary is...                               ****
    if ((toShift && variableTop > ce && primary != 0)
                || (isShifted && primary == 0)) {

        if (primary == 0) {
            return UCOL_IGNORABLE;
        }

        if (strength >= UCOL_QUATERNARY) {
            quaternary = primary;
        }

        primary = secondary = tertiary = 0;
        isShifted = TRUE;
    } else {
        if (strength >= UCOL_QUATERNARY) {
            quaternary = 0xFFFF;
        }

        isShifted = FALSE;
    }

    return primary << 48 | secondary << 32 | tertiary << 16 | quaternary;
}