/**
  Handle the window events.\n
  Create a window server session and connect the client\n
  Set the event type and call the SendEventToWindowGroup().\n
  Close the session on completion \n
*/
void CDefocusingEdwinUi::SendEventToWindowGroups(TWsEvent&	aEvent)
	{
	RWsSession	ws;
	TInt theRes = ws.Connect();
	TEST(theRes == KErrNone);

	RWindowGroup& winGroup = iCoeEnv->RootWin();
	TInt theId = winGroup.Identifier();
	
	aEvent.SetType(EEventKeyDown);
	aEvent.SetTimeNow();
	ws.SendEventToWindowGroup(theId, aEvent);
		
	aEvent.SetType(EEventKey);
	aEvent.SetTimeNow();
	ws.SendEventToWindowGroup(theId, aEvent);

	aEvent.SetType(EEventKeyUp);
	aEvent.SetTimeNow();
	ws.SendEventToWindowGroup(theId, aEvent);
	
	ws.Close();
	}