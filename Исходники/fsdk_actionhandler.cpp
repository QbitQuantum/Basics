FX_BOOL CPDFSDK_ActionHandler::ExecuteScreenAction(const CPDF_Action& action, CPDF_AAction::AActionType type, 
										CPDFSDK_Document* pDocument,/* CReader_DocView* pDocView,*/ CPDFSDK_Annot* pScreen, CFX_PtrList& list)
{
	ASSERT(pDocument != NULL);

	if (list.Find((CPDF_Dictionary*)action))
		return FALSE;
	list.AddTail((CPDF_Dictionary*)action);

	CPDFDoc_Environment* pEnv = pDocument->GetEnv();
	ASSERT(pEnv);
	if (action.GetType() == CPDF_Action::JavaScript)
	{
		if(pEnv->IsJSInitiated())
		{
			CFX_WideString swJS = action.GetJavaScript();
			if (!swJS.IsEmpty())
			{
				IFXJS_Runtime* pRuntime = pDocument->GetJsRuntime();
				ASSERT(pRuntime != NULL);

				pRuntime->SetReaderDocument(pDocument);

				IFXJS_Context* pContext = pRuntime->NewContext();
				ASSERT(pContext != NULL);

	// 			switch (type)
	// 			{
	// 			case CPDF_AAction::CursorEnter:
	// 				pContext->OnScreen_MouseEnter(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			case CPDF_AAction::CursorExit:
	// 				pContext->OnScreen_MouseExit(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			case CPDF_AAction::ButtonDown:
	// 				pContext->OnScreen_MouseDown(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			case CPDF_AAction::ButtonUp:
	// 				pContext->OnScreen_MouseUp(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			case CPDF_AAction::GetFocus:
	// 				pContext->OnScreen_Focus(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			case CPDF_AAction::LoseFocus:
	// 				pContext->OnScreen_Blur(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			case CPDF_AAction::PageOpen:
	// 				pContext->OnScreen_Open(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			case CPDF_AAction::PageClose:
	// 				pContext->OnScreen_Close(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			case CPDF_AAction::PageVisible:
	// 				pContext->OnScreen_InView(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			case CPDF_AAction::PageInvisible:
	// 				pContext->OnScreen_OutView(IsCTRLpressed(), IsSHIFTpressed(), pScreen);
	// 				break;
	// 			default:
	// 				ASSERT(FALSE);
	// 				break;
	// 			}

				CFX_WideString csInfo;
				FX_BOOL bRet = pContext->RunScript(swJS, csInfo);
				if (!bRet)
				{
					//CBCL_FormNotify::MsgBoxJSError(pPageView->GetPageViewWnd(), csInfo);
				}

				pRuntime->ReleaseContext(pContext);
			}
		}
	}
	else
	{
		DoAction_NoJs(action, pDocument/*, pDocView*/);
	}

// 	if (!IsValidDocView(pDocument, pDocView))
// 		return FALSE;

	for (FX_INT32 i=0,sz=action.GetSubActionsCount(); i<sz; i++)
	{
		CPDF_Action subaction = action.GetSubAction(i);
		if (!ExecuteScreenAction(subaction, type, pDocument,/* pDocView,*/ pScreen, list)) return FALSE;
	}

	return TRUE;
}