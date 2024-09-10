void BaseExposeControl::PopupErrorMessage()
{
	if(exposeTransform) //should exist if not and this message is popping up then we're scewed.
	{
		INode *expNode = exposeTransform->GetExposeNode();
		INode *node = exposeTransform->GetMyNode();
		if(expNode&&node)
		{
			TSTR msg; msg.printf(GetString(IDS_ILLEGAL_SELF_REFERENCE),expNode->GetName(),node->GetName(),node->GetName()); 
			if (GetCOREInterface()->GetQuietMode()) 
			{
				 GetCOREInterface()->Log()->LogEntry(SYSLOG_WARN,NO_DIALOG,GetString(IDS_ILLEGAL_CYCLE),msg);
			}	
			else
			{
				// beep or no??MessageBeep(MB_ICONEXCLAMATION); 
				MessageBox(GetCOREInterface()->GetMAXHWnd(),msg,GetString(IDS_ILLEGAL_CYCLE), 
				MB_ICONEXCLAMATION | MB_APPLMODAL | MB_OK);
			}

		}
		//suspend the hold
		BOOL resume =FALSE;
		if(theHold.Holding())
		{
			theHold.Suspend();
			resume =TRUE;
		}
		exposeTransform->SetExposeNode(NULL);
		if(resume)
			theHold.Resume();
	}
}