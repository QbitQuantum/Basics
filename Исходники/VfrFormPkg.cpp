EFI_VFR_RETURN_CODE
CFormPkg::DeclarePendingQuestion (
  IN CVfrVarDataTypeDB   &lCVfrVarDataTypeDB,
  IN CVfrDataStorage     &lCVfrDataStorage,
  IN CVfrQuestionDB      &lCVfrQuestionDB,
  IN EFI_GUID            *LocalFormSetGuid,
  IN UINT32 LineNo
  )
{
  SPendingAssign *pNode;
  CHAR8          *VarStr;
  UINT32         ArrayIdx;
  CHAR8          FName[MAX_NAME_LEN];
  EFI_VFR_RETURN_CODE  ReturnCode;
  EFI_VFR_VARSTORE_TYPE VarStoreType  = EFI_VFR_VARSTORE_INVALID;

  for (pNode = PendingAssignList; pNode != NULL; pNode = pNode->mNext) {
    if (pNode->mFlag == PENDING) {
      //
      //  declare this question as Numeric in SuppressIf True
      //
      // SuppressIf
      CIfrSuppressIf SIObj;
      SIObj.SetLineNo (LineNo);
      
      //TrueOpcode
      CIfrTrue TObj (LineNo);
      
      //Numeric qeustion
      CIfrNumeric CNObj;
      EFI_VARSTORE_INFO Info; 
  	  EFI_QUESTION_ID   QId   = EFI_QUESTION_ID_INVALID;

      CNObj.SetLineNo (LineNo);
      CNObj.SetPrompt (0x0);
      CNObj.SetHelp (0x0);

      //
      // Register this question, assume it is normal question, not date or time question
      //
      VarStr = pNode->mKey;
      ReturnCode = lCVfrQuestionDB.RegisterQuestion (NULL, VarStr, QId);
      if (ReturnCode != VFR_RETURN_SUCCESS) {
        gCVfrErrorHandle.HandleError (ReturnCode, pNode->mLineNo, pNode->mKey);
        return ReturnCode;
      }
 
#ifdef VFREXP_DEBUG
      printf ("Undefined Question name is %s and Id is 0x%x\n", VarStr, QId);
#endif
      //
      // Get Question Info, framework vfr VarName == StructName
      //
      ReturnCode = lCVfrVarDataTypeDB.ExtractFieldNameAndArrary (VarStr, FName, ArrayIdx);
      if (ReturnCode != VFR_RETURN_SUCCESS) {
        gCVfrErrorHandle.PrintMsg (pNode->mLineNo, pNode->mKey, "Error", "Var string is not the valid C variable");
        return ReturnCode;
      }
      //
      // Get VarStoreType
      //
      ReturnCode = lCVfrDataStorage.GetVarStoreType (FName, VarStoreType);
      if (ReturnCode == VFR_RETURN_UNDEFINED) {
        lCVfrDataStorage.DeclareBufferVarStore (
                           FName, 
                           LocalFormSetGuid, 
                           &lCVfrVarDataTypeDB, 
                           FName,
                           EFI_VARSTORE_ID_INVALID,
                           FALSE
                           );
        ReturnCode = lCVfrDataStorage.GetVarStoreType (FName, VarStoreType);  
      }
      if (ReturnCode != VFR_RETURN_SUCCESS) {
        gCVfrErrorHandle.PrintMsg (pNode->mLineNo, FName, "Error", "Var Store Type is not defined");
        return ReturnCode;
      }
      
      ReturnCode = lCVfrDataStorage.GetVarStoreId (FName, &Info.mVarStoreId);
      if (ReturnCode != VFR_RETURN_SUCCESS) {
        gCVfrErrorHandle.PrintMsg (pNode->mLineNo, FName, "Error", "Var Store Type is not defined");
        return ReturnCode;
      }

      if (*VarStr == '\0' && ArrayIdx != INVALID_ARRAY_INDEX) {
        ReturnCode = lCVfrDataStorage.GetNameVarStoreInfo (&Info, ArrayIdx);
      } else {
        if (VarStoreType == EFI_VFR_VARSTORE_EFI) {
          ReturnCode = lCVfrDataStorage.GetEfiVarStoreInfo (&Info);
        } else if (VarStoreType == EFI_VFR_VARSTORE_BUFFER) {
          VarStr = pNode->mKey;
          ReturnCode = lCVfrVarDataTypeDB.GetDataFieldInfo (VarStr, Info.mInfo.mVarOffset, Info.mVarType, Info.mVarTotalSize);
        } else {
          ReturnCode = VFR_RETURN_UNSUPPORTED;
        }
      }
      if (ReturnCode != VFR_RETURN_SUCCESS) {
        gCVfrErrorHandle.HandleError (ReturnCode, pNode->mLineNo, pNode->mKey);
        return ReturnCode;
      }

      CNObj.SetQuestionId (QId);
      CNObj.SetVarStoreInfo (&Info);
      CNObj.SetFlags (0, Info.mVarType);

      //
      // For undefined Efi VarStore type question
      // Append the extended guided opcode to contain VarName
      //
      if (VarStoreType == EFI_VFR_VARSTORE_EFI) {
        CIfrVarEqName CVNObj (QId, Info.mInfo.mVarName);
        CVNObj.SetLineNo (LineNo);
      }
      
      //
      // End for Numeric
      //
      CIfrEnd CEObj; 
      CEObj.SetLineNo (LineNo);
      //
      // End for SuppressIf
      //
      CIfrEnd SEObj;
      SEObj.SetLineNo (LineNo);
    }
  }
  return VFR_RETURN_SUCCESS;
}