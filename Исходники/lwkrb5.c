DWORD
LwKrb5FindPac(
    krb5_context ctx,
    const krb5_ticket *pTgsTicket,
    const krb5_keyblock *serviceKey,
    OUT PVOID* ppchLogonInfo,
    OUT size_t* psLogonInfo
    )
{
    DWORD dwError = LW_ERROR_SUCCESS;
    //Do not free
    struct berval bv = {0};
    struct berval contents = {0};
    //Do not free
    krb5_authdata **ppCur = NULL;
    //Do not free associated buffer
    BerElement *ber = NULL;
    ber_tag_t tag = 0;
    ber_len_t len = 0;
    // Do not free
    char *cookie = NULL;
    int adType;
    ber_tag_t seqTag, context0Tag, context1Tag;
    char* pchLogonInfo = NULL;
    size_t sLogonInfo = 0;
    
    ber = ber_alloc_t(0);
    
    if (pTgsTicket && pTgsTicket->enc_part2)
    {
        ppCur = pTgsTicket->enc_part2->authorization_data;
    }

    while (ppCur && (*ppCur != NULL))
    {
        if (ppCur[0]->ad_type == AD_IF_RELEVANT_TYPE)
        {
            // This auth data contains a DER encoded sequence of more
            // auth data. One of them could be a pac.
            bv.bv_len = ppCur[0]->length;
            bv.bv_val = (char *)ppCur[0]->contents;
            ber_init2(ber, &bv, 0);

            tag = ber_first_element(ber, &len, &cookie);
            while (tag != LBER_ERROR)
            {
                // Free does nothing if pointer is NULL
                ber_memfree(contents.bv_val);
                contents.bv_val = NULL;

                tag = ber_scanf(ber,
                        "t{t[i]t[",
                        &seqTag,
                        &context0Tag,
                        &adType,
                        &context1Tag);
                if (tag == LBER_ERROR)
                {
                    // This auth data is invalid. Skip it and try
                    // the next one
                    break;
                }
                tag = ber_scanf(ber,
                        "o]}",
                        &contents);
                if (tag == LBER_ERROR)
                {
                    // This auth data is invalid. Skip it and try
                    // the next one
                    break;
                }

                if (adType == AD_WIN2K_PAC)
                {
                    dwError = LwKrb5VerifyPac(
                        ctx,
                        pTgsTicket,
                        &contents,
                        serviceKey,
                        &pchLogonInfo,
                        &sLogonInfo);
                    if (dwError == LW_ERROR_INVALID_MESSAGE)
                    {
                        dwError = LW_ERROR_SUCCESS;
                        continue;
                    }
                    BAIL_ON_LW_ERROR(dwError);
                    // Found a good PAC !
                    goto end_search;
                }

                //returns LBER_ERROR when there are no more elements left.
                tag = ber_next_element(ber, &len, cookie);
            }
        }

        ppCur++;
    }
end_search:

    *ppchLogonInfo = pchLogonInfo;
    *psLogonInfo = sLogonInfo;

cleanup:
    if (contents.bv_val != NULL)
    {
        ber_memfree(contents.bv_val);
    }
    if (ber != NULL)
    {
        ber_free(ber, 0);
    }

    return dwError;

error:
    LW_SAFE_FREE_MEMORY(pchLogonInfo);
    *ppchLogonInfo = NULL;
    goto cleanup;
}