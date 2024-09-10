/******************************************************************************
*   GetIDsOfNames -- Takes an array of strings and returns an array of DISPID's
*   which correspond to the methods or properties indicated.  In real life,
*   If the name is not recognized, then DISP_E_UNKNOWNNAME is returned.
*   However, this is T-Rexx, we know every thing.  Log the name that is being
*   sought, and return a bogus DispID.
******************************************************************************/
STDMETHODIMP OrxScript::GetIDsOfNames(REFIID riid,
                                          OLECHAR **pNames,
                                          UINT pNamesCount,  LCID plcid,
                                          DISPID *pbDispID)
{
    HRESULT RetCode = S_OK,RC;
    UINT    i;
    char    lIID[100];


    StringFromGUID2(riid,(LPOLESTR)lIID,sizeof(lIID)/2);
    FPRINTF(logfile,"OrxScript::GetIDsOfNames\n");
    FPRINTF2(logfile,"pNamesCount %d   riid %S \n",pNamesCount,lIID);

    //check parameters
    if (riid != IID_NULL)
    {
        RetCode = E_INVALIDARG;
    }

    else
    {
        //loop through all the pNames that were passed in, and pass
        //them to the routine that deals with one name at a time.
        for (i = 0; i < pNamesCount; i++)
        {

            RC = GetDispID(pNames[i],fdexNameCaseInsensitive,&pbDispID[i]);
            if (RC != S_OK)
            {
                RetCode = RC;     //  The only returns the last bad error code.
            }

        }
    }

    //  RetCode = S_OK;
    return RetCode;
}