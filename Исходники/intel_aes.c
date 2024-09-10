int check_for_aes_instructions()
{
    unsigned int cpuid_results[4];
    int yes=1, no=0;

    // Removed checks for Intel CPU -HN

    __cpuid(cpuid_results,1);

    if (cpuid_results[2] & AES_INSTRCTIONS_CPUID_BIT)
        return yes;

    return no;
}