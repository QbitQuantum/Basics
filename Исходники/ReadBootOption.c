EFI_LOAD_OPTION* ReadBootoptions(IN UINT16 BootIndex)
{
    EFI_STATUS Status;
    UINTN OptionSize;
    CHAR16 BootVarName[15];
    EFI_LOAD_OPTION *BootOption;
    
    Swprintf( BootVarName, L"Boot%04X", BootIndex);         

    OptionSize = 0;
    Status = pRS->GetVariable( BootVarName, &gEfiGlobalVariableGuid, NULL, &OptionSize, NULL);
    if (Status != EFI_NOT_FOUND)
    {       
        BootOption = Malloc( OptionSize );
        Status = pRS->GetVariable( BootVarName, &gEfiGlobalVariableGuid, NULL, &OptionSize, BootOption);
        if (EFI_ERROR(Status)) {
            return NULL;
        }
        else{
        	Print(L"Boot%04x\n\r",BootIndex);
        	Print(L"Length:%d\n\r",OptionSize);
        	return BootOption;
        }        
    }
    else
        return NULL;

}