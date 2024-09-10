/**
Test code for INC042690 - Bi-directional MIME types are not supported in Charconv
The bi-directional MIME types only indicate how to treat the layout of the mail,
the actual character conversion should be the same as for the exisiting ISO-8859-6/ISO-8859-8 plugins

@SYMTestCaseID          SYSLIB-CHARCONV-CT-0542
@SYMTestCaseDesc        Tests the Bi-directional MIME
@SYMTestPriority        Medium
@SYMTestActions         Tests for conversions of ISO_8859-6 UID to MIB
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
void CT_ISO8859X::testInc042690L()
	{
	INFO_PRINTF1(_L(" @SYMTestCaseID:SYSLIB-CHARCONV-CT-0542 Test for INC042690 "));

	RFs fileServerSession;
	CleanupClosePushL(fileServerSession);
	User::LeaveIfError(fileServerSession.Connect());
	CCnvCharacterSetConverter* characterSetConverter=CCnvCharacterSetConverter::NewLC();

	// check that the character set value of '81' is converted to the ISO_8859-6 UID (0x10008a29)
	test(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(81,fileServerSession)==KCharacterSetIdentifierIso88596);
	INFO_PRINTF1(_L("\nMIB 81->Char Set ISO_8859-6 UID - OK"));

	// check that the character set value of '82' is converted to the ISO_8859-6 UID (0x10008a29)
	test(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(82,fileServerSession)==KCharacterSetIdentifierIso88596);
	INFO_PRINTF1(_L("\nMIB 82->Char Set ISO_8859-6 UID - OK"));

	// check that the character set value of '84' is converted to the ISO_8859-8 UID (0x10008a2a)
	test(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(84,fileServerSession)==KCharacterSetIdentifierIso88598);
	INFO_PRINTF1(_L("\nMIB 84->Char Set ISO_8859-8 UID - OK"));

	// check that the character set value of '85' is converted to the ISO_8859-8 UID (0x10008a2a)
	test(characterSetConverter->ConvertMibEnumOfCharacterSetToIdentifierL(85,fileServerSession)==KCharacterSetIdentifierIso88598);
	INFO_PRINTF1(_L("\nMIB 85->Char Set ISO_8859-8 UID - OK"));

	// check that the ISO_8859-6 UID (0x10008a29) is converted to the character set value of '9'
	test(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(KCharacterSetIdentifierIso88596,fileServerSession)==9);
	INFO_PRINTF1(_L("\nChar Set ISO_8859-6 UID->MIB - OK"));

	// check that the ISO_8859-8 UID (0x10008a2a) is converted to the character set value of '11'
	test(characterSetConverter->ConvertCharacterSetIdentifierToMibEnumL(KCharacterSetIdentifierIso88598,fileServerSession)==11);
	INFO_PRINTF1(_L("\nChar Set ISO_8859-8 UID->MIB - OK"));

	INFO_PRINTF1(_L("\nTest for INC042690 complete:\n"));
	CleanupStack::PopAndDestroy(2); // characterSetConverter and fileServerSession
	}