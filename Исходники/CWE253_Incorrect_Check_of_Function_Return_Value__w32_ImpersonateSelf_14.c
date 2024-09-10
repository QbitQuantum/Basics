/* good2() reverses the bodies in the if statement */
static void good2()
{
    if(globalFive==5)
    {
        /* FIX: check for the correct return value */
        if (!ImpersonateSelf(SecurityImpersonation))
        {
            exit(1);
        }
    }
}