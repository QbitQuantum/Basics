void CSQLiteConversion::SqliteStatementExecution(std::vector<CString> &statements, sqlite3 *&sqlitedatabase, int rc , wxGauge *&gauge, unsigned &nValue, wxTextCtrl *&PrgDlg,
        unsigned &nErrorCount, CString *sTableNames, unsigned &flag, unsigned &nTableCount, int *IndexTable, CString *sTableNames2)
{
    char *zErrMsg = 0;
    unsigned index = 0;
    auto end_it = statements.end();
    for( auto it = statements.begin(); it != end_it; ++it )
    {
        ++nValue;
        gauge ->SetValue(nValue);
        std::string sB = ConvertToUTF8(*it);
        const char* pszC = _strdup(sB.c_str());
        rc = sqlite3_exec(sqlitedatabase, pszC, NULL, 0, &zErrMsg);
        if( rc != SQLITE_OK )
        {
            ++nErrorCount;
            PrgDlg->SetDefaultStyle(wxTextAttr (wxNullColour, *wxRED));
            wxString ErrorMessage = wxT("");
            ErrorMessage += wxString::FromUTF8(zErrMsg);
            ErrorMessage += " \n";
            PrgDlg->WriteText(ErrorMessage);
            CT2CA pszConvertedAnsiString (*it);
            std::string strStd (pszConvertedAnsiString);
            ErrorMessage = wxString::FromUTF8(_strdup(strStd.c_str() ) ) + "\n";
            PrgDlg->WriteText(ErrorMessage);
            if(flag & 1)
            {
                ErrorMessage = wxT("Table: ");
                sB = ConvertToUTF8(sTableNames[nValue-1]);
                ErrorMessage += wxString::FromUTF8(_strdup(sB.c_str() ) );
                ErrorMessage += wxT(" wasnt created succesfully \n");
                PrgDlg->WriteText(ErrorMessage);
            }
            PrgDlg->SetDefaultStyle(wxTextAttr (wxNullColour));
            sqlite3_free(zErrMsg);
        }
        else
        {
            if(flag & ExecuteTables)
            {
                wxString sMessage = wxT("Table: ");
                sB = ConvertToUTF8(sTableNames[nValue-1]);
                sMessage += wxString::FromUTF8(_strdup(sB.c_str() ) );
                sMessage += wxT(" created succesfully \n");
                PrgDlg->WriteText(sMessage);
            }
            else if(flag & ExecuteInserts)
            {
                if(*it == "END TRANSACTION")
                {
                    sTableNames[index];
                    wxString sMessage = wxT("Table: ");
                    sB = ConvertToUTF8(sTableNames[index]);
                    sMessage += wxString::FromUTF8(_strdup(sB.c_str() ) );
                    sMessage += wxT(" records inserted \n");
                    ++index;
                    PrgDlg->WriteText(sMessage);
                }
            }
            else if(flag & ExecuteIndexes)
            {
                if( index < nTableCount )
                {
                    while( !IndexTable[index] )
                    {
                        wxString sMessage = wxT("indexes of table: ");
                        sB = ConvertToUTF8(sTableNames2[index]);
                        sMessage += wxString::FromUTF8(_strdup(sB.c_str() ) );
                        sMessage += wxT(" created \n");
                        PrgDlg->WriteText(sMessage);
                        ++index;
                    }
                }
                IndexTable[index]--;
                if( index < nTableCount )
                {
                    if( !IndexTable[index] )
                    {
                        wxString sMessage = wxT("indexes of table: ");
                        sB = ConvertToUTF8(sTableNames2[index]);
                        sMessage += wxString::FromUTF8(_strdup(sB.c_str() ) );
                        sMessage += wxT(" created \n");
                        PrgDlg->WriteText(sMessage);
                        ++index;
                    }
                }
                if(index < nTableCount )
                {
                    while( !IndexTable[index] )
                    {

                        wxString sMessage = wxT("indexes of table: ");
                        sB = ConvertToUTF8(sTableNames2[index]);
                        sMessage += wxString::FromUTF8(_strdup(sB.c_str() ) );
                        sMessage += wxT(" created \n");
                        PrgDlg->WriteText(sMessage);
                        ++index;
                    }
                }

            }
        }
    }
}