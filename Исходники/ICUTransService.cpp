// ---------------------------------------------------------------------------
//  ICUTransService: The virtual transcoding service API
// ---------------------------------------------------------------------------
int ICUTransService::compareIString(const   XMLCh* const    comp1
                                    , const XMLCh* const    comp2)
{
    size_t  i = 0;
    size_t  j = 0;

    for(;;)
    {
        UChar32 ch1;
        UChar32 ch2;

        U16_NEXT_UNSAFE(comp1, i, ch1);
        U16_NEXT_UNSAFE(comp2, j, ch2);

        const UChar32   folded1 =
            u_foldCase(ch1, U_FOLD_CASE_DEFAULT);

        const UChar32   folded2 =
            u_foldCase(ch2, U_FOLD_CASE_DEFAULT);

        if (folded1 !=
            folded2)
        {
            return folded1 - folded2;
        }
        else if (ch1 == 0)
        {
            // If ch1 is 0, the ch2 must also be
            // 0.  Otherwise, the previous if
            // would have failed.
            break;
        }
    }

    return 0;
}