ET_ReturnCode CT_LexPreprocessor::PrepareLexemes(__int64 llStart, __int64 llEnd, BOOL bStress)
{
    USES_CONVERSION;
    
    if (llStart < 0 || llEnd < 0 || m_pDb == NULL || sp_dict == NULL)
    {
        ERROR_LOG(L"Illegal argument.");
        return H_ERROR_INVALID_ARG;
    }

    if (llStart == 0 && llEnd == 0)
    {
        // Call the i_ClassifyStems function instead of preparing lexemes
        iClassifyStems();
        return H_NO_ERROR;
    }

    // TEST
    bStress = TRUE;

    CEString sStem;
    int iMaxStems = 0;
    const int MAX_NUM_STEMS = 9;
    long lItems = 0, lId = 0, lWordforms = 0;
    __int64 llLexemeId;
    ET_ReturnCode hr;
    wsmatch result;
    CEString *arr_sParadigm, **parr_sStems, sEnding;
    parr_sStems = new CEString*;
    *parr_sStems = new CEString[1];
    bool bMatch;

    m_pDb->BeginTransaction();
    
    for (llLexemeId = llStart; 
         llLexemeId <= llEnd; 
         ++llLexemeId) // for every lexeme within the range
    {
        int *arr_iSubtableId, *arr_iHash;
        parr_sStems = new CEString*;
        *parr_sStems = new CEString[1];
        int iWf = 0;
        CComPtr<ILexeme> sp_lex;

        // Find the lexeme in the db; generate its paradigm
        // (i_th element of arr_str_Paradigm has form arr_l_Hash[i])
        try
        {
            hr = sp_dict->GetLexeme((LONG)llLexemeId, &sp_lex);
            if (hr != H_NO_ERROR)
            {
                ERROR_LOG(L"GetLexeme() failed.");
                return hr;
            }
            CComBSTR bstrLemma;
            sp_lex->get_InitialForm(&bstrLemma);
            ET_PartOfSpeech eoPOS = POS_UNDEFINED;
            hr = sp_lex->get_PartOfSpeech(&eoPOS);
            // --------- Test ----------
            //if (eoPOS != POS_NOUN && eoPOS != POS_ADJ && eoPOS != POS_VERB && eoPOS != POS_PRONOUN_ADJ)
            //if (eoPOS == POS_NUM_ADJ)
            //{
            //    continue;
            //}
            // --------- /Test ----------
            BOOL bHasIrregularForms = 0;
            sp_lex->get_HasIrregularForms(&bHasIrregularForms);
            if (eoPOS == POS_VERB && bHasIrregularForms != 0)
            {
                iMaxStems = 5;
            }
            else if ((eoPOS == POS_NOUN && bHasIrregularForms == 0) ||
                     (eoPOS == POS_ADJ && bHasIrregularForms == 0) ||
                     eoPOS == POS_PRONOUN_ADJ ||
                     eoPOS == POS_NUM || eoPOS == POS_NUM_ADJ)
            {
                iMaxStems = 2;
            }
            else
            {
                iMaxStems = 3;
            }
            hr = sp_lex->GenerateWordForms();
            if (hr == H_ERROR_UNEXPECTED) // Just skip it
            {
                continue;
            }
            if (hr != H_NO_ERROR)
            {
                ERROR_LOG (L"GenerateWordForms() failed.");
                continue;
                //return h_r;
            }
            hr = sp_lex->get_Count(&lWordforms);
            if (lWordforms <= 0)
            {
                ERROR_LOG (L"l_Wordforms = " + CEString::sToString<long>(lWordforms) + L".");
                //return E_FAIL;
                continue;
            }

            arr_sParadigm = new CEString[lWordforms];
            arr_iHash = new int[lWordforms];
            for (long lItem = 1; lItem <= lWordforms; ++lItem)
            {
                CComVariant sp_disp = NULL;
                hr = sp_lex->get_Item(lItem, &sp_disp);
                if (hr != H_NO_ERROR)
                {
                    ERROR_LOG(L"get_Item failed.");
                    continue;
                    //return h_r;
                }
                CComQIPtr<IWordForm> sp_wf = sp_disp.pdispVal;
                CComBSTR bstrWordForm;
                CEString sWordForm;
                long lHash = -1;
                sp_wf->get_Wordform(&bstrWordForm);
                if (bstrWordForm.Length() <= 0)
                {
                    ERROR_LOG(L"Empty wordform!");
                }
                sp_wf->get_Hash(&lHash);
                arr_iHash[lItem - 1] = (int)lHash; // TODO: it should be of the same type throughout the whole project
                sWordForm = OLE2W(bstrWordForm);
                if (bStress)
                {
                    long lStressPos = -1;
                    long lStressCount = 0;
                    BOOL bPrimary = FALSE;
                    sp_wf->get_StressCount(&lStressCount);
                    for (long lStress = 0; lStress < lStressCount; ++lStress)
                    {
                        // Use only the first primary stress
                        sp_wf->GetStressPos(lStress, &lStressPos, &bPrimary);
                        if (bPrimary == TRUE)
                        {
                            break;
                        }
                        else
                        {
                            lStressPos = -1;
                        }
                    }
                    CEString sWfStressed = sInsertStress(lStressPos, OLE2W(bstrWordForm));
                    arr_sParadigm[lItem - 1] = sWfStressed;
                }
                else
                {
                    arr_sParadigm[lItem - 1] = OLE2W(bstrWordForm);
                }

                sp_disp.Clear();
            }
            
            // Create several gr_stems
            int iStems = 0;
            while (iStems <= 0 && iMaxStems <= MAX_NUM_STEMS)
            {
                delete[] *parr_sStems;
                delete parr_sStems;
                parr_sStems = new CEString*;
                *parr_sStems = new CEString[1];
                iStems = iLCP(arr_sParadigm, parr_sStems, (int)lWordforms, iMaxStems);
                if (iStems == 1 && (*parr_sStems)[0].uiLength() <= 0)
                {
                    iStems = 0;
                }
                iMaxStems += 2;
            }
            
            // Split every wordform into stem and ending,
            // then for every gr_stem create a table of endings usable with it
            CEndingsTable *arr_m_Endings;
            arr_m_Endings = new CEndingsTable[iStems];
            arr_iSubtableId = new int[iStems];
            for (iWf = 0; iWf < lWordforms; ++iWf)
            {
                for (int iS = 0; iS < iStems; ++iS)
                {
                    bMatch = arr_sParadigm[iWf].bRegexMatch((*parr_sStems)[iS] + L"(.*)");
                    if (bMatch == true)
                    {
                        sEnding = arr_sParadigm[iWf].sGetRegexMatch(0);
                        // TODO: Several stress positions
                        int iStressPos = iDeleteStress(sEnding);
                        if ((*parr_sStems)[iS].sSubstr((*parr_sStems)[iS].uiLength() - 1, 1) == L"<")
                        {
                            iStressPos = 0;
                        }
                        // Write the ending and its grammatical meaning 
                        // to the temporary "endings table" no. i_s
                        arr_m_Endings[iS].iAddEnding(arr_iHash[iWf],
                            sEnding, iStressPos);
                        break;
                    }
                }
            }
            // Write the "endings tables" to the db if necessary;
            // get their subtable_id's
            for (int iS = 0; iS < iStems; ++iS)
            {
                arr_iSubtableId[iS] = arr_m_Endings[iS].iDbWrite(vecDb);
            }
            // Add the stems with links to the corresponding subtables to the db
            vInsertStemsAndLinks(parr_sStems, OLE2W(bstrLemma), arr_iSubtableId, iStems, llLexemeId);

            // Delete the arrays
            for (int i_ = 0; i_ < iStems; ++i_)
            {
                arr_m_Endings[i_].~CEndingsTable();
            }
            delete[] arr_sParadigm;
            delete[] arr_iHash;
            delete[] arr_iSubtableId;
            delete[] (*parr_sStems);
            delete parr_sStems;

            // Commit transactions approximately every 200 entries
            if (llLexemeId % 200 == 0)
            {
                m_pDb->CommitTransaction();
                m_pDb->BeginTransaction();
            }
        }
        catch (...)
        {
            ERROR_LOG (L"Exception thrown.");
            //return E_FAIL;
            continue;
        }
    } // for (llLexemeId = llStart; llLexemeId <= llEnd; ++llLexemeId)...
    m_pDb->CommitTransaction();
    m_pDb->BeginTransaction();
    for (int iTable = iDbSize; iTable < vecDb.size(); ++iTable)
    {
        vecDb[iTable].iDbWrite(m_pDb, false, iTable);
    }
    m_pDb->CommitTransaction();
    iDbSize = vecDb.size();

    sp_dict->Clear();

    CoUninitialize();

    return H_NO_ERROR;

} // PrepareLexemes(__int64 ll_start, __int64 ll_end)