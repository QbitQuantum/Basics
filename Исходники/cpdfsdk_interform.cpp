CFX_WideString CPDFSDK_InterForm::OnFormat(CPDF_FormField* pFormField,
                                           FX_BOOL& bFormatted) {
  CFX_WideString sValue = pFormField->GetValue();
  CPDFSDK_Environment* pEnv = m_pDocument->GetEnv();
  ASSERT(pEnv);
  if (!pEnv->IsJSInitiated()) {
    bFormatted = FALSE;
    return sValue;
  }

  IJS_Runtime* pRuntime = m_pDocument->GetJsRuntime();
  pRuntime->SetReaderDocument(m_pDocument);

  if (pFormField->GetFieldType() == FIELDTYPE_COMBOBOX &&
      pFormField->CountSelectedItems() > 0) {
    int index = pFormField->GetSelectedIndex(0);
    if (index >= 0)
      sValue = pFormField->GetOptionLabel(index);
  }

  bFormatted = FALSE;

  CPDF_AAction aAction = pFormField->GetAdditionalAction();
  if (aAction.GetDict() && aAction.ActionExist(CPDF_AAction::Format)) {
    CPDF_Action action = aAction.GetAction(CPDF_AAction::Format);
    if (action.GetDict()) {
      CFX_WideString script = action.GetJavaScript();
      if (!script.IsEmpty()) {
        CFX_WideString Value = sValue;

        IJS_Context* pContext = pRuntime->NewContext();
        pContext->OnField_Format(pFormField, Value, TRUE);
        CFX_WideString sInfo;
        FX_BOOL bRet = pContext->RunScript(script, &sInfo);
        pRuntime->ReleaseContext(pContext);

        if (bRet) {
          sValue = Value;
          bFormatted = TRUE;
        }
      }
    }
  }

  return sValue;
}