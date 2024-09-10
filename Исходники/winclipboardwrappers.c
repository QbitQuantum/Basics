int
winProcSetSelectionOwner (ClientPtr client)
{
  int			i;
  DrawablePtr		pDrawable;
  WindowPtr		pWindow = None;
  Bool			fOwnedToNotOwned = FALSE;
  static Window		s_iOwners[CLIP_NUM_SELECTIONS] = {None};
  static unsigned long	s_ulServerGeneration = 0;
  REQUEST(xSetSelectionOwnerReq);
  
  REQUEST_SIZE_MATCH(xSetSelectionOwnerReq);

#if 0
  ErrorF ("winProcSetSelectionOwner - Hello.\n");
#endif

  /* Watch for server reset */
  if (s_ulServerGeneration != serverGeneration)
    {
      /* Save new generation number */
      s_ulServerGeneration = serverGeneration;

      /* Initialize static variables */
      for (i = 0; i < CLIP_NUM_SELECTIONS; ++i)
	s_iOwners[i] = None;
    }

  /* Abort if clipboard not completely initialized yet */
  if (!g_fClipboardStarted)
    {
      ErrorF ("winProcSetSelectionOwner - Clipboard not yet started, "
	      "aborting.\n");
      goto winProcSetSelectionOwner_Done;
    }
  
  /* Grab window if we have one */
  if (None != stuff->window)
    {
      /* Grab the Window from the request */
      int rc = dixLookupWindow(&pWindow, stuff->window, client, DixReadAccess);
      if (rc != Success) {
	  ErrorF ("winProcSetSelectionOwner - Found BadWindow, aborting.\n");
	  goto winProcSetSelectionOwner_Done;
      }
    }

  /* Now we either have a valid window or None */

  /* Save selection owners for monitored selections, ignore other selections */
  if (XA_PRIMARY == stuff->selection)
    {
      /* Look for owned -> not owned transition */
      if (None == stuff->window
	  && None != s_iOwners[CLIP_OWN_PRIMARY])
	{
	  fOwnedToNotOwned = TRUE;

#if 0
	  ErrorF ("winProcSetSelectionOwner - PRIMARY - Going from "
		  "owned to not owned.\n");
#endif

	  /* Adjust last owned selection */
	  if (None != s_iOwners[CLIP_OWN_CLIPBOARD])
	    g_atomLastOwnedSelection = MakeAtom ("CLIPBOARD", 9, TRUE);
	  else
	    g_atomLastOwnedSelection = None;
	}
      
      /* Save new selection owner or None */
      s_iOwners[CLIP_OWN_PRIMARY] = stuff->window;

#if 0
      ErrorF ("winProcSetSelectionOwner - PRIMARY - Now owned by: %d\n",
	      stuff->window);
#endif
    }
  else if (MakeAtom ("CLIPBOARD", 9, TRUE) == stuff->selection)
    {
      /* Look for owned -> not owned transition */
      if (None == stuff->window
	  && None != s_iOwners[CLIP_OWN_CLIPBOARD])
	{
	  fOwnedToNotOwned = TRUE;
	  
#if 0
	  ErrorF ("winProcSetSelectionOwner - CLIPBOARD - Going from "
		  "owned to not owned.\n");
#endif

	  /* Adjust last owned selection */
	  if (None != s_iOwners[CLIP_OWN_PRIMARY])
	    g_atomLastOwnedSelection = XA_PRIMARY;
	  else
	    g_atomLastOwnedSelection = None;
	}
      
      /* Save new selection owner or None */
      s_iOwners[CLIP_OWN_CLIPBOARD] = stuff->window;

#if 0
      ErrorF ("winProcSetSelectionOwner - CLIPBOARD - Now owned by: %d\n",
	      stuff->window);
#endif
    }
  else
    goto winProcSetSelectionOwner_Done;

  /*
   * At this point, if one of the selections is still owned by the 
   * clipboard manager then it should be marked as unowned since
   * we will be taking ownership of the Win32 clipboard.
   */
  if (g_iClipboardWindow == s_iOwners[CLIP_OWN_PRIMARY])
    s_iOwners[CLIP_OWN_PRIMARY] = None;
  if (g_iClipboardWindow == s_iOwners[CLIP_OWN_CLIPBOARD])
    s_iOwners[CLIP_OWN_CLIPBOARD] = None;

  /*
   * Handle case when selection is being disowned,
   * WM_DRAWCLIPBOARD did not do the disowning,
   * both monitored selections are no longer owned,
   * an owned to not owned transition was detected,
   * and we currently own the Win32 clipboard.
   */
  if (None == stuff->window
      && g_iClipboardWindow != client->lastDrawableID
      && (None == s_iOwners[CLIP_OWN_PRIMARY]
	  || g_iClipboardWindow == s_iOwners[CLIP_OWN_PRIMARY])
      && (None == s_iOwners[CLIP_OWN_CLIPBOARD]
	  || g_iClipboardWindow == s_iOwners[CLIP_OWN_CLIPBOARD])
      && fOwnedToNotOwned
      && g_hwndClipboard != NULL
      && g_hwndClipboard == GetClipboardOwner ())
    {
#if 0
      ErrorF ("winProcSetSelectionOwner - We currently own the "
	      "clipboard and neither the PRIMARY nor the CLIPBOARD "
	      "selections are owned, releasing ownership of Win32 "
	      "clipboard.\n");
#endif
      
      /* Release ownership of the Windows clipboard */
      OpenClipboard (NULL);
      EmptyClipboard ();
      CloseClipboard ();

      /* Clear X selection ownership (might still be marked as us owning) */
      s_iOwners[CLIP_OWN_PRIMARY] = None;
      s_iOwners[CLIP_OWN_CLIPBOARD] = None;
      
      goto winProcSetSelectionOwner_Done;
    }

  /* Abort if no window at this point */
  if (None == stuff->window)
    {
#if 0
      ErrorF ("winProcSetSelectionOwner - No window, returning.\n");
#endif
      goto winProcSetSelectionOwner_Done;
    }

  /* Abort if invalid selection */
  if (!ValidAtom (stuff->selection))
    {
      ErrorF ("winProcSetSelectionOwner - Found BadAtom, aborting.\n");
      goto winProcSetSelectionOwner_Done;
    }

  /* Cast Window to Drawable */
  pDrawable = (DrawablePtr) pWindow;
  
  /* Abort if clipboard manager is owning the selection */
  if (pDrawable->id == g_iClipboardWindow)
    {
#if 0
      ErrorF ("winProcSetSelectionOwner - We changed ownership, "
	      "aborting.\n");
#endif
      goto winProcSetSelectionOwner_Done;
    }

  /* Abort if root window is taking ownership */
  if (pDrawable->id == 0)
    {
      ErrorF ("winProcSetSelectionOwner - Root window taking ownership, "
	      "aborting\n");
      goto winProcSetSelectionOwner_Done;
    }

  /* Close clipboard if we have it open already */
  if (GetOpenClipboardWindow () == g_hwndClipboard)
    {
      CloseClipboard ();
    }

  /* Access the Windows clipboard */
  if (!OpenClipboard (g_hwndClipboard))
    {
      ErrorF ("winProcSetSelectionOwner - OpenClipboard () failed: %08x\n",
	      (int) GetLastError ());
      goto winProcSetSelectionOwner_Done;
    }

  /* Take ownership of the Windows clipboard */
  if (!EmptyClipboard ())
    {
      ErrorF ("winProcSetSelectionOwner - EmptyClipboard () failed: %08x\n",
	      (int) GetLastError ());
      goto winProcSetSelectionOwner_Done;
    }

  /* Advertise Unicode if we support it */
  if (g_fUnicodeSupport)
    SetClipboardData (CF_UNICODETEXT, NULL);

  /* Always advertise regular text */
  SetClipboardData (CF_TEXT, NULL);

  /* Save handle to last owned selection */
  g_atomLastOwnedSelection = stuff->selection;

  /* Release the clipboard */
  if (!CloseClipboard ())
    {
      ErrorF ("winProcSetSelectionOwner - CloseClipboard () failed: "
	      "%08x\n",
	      (int) GetLastError ());
      goto winProcSetSelectionOwner_Done;
    }

 winProcSetSelectionOwner_Done:
  return (*winProcSetSelectionOwnerOrig) (client);
}