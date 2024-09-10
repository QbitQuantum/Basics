int main()
{
    int retval =ESuccess;
    wchar_t* mywcharstring = L"Hello Widechar String";
    int wchar_length= wcslen(mywcharstring);
    TPtrC myTptrc;
    retval = WcharpToTptrc16(mywcharstring, myTptrc);

    int buf_len = myTptrc.Length();
    if (retval ==ESuccess &&\
    wchar_length == buf_len  )
    {
    printf("wcharptotptrc16 boundary1 Passed\n");
    }
    else
    {
    assert_failed = true;
    printf("wcharptotptrc16 boundary1 Failed\n");
    }      
    testResultXml("test_wcharptotptrc16_boundary1");
	
	return 0;
}