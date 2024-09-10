CComBSTR CbDevice::GetErrMsg(short code)
{
    char ErrMsg[ERRSTRLEN+16];
    strcpy(ErrMsg,"MCC: ");
    cbGetErrMsg((short)code,ErrMsg+strlen(ErrMsg));
    ATLTRACE2(MCC_UL_CALL,3,"cbGetErrMsg(code = %d,ErrMsg); result: ErrMsg=%s\n",code,ErrMsg);
    
    // Allocate memory and copy input retVal. The Detach is required
    // so that the memory will not be freed. We need the string to be 
    // returned to the 'engine'.
    
    return ErrMsg;
}