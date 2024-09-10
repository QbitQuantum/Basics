HRESULT CAnalyzer::LoadDb(BSTR bstrPath)
{
    USES_CONVERSION;

int iDebugFlag =  _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
iDebugFlag |= _CRTDBG_LEAK_CHECK_DF;

    if (m_pDb)
    {
        delete m_pDb;
    }

    m_sDbPath = OLE2W(bstrPath);
    m_pDb = new CSqlite(m_sDbPath);
    if (m_pDb == NULL)
    {
        ERROR_LOG (L"Failed to instantiate CSqlite.");
        return E_FAIL;
    }

    // Fill umap_freq_stems
    umap_freq_stems.clear();
    CEString str_query = L"Select * from stems_for_analysis"; // TODO: frequencies
    m_pDb->PrepareForSelect(str_query);
    stStemLinks s_links;
    CEString str_stem = L"", str_stem_without_yo = L"";

    while (m_pDb->bGetRow())
    {
        m_pDb->GetData(0, s_links.iStemId);
        m_pDb->GetData(1, s_links.llLexemeId);
        m_pDb->GetData(2, str_stem);
        m_pDb->GetData(3, s_links.iStressPos);
        m_pDb->GetData(4, s_links.iEndingsLink);
        m_pDb->GetData(5, s_links.sLemma);
        if (str_stem.bIsEmpty())
        {
            continue;
        }
        umap_freq_stems.insert(pair<CEString, stStemLinks>(str_stem, s_links));
        str_stem_without_yo = str_stem;
        str_stem_without_yo.Replace(0, str_stem_without_yo.uiLength(), L'ё', L'е');
        if (str_stem_without_yo != str_stem)
        {
            umap_freq_stems.insert (pair<CEString, stStemLinks> (str_stem_without_yo, s_links));
        }
    }

    m_pDb->Finalize();

    // Fill arr_freq_endings
    int i_subtable_id, i_cur_subtable_id = -1, i_hash, iStressPos;
    CEString str_ending = L"", str_ending_without_yo = L"";
    if (arr_freq_endings != NULL)
    {
        delete[] arr_freq_endings;
    }
    int i_last_subtable = m_pDb->iLastID(L"endings_for_analysis");
    if (i_last_subtable < -1)
    {
        return E_FAIL;
    }
    arr_freq_endings = new CEndingsTable[i_last_subtable + 1];
    str_query = L"Select * from endings_for_analysis order by subtable_id asc";
    m_pDb->PrepareForSelect(str_query);
    CEndingsTable co_et;
    while (m_pDb->bGetRow())
    {
        m_pDb->GetData(1, i_subtable_id);
        m_pDb->GetData(2, str_ending);
        m_pDb->GetData(3, i_hash);
        m_pDb->GetData(4, iStressPos);
        if (i_subtable_id != i_cur_subtable_id)
        {
            // Push the current subtable to the array
            if (i_cur_subtable_id >= 0)
            {
                CEndingsTable coETCopy(co_et);
                arr_freq_endings[i_cur_subtable_id] = coETCopy;
            }
            i_cur_subtable_id = i_subtable_id;
            co_et.Clear();
        }
        co_et.iAddEnding(i_hash, str_ending, iStressPos);
        str_ending_without_yo = str_ending;
        str_ending_without_yo.Replace(0, str_ending_without_yo.uiLength(), L'ё', L'е');
        if (str_ending_without_yo != str_ending)
        {
            co_et.iAddEnding(i_hash, str_ending_without_yo, iStressPos);
        }
    }
    m_pDb->Finalize();

    // Fill umap_endings2subtbl
    umap_endings2subtbl.clear();
    str_query = L"Select * from subtables_for_heuristics";
    m_pDb->PrepareForSelect(str_query);
    int iLexemeCount = 0, iCutRight = 0;
    CEString sStemFinal = L"", sLemmaFinal = L"";
    while (m_pDb->bGetRow())
    {
        m_pDb->GetData (1, i_subtable_id);
        m_pDb->GetData (2, iLexemeCount);
        m_pDb->GetData (3, sStemFinal);
        m_pDb->GetData (4, iCutRight);
        m_pDb->GetData (5, sLemmaFinal);
        arr_freq_endings[i_subtable_id].m_iLexemeCount = iLexemeCount;
        arr_freq_endings[i_subtable_id].m_iCutRight = iCutRight;
        arr_freq_endings[i_subtable_id].m_sStemFinal = sStemFinal;
        arr_freq_endings[i_subtable_id].m_sLemmaFinal = sLemmaFinal;
        for (vector<stInflexion>::iterator iterEnding = arr_freq_endings[i_subtable_id].m_vecEndings.begin();
             iterEnding != arr_freq_endings[i_subtable_id].m_vecEndings.end();
             ++iterEnding)
        {
//            umap_endings2subtbl.insert(unordered_multimap<CEString, int>::value_type(*iter_ending, i_subtable_id));
            umap_endings2subtbl.insert(pair<CEString, int>(iterEnding->sEnding, i_subtable_id));
        }
    }
    m_pDb->Finalize();
    return S_OK;
}