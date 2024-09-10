/**
 * @see GetInfoCpm test case NET-CONFIGURATOR-I-0018-HP
 *
 * doTestStepL virtual function does the below action
 * Connect to a configurator
 * Configurator get the module inidata section. Inidata section contains
   module initialisation information in the module's configuration file.
 * close the connection to configuator
 * Expected:-GetInfoCpm return kerrNone
*/
TVerdict CGetInfoCpm::doTestStepL()
	{

	SetTestStepResult(EFail);
	_LIT8(KNameDummyCpm,"DummyCpm");

	RBuf8 data;
	data.Create(100);
	TInt actualdatasize;

	//Configurator call to get the module inidata section
	TInt error = iConfigurator.GetModuleIniData(KNameDummyCpm(), data, actualdatasize);
	if (error == KErrOverflow)
		{
		INFO_PRINTF2(_L("GetModuleIniData returned KErrOverflow (%d)  \n"), error);
		data.ReAlloc(actualdatasize);
	    error = iConfigurator.GetModuleIniData(KNameDummyCpm(), data, actualdatasize);
	  	}
	else if (error == KErrRSModuleUnknown )
		{
		INFO_PRINTF2(_L("GetModuleIniData returned KErrRSModuleUnknown (%d)  \n"), error);
		}
	else if (error == KErrNone)
		{
	    INFO_PRINTF1(_L("GetModuleIniData Sucessful"));
	    SetTestStepResult(EPass);
		}
	else
		{
		INFO_PRINTF2(_L("GetModuleIniData  (DummyCpm) returned Error (%d)  \n"), error);
		}

    data.Close();
	return TestStepResult();
	}