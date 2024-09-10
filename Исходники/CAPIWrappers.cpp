/****************************************************************************++

Routine Description:

    Creates a handle to the CSP

Arguments:

    pwzContainerName - name of the container to be created. if NULL, GUID is generated
                      for the name of the container

    fCreateNewKeys   - forces new keys to be created

    phCryptProv      - pointer to the location, where handle should be returned

Notes:

    -

Return Value:

    - S_OK

      - or -

    - CAPI error returned by CryptAcquireContextW

--*****************************************************************************/
HRESULT
CreateCryptProv(
    IN      PCWSTR          pwzContainerName,
    IN      BOOL            fCreateNewKeys,
    OUT     HCRYPTPROV*     phCryptProv)
{

    HRESULT         hr = S_OK;
    HCRYPTKEY       hKey = NULL;
    RPC_STATUS      status =  RPC_S_OK;
    BOOL            fCreatedContainer = FALSE;
    WCHAR*          pwzNewContainerName = NULL;

    *phCryptProv = NULL;

    if (NULL == pwzContainerName)
    {
         UUID    uuid;
         BOOL   fServiceAccount = FALSE;

        //
        // generate container name from the UUID
        //
        status = UuidCreate(&uuid);
        hr = HRESULT_FROM_RPCSTATUS(status);
        if (FAILED(hr))
        {
            goto Cleanup;
        }

        status = UuidToStringW(&uuid, (unsigned short**)&pwzNewContainerName);
        hr = HRESULT_FROM_RPCSTATUS(status);
        if (FAILED(hr))
        {
            goto Cleanup;
        }

        pwzContainerName = pwzNewContainerName;

        hr = IsServiceAccount(&fServiceAccount);
        if (FAILED(hr))
        {
            goto Cleanup;
        }

        //
        // open the clean key container
        //
        // note: CRYPT_NEW_KEYSET is not creating new keys, it just
        // creates new key container. duh.
        //
        if (!CryptAcquireContextW(phCryptProv,
                                pwzNewContainerName,
                                NULL,               // default provider name
                                DEFAULT_PROV_TYPE,
                                fServiceAccount ?
                                    (CRYPT_SILENT | CRYPT_NEWKEYSET | CRYPT_MACHINE_KEYSET) :
                                    (CRYPT_SILENT | CRYPT_NEWKEYSET)))
        {
            hr = HRESULT_FROM_WIN32(GetLastError());

            //
            // we are seeing that CryptAcquireContextW returns NTE_FAIL under low
            // memory condition, so we just mask the error
            //
            if (NTE_FAIL == hr)
            {
                hr = E_OUTOFMEMORY;
            }

            goto Cleanup;
        }

        fCreatedContainer = TRUE;

    }
    else
    {
        BOOL    fServiceAccount = FALSE;

        hr = IsServiceAccount(&fServiceAccount);
        if (FAILED(hr))
        {
            goto Cleanup;
        }

        //
        // open the provider first, create the keys too
        //
        if (!CryptAcquireContextW(phCryptProv,
                            pwzContainerName,
                            NULL,               // default provider name
                            DEFAULT_PROV_TYPE,
                            fServiceAccount ?
                                (CRYPT_SILENT | CRYPT_MACHINE_KEYSET) :
                                (CRYPT_SILENT)))
        {
            hr = HRESULT_FROM_WIN32(GetLastError());

            //
            // we are seeing that CryptAcquireContextW returns NTE_FAIL under low
            // memory condition, so we just mask the error
            //
            if (NTE_FAIL == hr)
            {
                hr = E_OUTOFMEMORY;
            }

            goto Cleanup;
        }
    }

    if (fCreateNewKeys)
    {
        //
        // make sure keys exist
        //
        if (!CryptGetUserKey(*phCryptProv,
                            DEFAULT_KEY_SPEC,
                            &hKey))
        {
            hr = HRESULT_FROM_WIN32(GetLastError());

            // if key does not exist, create it
            if (HRESULT_FROM_WIN32((unsigned long)NTE_NO_KEY) == hr)
            {
                hr = S_OK;

                if (!CryptGenKey(*phCryptProv,
                                  DEFAULT_KEY_SPEC,
                                  CRYPT_EXPORTABLE,
                                  &hKey))
                {
                    hr = HRESULT_FROM_WIN32(GetLastError());

                    //
                    // we are seeing that CryptGenKey returns ERROR_CANTOPEN under low
                    // memory condition, so we just mask the error
                    //
                    if (HRESULT_FROM_WIN32(ERROR_CANTOPEN) == hr)
                    {
                        hr = E_OUTOFMEMORY;
                    }

                    goto Cleanup;
                }

            }
            else
            {
                // failed to get user key by some misterious reason, so bail out
                goto Cleanup;
            }
        }
    }

Cleanup:

    DestroyKey(hKey);

    if (FAILED(hr))
    {

        //
        // release the context
        //
        ReleaseCryptProv(*phCryptProv);
        *phCryptProv = NULL;

        //
        // delete the keys, if we created them
        //
        if (fCreatedContainer)
        {
            DeleteKeys(pwzContainerName);
        }
    }

    if (NULL != pwzNewContainerName)
    {
        // this always returns RPC_S_OK
        status = RpcStringFreeW((unsigned short**)&pwzNewContainerName);
        USES(status);
    }

    return hr;
}