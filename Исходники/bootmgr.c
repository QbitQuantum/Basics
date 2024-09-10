EFI_STATUS
EFIAPI
ShellAppMain (
  IN UINTN Argc,
  IN CHAR16 **Argv
  )
{
  EFI_STATUS    Status;
  UINT16        *BootVariable;
  UINTN         BootVariableSize;
  UINT16        LDAttr;
  CHAR16        *Name;
  UINTN         NewNameSize;
  UINTN         NameSize;
  UINTN         i;
  UINT32        Attr;
  EFI_GUID      VarGuid;
  

  ParseOpt(Argc, Argv);

  //------------Usage-----------------------
  if (opts.usage){
  	Usage();
  	return EFI_SUCCESS;
  }
  //----------Set BootOrder-----------------
  if (opts.set_bootorder){
  	BootVariable = mGetVariable(L"BootOrder", &gEfiGlobalVariableGuid, &BootVariableSize, &Attr);
    BootVariable[0]=opts.bootnum;
    Status = gRT->SetVariable(L"BootOrder", &gEfiGlobalVariableGuid, Attr, BootVariableSize, BootVariable);
    if (!EFI_ERROR(Status))
      Print(L"Set first boot to Boot%04x\n", opts.bootnum);
    return Status;
  }


  //----------Show Boot UEFI variables--------
  //get BootCurrent
  BootVariable = mGetVariable(L"BootCurrent", &gEfiGlobalVariableGuid, &BootVariableSize, NULL);
  if (BootVariable != NULL)
    Print(L"BootCurrent: %04x\n", *BootVariable);
  //get BootOrder
  BootVariable = mGetVariable(L"BootOrder", &gEfiGlobalVariableGuid, &BootVariableSize, &Attr);
  if (BootVariable != NULL){
  	Print(L"BootOrder:  ");
    for(i=0; i<(BootVariableSize/2); i++){
    	Print(L" %04x ",BootVariable[i]);
    }
    Print(L"\n");
  }

  //Print all BOOT#### Load Options
  NameSize = sizeof(CHAR16);
  Name     = AllocateZeroPool(NameSize);
  for (i=0; ;i++ ){
  	NewNameSize = NameSize;
  	//search all EFI variables
  	Status = gRT->GetNextVariableName (&NewNameSize, Name, &VarGuid);
  	  if (Status == EFI_BUFFER_TOO_SMALL) {
      Name = ReallocatePool (NameSize, NewNameSize, Name);
      Status = gRT->GetNextVariableName (&NewNameSize, Name, &VarGuid);
      NameSize = NewNameSize;
    }
    //
    if (Status == EFI_NOT_FOUND) {
      break;
    }
    //skip if not Global variable
    if (!CompareGuid(&VarGuid, &gEfiGlobalVariableGuid))
    	continue;
    //check BOOT#### variable
    if(!StrnCmp(Name, L"Boot", 4) &&
    	IsCharDigit(Name[4]) && IsCharDigit(Name[5]) &&
    	IsCharDigit(Name[6]) && IsCharDigit(Name[7]))
    {
    	Print(L"%s:", Name);
        //get BOOT####
        BootVariable = mGetVariable(Name, &gEfiGlobalVariableGuid, &BootVariableSize, NULL);
        //print attribute
        LDAttr = BootVariable[0];
        if (opts.show_verbose){
        	i = 6;   //for adjust display
          if (LDAttr == 0)
        	Print(L"CB*", i--);     //category boot
          if (LDAttr & 1)
           	Print(L"A* ", i--);      //active
          if (LDAttr & 2)
           	Print(L"FR*", i--);     //force reconnect
          if (LDAttr & 8)
           	Print(L"H* ", i--);      //hidden
          if (LDAttr & 0x100)
           	Print(L"CA*", i--);     //category app
           //Print(L"\n");
           while (i--){
           	Print(L"   ");
           }
        }
        //print EFI_LOAD_OPTION description
        Print(L" %s",(CHAR16 *)(BootVariable+3));
        Print(L"\n");
        
    }
  }

  return Status;
}