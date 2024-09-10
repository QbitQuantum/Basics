/**
  Display the confirm text and get user confirmation.

  @param[in] TpmPpCommand  The requested TPM physical presence command.

  @retval    TRUE          The user has confirmed the changes.
  @retval    FALSE         The user doesn't confirm the changes.
**/
BOOLEAN
UserConfirm (
  IN      UINT8                     TpmPpCommand
  )
{
  CHAR16                            *ConfirmText;
  CHAR16                            *TmpStr1;
  CHAR16                            *TmpStr2; 
  UINTN                             BufSize;
  BOOLEAN                           CautionKey;
  UINT16                            Index;
  CHAR16                            DstStr[81];
    
  TmpStr2     = NULL;
  CautionKey  = FALSE;
  BufSize     = CONFIRM_BUFFER_SIZE;
  ConfirmText = AllocateZeroPool (BufSize);
  ASSERT (ConfirmText != NULL);

  switch (TpmPpCommand) {
    case PHYSICAL_PRESENCE_ENABLE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ENABLE));
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_DISABLE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_DISABLE));
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;
      
    case PHYSICAL_PRESENCE_ACTIVATE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACTIVATE));
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_DEACTIVATE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_DEACTIVATE));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1); 
      break;

    case PHYSICAL_PRESENCE_CLEAR:
      CautionKey = TRUE;
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CLEAR));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING_CLEAR));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      StrnCat (ConfirmText, L" \n\n", (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);      

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CAUTION_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_ENABLE_ACTIVATE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ENABLE_ACTIVATE));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NOTE_ON));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_DEACTIVATE_DISABLE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_DEACTIVATE_DISABLE));
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));      
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NOTE_OFF));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_SET_OWNER_INSTALL_TRUE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ALLOW_TAKE_OWNERSHIP));
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));      
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_SET_OWNER_INSTALL_FALSE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_DISALLOW_TAKE_OWNERSHIP));
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));      
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_ENABLE_ACTIVATE_OWNER_TRUE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_TURN_ON));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NOTE_ON));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_DEACTIVATE_DISABLE_OWNER_FALSE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_TURN_OFF));
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));      
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NOTE_OFF));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_DEFERRED_PP_UNOWNERED_FIELD_UPGRADE:
      CautionKey = TRUE;
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_UNOWNED_FIELD_UPGRADE));
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_UPGRADE_HEAD_STR));      
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);
      
      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING_MAINTAIN));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CAUTION_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_SET_OPERATOR_AUTH:
      //
      // TPM_SetOperatorAuth
      // This command requires UI to prompt user for Auth data
      // Here it is NOT implemented
      //
      break;

    case PHYSICAL_PRESENCE_CLEAR_ENABLE_ACTIVATE:
      CautionKey = TRUE;
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CLEAR_TURN_ON));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NOTE_ON));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING_CLEAR));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING_CLEAR_CONT));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CAUTION_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_SET_NO_PPI_PROVISION_TRUE:
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NO_PPI_PROVISION));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_PPI_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ACCEPT_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NO_PPI_INFO));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_SET_NO_PPI_CLEAR_TRUE:
      CautionKey = TRUE;
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CLEAR));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_PPI_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NOTE_CLEAR));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING_CLEAR));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      StrnCat (ConfirmText, L" \n\n", (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1); 

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CAUTION_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NO_PPI_INFO));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_SET_NO_PPI_MAINTENANCE_TRUE:
      CautionKey = TRUE;
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NO_PPI_MAINTAIN));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_PPI_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING_MAINTAIN));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CAUTION_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NO_PPI_INFO));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_ENABLE_ACTIVATE_CLEAR:
      CautionKey = TRUE;
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ENABLE_ACTIVATE_CLEAR));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING_CLEAR));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      StrnCat (ConfirmText, L" \n\n", (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CAUTION_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    case PHYSICAL_PRESENCE_ENABLE_ACTIVATE_CLEAR_ENABLE_ACTIVATE:
      CautionKey = TRUE;
      TmpStr2 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_ENABLE_ACTIVATE_CLEAR_ENABLE_ACTIVATE));

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_HEAD_STR));
      UnicodeSPrint (ConfirmText, BufSize, TmpStr1, TmpStr2);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_NOTE_ON));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING_CLEAR));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_WARNING_CLEAR_CONT));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);

      TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_CAUTION_KEY));
      StrnCat (ConfirmText, TmpStr1, (BufSize / sizeof (CHAR16)) - StrLen (ConfirmText) - 1);
      FreePool (TmpStr1);
      break;

    default:
      ;
  }

  if (TmpStr2 == NULL) {
    FreePool (ConfirmText);
    return FALSE;
  }

  TmpStr1 = PhysicalPresenceGetStringById (STRING_TOKEN (TPM_REJECT_KEY));
  BufSize -= StrSize (ConfirmText);
  UnicodeSPrint (ConfirmText + StrLen (ConfirmText), BufSize, TmpStr1, TmpStr2);

  DstStr[80] = L'\0';
  for (Index = 0; Index < StrLen (ConfirmText); Index += 80) {
    StrnCpy(DstStr, ConfirmText + Index, 80);    
    Print (DstStr);    
  }
  
  FreePool (TmpStr1);
  FreePool (TmpStr2);
  FreePool (ConfirmText);

  if (ReadUserKey (CautionKey)) {
    return TRUE;
  }

  return FALSE;  
}