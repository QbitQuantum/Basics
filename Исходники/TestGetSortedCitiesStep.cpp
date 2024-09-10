TVerdict CTestGetSortedCitiesStep::doTestStepL()
/**
 * @return - TVerdict code
 * Override of base class virtual
 * The test is tesing GetCitiesL() with various input parameters,
 * firstly the TzId and sort key, then a default city and sort key
 * and finally just a sort key so all cities are found.
 */
	{ 
   	SetTestStepResult(EPass);
    TRAPD(errL, iLocalizer = CTzLocalizer::NewL());
 	__UHEAP_MARK;

 	RTz tz;
    User::LeaveIfError(tz.Connect());
    CleanupClosePushL(tz);
    CTzUserData* userdata = CTzUserData::NewL(tz);
    CleanupStack::PushL(userdata); 
 	//CreateAUserRuleLC should be in doTestStepPreambleL and clean the data in postamble when Shazia submits her code
    CreateUserRuleLC(*userdata);
   	iLocalizer->SetDataSource(iDataSource);
 	if (errL == KErrNone)
	    {
	    CTzLocalizedCityArray* cities = NULL;		  	  	  	  
	 	TInt tzId;
	  	TPtrC defaultCityFromIni; 
	  	  
	  	if (GetIntFromConfig(ConfigSection(),KTzIdTag,tzId))
	  	    {
	  	    _LIT(KTzIdFound,"Get sorted Cities : tz id tag found");
	  	    INFO_PRINTF1(KTzIdFound);
	  	  	TRAPD(err1, cities = iLocalizer->GetCitiesL(tzId, iSortOrder));
	  	  	if (err1 != KErrNone)
	  	  	    {
	  	  	    _LIT(KGetCitiesLeft,"Get sorted Cities : GetCitiesL left");
	  	  	    ERR_PRINTF1(KGetCitiesLeft);
	  	  	    SetTestStepResult(EFail); 	
	  	  	    }
	  	  	    
	  	  	    CleanupStack::PushL(cities);	  	  	
	  	    }
	  	else if (GetStringFromConfig(ConfigSection(),KDefaultCityTag,defaultCityFromIni))
	  	    {	  	  	
	  	    TBuf<40> buf;
	  	    buf.Copy(defaultCityFromIni);
	  	    _LIT(KDefCityFound,"Get sorted Cities : Default City Tag found = %S");
            INFO_PRINTF2(KDefCityFound, &buf);
	  	  	CTzLocalizedCity* defaultCity = NULL;
	  	    TRAPD(errdefcity, defaultCity = iLocalizer->GetDefaultCityL(KDefaultTzId));
	  	    if (errdefcity == KErrNone)
	            {
	 	        CleanupStack::PushL(defaultCity);
	  	        TRAPD(err2, cities = iLocalizer->GetCitiesL(*defaultCity,iSortOrder));
	  	  	    if (err2 != KErrNone)	
	  	  	        {
	  	  	        _LIT(KGetCities2Left,"Get sorted Cities : GetCitiesL(city,sort) left");
	  	  	        ERR_PRINTF1(KGetCities2Left);
	  	  	        SetTestStepResult(EFail); 
	  	  	        }
	  	  	   
	  	  	    CleanupStack::PopAndDestroy(defaultCity);
	  	  	    CleanupStack::PushL(cities);
	  	  	    }
	  	  	else
	  	  	    {
	  	  	    _LIT(KGetDefCityLeft,"Get sorted Cities : GetDefaultCity left");
	  	  	    ERR_PRINTF1(KGetDefCityLeft);
	  	  	   	SetTestStepResult(EFail);
	  	  	    }	  	  		  	  	
	  	    }	  	  	  	  	  	  
	  	else
	  	    {
	  	  	TRAPD(err3, cities = iLocalizer->GetCitiesL(iSortOrder));
	  	  	if (err3 != KErrNone)
	  	  	    {
	  	  	    _LIT(KGetCities3Left,"Get sorted Cities : GetCities(sort) left");
	  	  		ERR_PRINTF1(KGetCities3Left);
	  	  	   	SetTestStepResult(EFail);
	  	  	    }
	  	  	CleanupStack::PushL(cities);
	  	    }
	  	
	  	//Loop through the cities array and match against ini file data  	  	  
        if (cities != NULL)
            {
            TBuf<50> cityTag;
            for(TInt n=0; n < cities->Count(); n++)
                {
                cityTag = KCityTag;
                cityTag.AppendNum(n + 1);
          	
                TPtrC CityNameFromIni;	
                TPtrC temp(cities->At(n).Name() );         	
                if ( !GetStringFromConfig(ConfigSection(), cityTag, CityNameFromIni)) //i.e. cities->At(n).Name() != CityNameFromIni)
                    {          
					if ( (&temp)->Length()!=0  )
						{
						if ( (&CityNameFromIni)->Length()!=0)
							{
							_LIT(KMessage,"Got city: %S, instead of: %S");
		           	        ERR_PRINTF3(KMessage, &temp, &CityNameFromIni);
							}
						else
							{
							_LIT(KMessage,"Got city: %S, Was expecting NULL");
           	        		ERR_PRINTF2(KMessage, &temp);
							}
						}
					else
						{
						_LIT(KMessage,"Got NULL, Was expecting city: %S");
           	        	ERR_PRINTF2(KMessage, &CityNameFromIni);
						}
           	        SetTestStepResult(EFail);          		
                    }
                else if (cities->At(n).Name()!=CityNameFromIni)
                	{
                   	_LIT(KNoMatch,"TestGetSortedCitiesStep: City names do not match.  Expected %S, got %S.");
                   	
                   	ERR_PRINTF3(KNoMatch, &CityNameFromIni, &temp);      
                	SetTestStepResult(EFail);  
                	}
                }
            }
            CleanupStack::PopAndDestroy(cities);    	
	    }
    else
	    {
	    SetTestStepResult(EFail);
	    _LIT(KNewLeft,"TestGetSortedCitiesStep: Problem with NewL");
		ERR_PRINTF1(KNewLeft);	
     	}
	
   //the following doesn't need when Shazia submits her code
   	CleanupStack::PopAndDestroy(2);
	 
    __UHEAP_MARK;
	return TestStepResult();
	}