int main()
{
    __UHEAP_MARK;
    int retval =ESuccess;
    wchar_t* mywcharstring = L"Hello Widechar String";
    int wchar_length= wcslen(mywcharstring);
    TBufC8<30> buf;
    TPtr8 myTptr = buf.Des();
    char* temp=new char[30];
    retval = WcharpToTptr8(mywcharstring,temp, myTptr);

    int buf_len = myTptr.Length();
    if (retval ==ESuccess &&\
    wchar_length == buf_len  )
    {
    printf("wcharptotptr8 boundary1 Passed\n");
    }
    else
    {
    assert_failed = true;	
    printf("wcharptotptr8 boundary1 Failed\n");
    }      
    delete[] temp;
    __UHEAP_MARKEND;
    testResultXml("test_wcharptotptr8_boundary1");
	
	return 0;
}