TVerdict CWriteStringStep::doTestStepL()
/**
 * @return - TVerdict code
 * Override of base class pure virtual
 * Our implementation only gets called if the base class doTestStepPreambleL() did
 * not leave. That being the case, the current test result value will be EPass.
 */
	{
	INFO_PRINTF1(_L("This step tests WriteStringToConfig function."));
	SetTestStepResult(EFail);
	
	TPtrC originalValue;
	TBool ret = EFalse;
	
	if(!GetStringFromConfig(ConfigSection(),KTe_RegStepTestSuiteString, originalValue))
		{
		// Leave if there's any error.
		User::Leave(KErrNotFound);
		}

	INFO_PRINTF2(_L("The Original String is %S"), &originalValue); // Block end
	
	RBuf buf;
	buf.Create(originalValue.Length());
	buf.Copy(originalValue);
	
	_LIT(KText,"GoodBye Jason");
	TBufC<16> buf1(KText); 
	TPtrC TheString1(buf1);
	if (WriteStringToConfig(ConfigSection(), KTe_RegStepTestSuiteString, TheString1))
		{
		if (GetStringFromConfig(ConfigSection(), KTe_RegStepTestSuiteString, TheString1) && 0==TheString1.Compare(KText()))
			{
			INFO_PRINTF2(_L("Changed String To %S"),&TheString1); 
			ret = ETrue;
			}
		}
		
	_LIT(KText2,"Hello Jason");
	TBufC<16> buf2(KText2); 
	TPtrC TheString2(buf2);
	
	if (WriteStringToConfig(ConfigSection(), KTe_RegStepTestSuiteString, TheString2))
		{
		if (GetStringFromConfig(ConfigSection(), KTe_RegStepTestSuiteString, TheString2) && 0==TheString2.Compare(KText2()))
			{
			INFO_PRINTF2(_L("Changed String To %S"), &TheString2); 
			}
		}
	else
		{
		ret = EFalse;
		}
	
	if (!WriteStringToConfig(ConfigSection(), KTe_RegStepTestSuiteString, buf))
		{
		ret = EFalse;
		}
	buf.Close();
	
	if (ret)
		{
		SetTestStepResult(EPass);
		}
	
	return TestStepResult();
	}