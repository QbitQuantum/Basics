std::wstring ExpandSection(
	const std::wstring & czSectionOriginal             /**< In:     the configuration-section where you can find above specified parameter */
    ) 
{
    HRESULT                          hResult;
    int                              iResult;
    basic_string <char>::size_type   iTotLenght = czSectionOriginal.length();
    basic_string <char>::size_type   iStrLenght;
    wchar_t                          wsSectionCustom[256]; 


    //--- Find if anything to expand
    if ((iTotLenght == 0)||(czSectionOriginal[0] != '$'))
    {
        //nothing to replace
        return(czSectionOriginal);
    }

    //--- check for EIDMW_CNF_MACRO_INSTALL
    iStrLenght = wcslen(EIDMW_CNF_MACRO_INSTALL);
    iResult = czSectionOriginal.compare(0, iStrLenght, EIDMW_CNF_MACRO_INSTALL);
    if (iResult == 0)
    {
        //replace EIDMW_CNF_MACRO_INSTALL
        std::wstring czSectionExpanded = CConfig::GetString(EIDMW_CNF_GENERAL_INSTALLDIR, EIDMW_CNF_SECTION_GENERAL);
        
        //add part after the $-macro
        czSectionExpanded.append(czSectionOriginal.substr(iStrLenght, iTotLenght-iStrLenght));//add part after the $-macro
        return(czSectionExpanded);
    }

    //--- check for EIDMW_CNF_MACRO_HOME
    // returns by default "C:\WINDOWS\system32\config\systemprofile\Application Data" for services.
    iStrLenght = wcslen(EIDMW_CNF_MACRO_HOME);
    iResult = czSectionOriginal.compare(0, iStrLenght, EIDMW_CNF_MACRO_HOME);
    if (iResult == 0)
    {
        //replace EIDMW_CNF_MACRO_HOME
        hResult = SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_DEFAULT, wsSectionCustom);

        //non-user SW(eg.: services) returns: C:\WINDOWS\system32\config\systemprofile\Application Data, replace by common dir
        if((hResult != S_OK) || ((hResult == S_OK) && (wcsstr(wsSectionCustom, L":\\WINDOWS") != NULL)))
        {
            //try common path when problems or when no user found
            hResult = SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_DEFAULT, wsSectionCustom);
            if(hResult != S_OK)
            {
                //can not replace, return original string
                return(czSectionOriginal);
            }
        }
        std::wstring czSectionExpanded(wsSectionCustom);    

 	//	czSectionExpanded.append(WDIRSEP);
		//czSectionExpanded.append(EIDMW_CNF_MACRO_COMMON_SUBDIR);
       
        //add part after the $-macro
        czSectionExpanded.append(czSectionOriginal.substr(iStrLenght, iTotLenght-iStrLenght));//add part after the $-macro
        return(czSectionExpanded);
    }

    //--- check for EIDMW_CNF_MACRO_COMMON
    iStrLenght = wcslen(EIDMW_CNF_MACRO_COMMON);
    iResult = czSectionOriginal.compare(0, iStrLenght, EIDMW_CNF_MACRO_COMMON);
    if (iResult == 0)
    {
        //replace EIDMW_CNF_MACRO_COMMON

        //hResult = SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_DEFAULT, wsSectionCustom);
        //if(hResult != S_OK)
        //{
        //    //can not replace, return original string
        //    return(czSectionOriginal);
        //}
        //std::wstring czSectionExpanded(wsSectionCustom);   

//////////////////////////////////////////////////////
//Problem of access right for the user with limited right
        hResult = SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_DEFAULT, wsSectionCustom);

        //non-user SW(eg.: services) returns: C:\WINDOWS\system32\config\systemprofile\Application Data, replace by common dir
        if((hResult != S_OK) || ((hResult == S_OK) && (wcsstr(wsSectionCustom, L":\\WINDOWS") != NULL)))
        {
            //try common path when problems or when no user found
            hResult = SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_DEFAULT, wsSectionCustom);
            if(hResult != S_OK)
            {
                //can not replace, return original string
                return(czSectionOriginal);
            }
        }
        std::wstring czSectionExpanded(wsSectionCustom);    
//////////////////////////////////////////////////////

		czSectionExpanded.append(WDIRSEP);
		czSectionExpanded.append(EIDMW_CNF_MACRO_COMMON_SUBDIR);

        //add part after the $-macro
        czSectionExpanded.append(czSectionOriginal.substr(iStrLenght, iTotLenght-iStrLenght));//add part after the $-macro
        return(czSectionExpanded);
    }

    return(czSectionOriginal);
}