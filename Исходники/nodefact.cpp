HRESULT CNodeFactory::ProcessQualifyAssemblyTag(XML_NODE_INFO **aNodeInfo, USHORT cNumRecs)
{
    HRESULT                                            hr = S_OK;
    USHORT                                             idx = 1;
    LPWSTR                                             pwzAttributeNS = NULL;
    LPWSTR                                             pwzPartialName = NULL;
    LPWSTR                                             pwzFullName = NULL;
    CQualifyAssembly                                  *pqa = NULL;
    IAssemblyName                                     *pNameFull = NULL;
    IAssemblyName                                     *pNamePartial = NULL;
    IAssemblyName                                     *pNameQualified = NULL;
    LPWSTR                              wzCanonicalDisplayName=NULL;

    ASSERT(aNodeInfo && cNumRecs);

    while (idx < cNumRecs) {
        if (aNodeInfo[idx]->dwType == XML_ATTRIBUTE) {
            // Found an attribute. Find out which one, and extract the data.
            // Node: ::ExtractXMLAttribute increments idx.

            hr = ApplyNamespace(aNodeInfo[idx], &pwzAttributeNS, 0);
            if (FAILED(hr)) {
                goto Exit;
            }

            if (!lstrcmpW(pwzAttributeNS, XML_ATTRIBUTE_PARTIALNAME)) {
                SAFEDELETEARRAY(pwzAttributeNS);

                if (pwzPartialName) {
                    // Ignore duplicate attribute
                    idx++;
                }
                else {
                    hr = ::ExtractXMLAttribute(&pwzPartialName, aNodeInfo, &idx, cNumRecs);
                    if (FAILED(hr)) {
                        goto Exit;
                    }
                }
            }
            else if (!lstrcmpW(pwzAttributeNS, XML_ATTRIBUTE_FULLNAME)) {
                SAFEDELETEARRAY(pwzAttributeNS);

                if (pwzFullName) {
                    // Ignore duplicate attribute
                    idx++;
                }
                else {
                    hr = ::ExtractXMLAttribute(&pwzFullName, aNodeInfo, &idx, cNumRecs);
                    if (FAILED(hr)) {
                        goto Exit;
                    }
                }

            }
            else {
                SAFEDELETEARRAY(pwzAttributeNS);
                idx++;
            }
        }
        else {
            idx++;
        }
    }

    if (pwzPartialName && pwzFullName) {
        DWORD                               dwSize;
        DWORD                               adwProperties[] = { ASM_NAME_NAME,
                                                                ASM_NAME_MAJOR_VERSION,
                                                                ASM_NAME_MINOR_VERSION,
                                                                ASM_NAME_BUILD_NUMBER,
                                                                ASM_NAME_REVISION_NUMBER,
                                                                ASM_NAME_CULTURE,
                                                                ASM_NAME_PUBLIC_KEY_TOKEN
                                                              };
        DWORD                               adwCmpFlags[] = { ASM_CMPF_NAME,
                                                              ASM_CMPF_MAJOR_VERSION,
                                                              ASM_CMPF_MINOR_VERSION,
                                                              ASM_CMPF_BUILD_NUMBER,
                                                              ASM_CMPF_REVISION_NUMBER,
                                                              ASM_CMPF_CULTURE,
                                                              ASM_CMPF_PUBLIC_KEY_TOKEN
                                                            };
        DWORD                               dwNumProps = sizeof(adwProperties) / sizeof(adwProperties[0]);

        if (FAILED(CreateAssemblyNameObject(&pNameFull, pwzFullName,
                                            CANOF_PARSE_DISPLAY_NAME, 0))) {
            goto Exit;
        }

        if (FAILED(CreateAssemblyNameObject(&pNamePartial, pwzPartialName,
                                            CANOF_PARSE_DISPLAY_NAME, 0))) {
            goto Exit;
        }

        // Check validity of qualification

        if (CAssemblyName::IsPartial(pNameFull) || !CAssemblyName::IsPartial(pNamePartial)) {
            goto Exit;
        }

        if (FAILED(pNamePartial->Clone(&pNameQualified))) {
            goto Exit;
        }

        for (DWORD i = 0; i < dwNumProps; i++) {
            dwSize = 0;
            if (pNamePartial->GetProperty(adwProperties[i], NULL, &dwSize) != HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)) {
                // Partial on this field. Set pNameQualified's corresponding
                // property to whatever is in pNameFull.

                dwSize = 0;
                pNameFull->GetProperty(adwProperties[i], NULL, &dwSize);
                if (!dwSize) {
                    goto Exit;
                }
                else {
                    BYTE                       *pBuf;

                    pBuf = NEW(BYTE[dwSize]);
                    if (!pBuf) {
                        hr = E_OUTOFMEMORY;
                        goto Exit;
                    }

                    if (FAILED(pNameFull->GetProperty(adwProperties[i], pBuf, &dwSize))) {
                        SAFEDELETEARRAY(pBuf);
                        goto Exit;
                    }

                    if (FAILED(pNameQualified->SetProperty(adwProperties[i], pBuf, dwSize))) {
                        SAFEDELETEARRAY(pBuf);
                        goto Exit;
                    }

                    SAFEDELETEARRAY(pBuf);
                }
            }
            else {
                // Full-specified on this field. Make sure it matches the full ref specified.

                if (pNamePartial->IsEqual(pNameFull, adwCmpFlags[i]) != S_OK) {
                    goto Exit;
                }
            }
        }

        if (CAssemblyName::IsPartial(pNameQualified)) {
            goto Exit;
        }

        // Get canonical display name format

        wzCanonicalDisplayName = NEW(WCHAR[MAX_URL_LENGTH+1]);
        if (!wzCanonicalDisplayName)
        {
            hr = E_OUTOFMEMORY;
            goto Exit;
        }

        dwSize = MAX_URL_LENGTH;
        if (FAILED(pNamePartial->GetDisplayName(wzCanonicalDisplayName, &dwSize, 0))) {
            goto Exit;
        }

        // Add qualified assembly entry to list

        pqa = new CQualifyAssembly;
        if (!pqa) {
            hr = E_OUTOFMEMORY;
            goto Exit;
        }

        pqa->_pwzPartialName = WSTRDupDynamic(wzCanonicalDisplayName);
        if (!pqa->_pwzPartialName) {
            hr = E_OUTOFMEMORY;
            goto Exit;
        }

        pqa->_pNameFull = pNameQualified;
        pNameQualified->AddRef();

        _listQualifyAssembly.AddTail(pqa);
    }

Exit:
    SAFEDELETEARRAY(pwzPartialName);
    SAFEDELETEARRAY(pwzFullName);

    SAFERELEASE(pNameFull);
    SAFERELEASE(pNamePartial);
    SAFERELEASE(pNameQualified);

    SAFEDELETEARRAY(wzCanonicalDisplayName);
    return hr;
}