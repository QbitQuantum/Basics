void DisplayDMOTypeInfo(const GUID *pCLSID, 
                        ULONG& ulNumInputsSupplied,  CListBox& ListInputTypes,
                        ULONG& ulNumOutputsSupplied, CListBox& ListOutputTypes)
{
    const int NUM_PAIRS=20;
    HRESULT hr;
    DMO_PARTIAL_MEDIATYPE aInputTypes[NUM_PAIRS]={0}, 
                          aOutputTypes[NUM_PAIRS]={0};
    ULONG ulNumInputTypes=NUM_PAIRS, ulNumOutputTypes=NUM_PAIRS, i;
    TCHAR szCLSID[128];

    // Read type/subtype information
    hr = DMOGetTypes(
        *pCLSID,
        ulNumInputTypes,  &ulNumInputsSupplied,  aInputTypes,
        ulNumOutputTypes, &ulNumOutputsSupplied, aOutputTypes);

    if (FAILED(hr))
        return;

    // Show input type/subtype pairs
    for (i=0; i<ulNumInputsSupplied; i++)
    {
        GetTypeSubtypeString(szCLSID, aInputTypes[i]);
        ListInputTypes.AddString(szCLSID);
    }

    // Show output type/subtype pairs
    for (i=0; i<ulNumOutputsSupplied; i++)
    {
        GetTypeSubtypeString(szCLSID, aOutputTypes[i]);
        ListOutputTypes.AddString(szCLSID);
    }
}