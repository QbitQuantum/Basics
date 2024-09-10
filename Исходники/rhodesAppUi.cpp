// -----------------------------------------------------------------------------
// CRhodesAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CRhodesAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			
			if ( iSyncEngineWrap )
				iSyncEngineWrap->TerminateThread();
			
			Exit();
			break;
		case EHelp:
			{

			CArrayFix<TCoeHelpContext>* buf = CCoeAppUi::AppHelpContextL();
			HlpLauncher::LaunchHelpApplicationL(iEikonEnv->WsSession(), buf);
			}
			break;
		case EAbout:
			{

			CAknMessageQueryDialog* dlg = new (ELeave)CAknMessageQueryDialog();
			dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
			HBufC* title = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TITLE);
			dlg->QueryHeading()->SetTextL(*title);
			CleanupStack::PopAndDestroy(); //title
			HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
			dlg->SetMessageTextL(*msg);
			CleanupStack::PopAndDestroy(); //msg
			dlg->RunLD();
			}
			break;
#ifdef ENABLE_RUBY_VM_STAT			
		case EStat:
			{
			CAknMessageQueryDialog* dlg = new (ELeave)CAknMessageQueryDialog();
			dlg->PrepareLC(R_STAT_QUERY_DIALOG);
			HBufC* title = iEikonEnv->AllocReadResourceLC(R_STAT_DIALOG_TITLE);
			dlg->QueryHeading()->SetTextL(*title);
			CleanupStack::PopAndDestroy(); //title
			char buf[500] = {0};
			sprintf( buf,    "stat:\n___________________\n"
							 "iceq stat:\n "
							 "iseq binread: %u%s\n"
							 "iseq marshal: %u%s\n"
							 "require_compiled: %u%s\n"
							 "httpd thread loaded: %d\n"
							 "sync thread loaded: %d\n",
							 g_iseq_binread_msec, "msec",
							 g_iseq_marshal_load_msec, "msec",
							 g_require_compiled_msec, "msec",
							 g_httpd_thread_loaded,
							 g_sync_thread_loaded);
			
			TPtrC8 ptr8((TUint8*)buf);
			HBufC *msg = HBufC::NewLC(ptr8.Length());
			msg->Des().Copy(ptr8);
			dlg->SetMessageTextL(*msg);
			CleanupStack::PopAndDestroy(msg);
			dlg->RunLD();
			}	
			break;
#endif			
		default:
			iAppView->HandleCommandL(aCommand);
			break;
		}
	}