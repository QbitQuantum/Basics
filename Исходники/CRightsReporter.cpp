///////////////////////////////////////////////////////////////////////////////
//
// Method: GetRightsForKID
// Description: Prints "is allowed" rights information to a report file for 
//  a given Key ID.
// Parameters: KID - Key ID string.
//
///////////////////////////////////////////////////////////////////////////////
HRESULT CRightsReporter::GetRightsForKID(BSTR KID)
{
    HRESULT hr = S_OK;

    // Get the rights information.
    if (SUCCEEDED(hr))
    {
        hr = m_pLicenseQuery->QueryActionAllowed(KID, 
                                                NULL, 
                                                m_cIsAllowedRights, 
                                                m_IsAllowedRights, 
                                                m_IsAllowedResults);
    }

    // Print the results to the output file.
    if (SUCCEEDED(hr))
    {
        // Loop through the results, reporting on each.
        for (int i = 0; i < m_cIsAllowedRights; i++)
        {
            fwprintf(m_pFile, L"%-35.35s - ", m_IsAllowedRights[i]);

            // Check the query result.
            if (m_IsAllowedResults[i] == 0)
            {
                fwprintf(m_pFile, L"Allowed\n\n");
            }
            else
            {
                // The action is not allowed.
                fwprintf(m_pFile, L"Not Allowed\n");

                // If the action is not allowed, check the result against the
                //  possible failure flags and report the reasons.
                
                // The DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED flag is set for any
                //  not allowed result. Only list it if no other reason is 
                //  provided.
                if ((m_IsAllowedResults[i] & 0xFFFFFFFF)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED)
                {
                    fwprintf(m_pFile, L"   Not allowed for an unspecified reason.\n");
                }

                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NO_LICENSE)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NO_LICENSE)
                {
                    fwprintf(m_pFile, L"   No license for this KID.\n");
                }

                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NO_RIGHT)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NO_RIGHT)
                {
                    fwprintf(m_pFile, L"   License does not grant this right.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_EXHAUSTED)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_EXHAUSTED)
                {
                    fwprintf(m_pFile, L"   Licensed counts for this right exhausted.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_EXPIRED)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_EXPIRED)
                {
                    fwprintf(m_pFile, L"   License expired.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NOT_STARTED)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NOT_STARTED)
                {
                    fwprintf(m_pFile, L"   License is not yet in effect.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_APPSEC_TOO_LOW)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_APPSEC_TOO_LOW)
                {
                    fwprintf(m_pFile, L"   Application security level is too low.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_REQ_INDIV)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_REQ_INDIV)
                {
                    fwprintf(m_pFile, L"   License requires security update.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_COPY_OPL_TOO_LOW)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_COPY_OPL_TOO_LOW)
                {
                    fwprintf(m_pFile, L"   Cannot copy to the configured device.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_COPY_OPL_EXCLUDED)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_COPY_OPL_EXCLUDED)
                {
                    fwprintf(m_pFile, L"   Configured device excluded from license.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NO_CLOCK_SUPPORT)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NO_CLOCK_SUPPORT)
                {
                    fwprintf(m_pFile, L"   License requires a secure clock.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NO_METERING_SUPPORT)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_NO_METERING_SUPPORT)
                {
                    fwprintf(m_pFile, L"   License requires metering.\n");
                }


                if ((m_IsAllowedResults[i] & DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_CHAIN_DEPTH_TOO_HIGH)
                    == DRM_ACTION_ALLOWED_QUERY_NOT_ENABLED_CHAIN_DEPTH_TOO_HIGH)
                {
                    fwprintf(m_pFile, L"   Incomplete license chain.\n");
                }

                // Print a newline character for spacing between entries.
                fwprintf(m_pFile, L"\n");
            }
        } // End for loop.
    }

    return hr;
}