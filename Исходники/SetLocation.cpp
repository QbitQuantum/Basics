// Prints the fields of a civic address location report.
// Empty fields are not printed.
void PrintCivicAddress(ICivicAddressReport *pCivicAddressReport)
{
    CComBSTR bstrAddress1;
    CComBSTR bstrAddress2;
    CComBSTR bstrPostalCode;
    CComBSTR bstrCity;
    CComBSTR bstrStateProvince;
    CComBSTR bstrCountryRegion;
    
    assert(pCivicAddressReport != NULL);

    wprintf(L"\n\n");

        HRESULT hr = pCivicAddressReport->GetAddressLine1(&bstrAddress1);
        if (SUCCEEDED(hr) && (bstrAddress1.Length() != 0))
        { 
			wprintf(L"\tAddress Line 1:\t%s\n", bstrAddress1.m_str);
        }
        hr = pCivicAddressReport->GetAddressLine2(&bstrAddress2);            
        if (SUCCEEDED(hr) && (bstrAddress2.Length() != 0))
        {   
			wprintf(L"\tAddress Line 2:\t%s\n", bstrAddress2.m_str);
        }        
        hr = pCivicAddressReport->GetPostalCode(&bstrPostalCode);
        if (SUCCEEDED(hr) && (bstrPostalCode.Length() != 0))
        {                
			wprintf(L"\tPostal Code:\t%s\n", bstrPostalCode.m_str);
        }
        hr = pCivicAddressReport->GetCity(&bstrCity);
        if (SUCCEEDED(hr) && (bstrCity.Length() != 0))
        {
			wprintf(L"\tCity:\t\t%s\n", bstrCity.m_str);
        }
        hr = pCivicAddressReport->GetStateProvince(&bstrStateProvince);
        if (SUCCEEDED(hr) && (bstrStateProvince.Length() != 0))
        {
			wprintf(L"\tState/Province:\t%s\n", bstrStateProvince.m_str);
        }
        hr = pCivicAddressReport->GetCountryRegion(&bstrCountryRegion);
        if (SUCCEEDED(hr)) 
        {
            // Country/Region is an ISO-3166 two-letter or three-letter code.
			wprintf(L"\tCountry/Region:\t%s\n\n", bstrCountryRegion.m_str);
        }        
}