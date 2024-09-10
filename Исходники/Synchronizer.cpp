void Synchronizer::_unregisterWndClass() // Win32-only
{
 	UT_DEBUGMSG(("Synchronizer::_unregisterWndClass()\n"));
 	UT_return_if_fail(sm_iClass);
 	
 	if (sm_iMessageWindows > 0)
  	{
 		UT_DEBUGMSG(("%d message windows still exist, skipping unregistering\n", sm_iMessageWindows));
 		return;
  	}
 	
 	AbiCollabSessionManager * pManager = AbiCollabSessionManager::getManager();
 	UT_return_if_fail(pManager);
 
 	HINSTANCE hInstance = pManager->getInstance();
 	UT_return_if_fail(hInstance);
 
 	UT_DEBUGMSG(("Unregistrating message window class\n"));
 	UT_return_if_fail(UnregisterClass(SYNC_CLASSNAME, hInstance));
 	sm_iClass = 0;
}