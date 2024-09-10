CMUSHclientDoc::~CMUSHclientDoc()
{
int i;

  // stop sounds playing, release sound buffers
  for (i = 0; i < MAX_SOUND_BUFFERS; i++)
    if (m_pDirectSoundSecondaryBuffer [i])
      {
      DWORD iStatus;
      if (SUCCEEDED (m_pDirectSoundSecondaryBuffer [i]->GetStatus (&iStatus)) &&
          (iStatus & DSBSTATUS_PLAYING))
        m_pDirectSoundSecondaryBuffer [i]->Stop ();

      m_pDirectSoundSecondaryBuffer [i]->Release ();
      }

  if (m_pTimerWnd)
    {
	  m_pTimerWnd->DestroyWindow();
	  delete m_pTimerWnd;
    m_pTimerWnd = NULL;
    }

  for (i = 0; i < 8; i++)  
    delete m_font [i];
  delete m_input_font;

  if (m_hNameLookup)
    WSACancelAsyncRequest (m_hNameLookup);  // cancel host name lookup in progress

  delete [] m_pGetHostStruct;   // delete buffer used by host name lookup

  delete m_MapFailureRegexp;    // delete regexp structure for mapping failures

	if (m_pSocket)
	{

    ShutDownSocket (*m_pSocket);

    delete m_pSocket;
    m_pSocket = NULL;

    }

	if (m_pChatListenSocket)
	{

    ShutDownSocket (*m_pChatListenSocket);

    delete m_pChatListenSocket;
    m_pChatListenSocket = NULL;

    }

  // UDP listening sockets
  for (map<int, UDPsocket *>::iterator udpSocketIterator = m_UDPsocketMap.begin ();
       udpSocketIterator != m_UDPsocketMap.end ();
       udpSocketIterator++)
      delete udpSocketIterator->second;

  // delete chat sessions

  DELETE_LIST (m_ChatList);

  // delete plugins

  // we have to do it this way, because otherwise if a plugin attempts to access the
  // plugin list (eg. BroadcastPlugin, Trace) during the delete operation, then it
  // may call a plugin that was deleted a moment ago, but is still in the list.

   for (PluginListIterator pit = m_PluginList.begin (); 
        pit != m_PluginList.end ();
        pit =  m_PluginList.erase (pit))    // erase from list and get next one
    delete *pit;  // delete *this* one

  CloseLog ();    // this writes out the log file postamble as well

// delete triggers
       
  DELETE_MAP (m_TriggerMap, CTrigger); 

// delete aliass

  DELETE_MAP (m_AliasMap, CAlias); 

// delete lines list

  DELETE_LIST (m_LineList);

// delete timer map

  DELETE_MAP (m_TimerMap, CTimer); 
  
// delete variables map

  DELETE_MAP (m_VariableMap, CVariable); 

// delete Element map

  DELETE_MAP (m_CustomElementMap, CElement); 

// delete active tags list

  DELETE_LIST (m_ActiveTagList);

// delete actions list

  DELETE_LIST (m_ActionList);


// get rid of our positions array

  delete [] m_pLinePositions;

// one less document

  gdoccount--;

// update activity window

  App.m_bUpdateActivity = TRUE;

// ****************** release scripting stuff

  DisableScripting ();

  if (!bWine)
  	AfxOleUnlockApp();        // not needed?

  // free compression stuff

  if (m_CompressOutput)
    free (m_CompressOutput);
  if (m_CompressInput)
    free (m_CompressInput);

  // don't wrap up if not initialised
  if (m_bCompressInitOK)
    inflateEnd (&m_zCompress);

  // don't need to know what the configuration was any more
  DeleteConfigurationArrays ();

  // delete our arrays
  for (tStringMapOfMaps::iterator it = m_Arrays.begin (); 
       it != m_Arrays.end ();
       it++)
         {
         tStringToStringMap * m = it->second;
         m->clear ();
         delete m;
         }

  // destroy accelerator table, if we had one
  if (m_accelerator)
    DestroyAcceleratorTable (m_accelerator);

  // if they loaded a special font, get rid of it
  RemoveSpecialFonts ();

#ifdef PANE

  // get rid of owned panes

  safe_for_each (m_PaneMap.begin (), m_PaneMap.end (), closepane);
#endif // PANE

  // delete MiniWindow map

  for (MiniWindowMapIterator mwit = m_MiniWindows.begin (); 
       mwit != m_MiniWindows.end ();
       mwit++)
         delete mwit->second;

  m_MiniWindowsOrder.clear ();

  // delete databases
  for (tDatabaseMapIterator dbit = m_Databases.begin (); 
       dbit != m_Databases.end ();
       dbit++)
         {
         if (dbit->second->pStmt)        // finalize any outstanding statement
           sqlite3_finalize(dbit->second->pStmt);
         if (dbit->second->db)           // and close the database
           sqlite3_close(dbit->second->db);
         delete dbit->second;      // now delete memory used by it
         }

}   // end of CMUSHclientDoc::~CMUSHclientDoc