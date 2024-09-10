BOOL CControlsModule::MetaProc(PBMetaStruct *pbMetaStructure, PPBSTRUCT pPBStructure, void *pParam)
{
	INSTANCE_DATA *pdata = (INSTANCE_DATA*) pParam;
	if (!pdata)
	{
		WRITELOG (L"pParam null");
		return FALSE;
	}

	LPCWSTR pparameter = pbMetaStructure->lpParameter;
	LPCWSTR pvalue = pbMetaStructure->lpValue;
	CControlListEntry *plist_entry;

	// Get CControl which we're operating on from the array in the instance data
	// Instantiate as necessary

	CControl *pcontrol = NULL;

	switch (nControlType)
	{
		case CT_QUITBUTTON:
			if (!pdata->pQuitButton)
				pdata->pQuitButton = new CQuitButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pQuitButton;
			break;

		case CT_RELOADBUTTON:
			if (!pdata->pReloadButton)
				pdata->pReloadButton = new CReloadButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pReloadButton;
			break;

		case CT_ADDRESSBAR:
			if (!pdata->pAddressBar)
			{
				pdata->pAddressBar = new CAddressBar (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);

				// If there's a go button then pass the address bar to it
				if (pdata->pGoButton)
					pdata->pGoButton->SetAddressBar(pdata->pAddressBar);
			}
			pcontrol = pdata->pAddressBar;
			break;

		case CT_TOPCOMMANDAREA:
			if (!pdata->pTopCommandArea)
			{
				pdata->pTopCommandArea = new CTopCommandArea (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
				BringControlsToFront (pdata);
			}
			pcontrol = pdata->pTopCommandArea;
			break;

		case CT_BOTTOMCOMMANDAREA:
			if (!pdata->pBottomCommandArea)
			{
				pdata->pBottomCommandArea = new CBottomCommandArea (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
				BringControlsToFront (pdata);
			}
			pcontrol = pdata->pBottomCommandArea;
			break;

		case CT_BACKBUTTON:
			if (!pdata->pBackButton)
				pdata->pBackButton = new CBackButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pBackButton;
			break;

		case CT_FORWARDBUTTON:
			if (!pdata->pForwardButton)
				pdata->pForwardButton = new CForwardButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pForwardButton;
			break;

		case CT_GOBUTTON:
			if (!pdata->pGoButton)
			{
				pdata->pGoButton = new CGoButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);

				// If there's an address bar then pass a pointer to it
				if (pdata->pAddressBar)
					pdata->pGoButton->SetAddressBar (pdata->pAddressBar);

				// If there's a stop button make sure it's under the go button
				if (pdata->pStopButton)
					SetWindowPos (pdata->pStopButton->GetWindow (), pdata->pGoButton->GetWindow (), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
			pcontrol = pdata->pGoButton;
			break;

		case CT_HOMEBUTTON:
			if (!pdata->pHomeButton)
				pdata->pHomeButton = new CHomeButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pHomeButton;
			break;

		case CT_MINIMIZEBUTTON:
			if (!pdata->pMinimizeButton)
				pdata->pMinimizeButton = new CMinimizeButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pMinimizeButton;
			break;

		case CT_PAGEZOOMINBUTTON:
			if (!pdata->pPageZoomInButton)
				pdata->pPageZoomInButton = new CPageZoomInButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pPageZoomInButton;
			break;

		case CT_PAGEZOOMOUTBUTTON:
			if (!pdata->pPageZoomOutButton)
				pdata->pPageZoomOutButton = new CPageZoomOutButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pPageZoomOutButton;
			break;

		case CT_SIPBUTTON:
			if (!pdata->pSIPButton)
				pdata->pSIPButton = new CSIPButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pSIPButton;
			break;

		case CT_STOPBUTTON:
			if (!pdata->pStopButton)
			{
				pdata->pStopButton = new CStopButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);

				// If there's a go button make sure it's on top of the stop button
				if (pdata->pGoButton)
					SetWindowPos (pdata->pStopButton->GetWindow (), pdata->pGoButton->GetWindow (), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
			pcontrol = pdata->pStopButton;
			break;

		case CT_ZOOMTEXTBUTTON:
			if (!pdata->pZoomTextButton)
				pdata->pZoomTextButton = new CZoomTextButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pZoomTextButton;
			break;

		case CT_KEYSTATE:
			if (!pdata->pKeyState)
				pdata->pKeyState = new CKeyState (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pKeyState;
			break;

		case CT_SCROLL:
			if (!pdata->pScroll)
				pdata->pScroll = new CScroll (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pScroll;
			break;

		case CT_BATTERY:
			if (!pdata->pBattery)
				pdata->pBattery = new CBattery (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
			pcontrol = pdata->pBattery;
			break;

		case CT_SIGNAL:
			if (!pdata->pSignal)
			{
				pdata->pSignal = new CSignal (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);

				// Check WLAN available
				if (!pdata->pSignal->OpenWLAN ())
				{
					delete pdata->pSignal;
					pdata->pSignal = NULL;

					WRITELOG (L"WLAN support not available");
					return TRUE;
				}
				
			}
			pcontrol = pdata->pSignal;
			break;

		case CT_CUSTOMBUTTON:
			// Record custom button ID
			if (cmp (pparameter, L"id"))
				WSAFECOPY (pdata->sControlID, pvalue);

			// Find button list entry for most recent ID
			plist_entry = pdata->pCustomButtonList->Find (pdata->sControlID);

			// Use existing control if found
			if (plist_entry)
			{
				pcontrol = plist_entry->pControl;
			}
			else
			{
				// Create new control if not found and add to list
				pcontrol = new CCustomButton (pPBStructure->hInstance, pPBStructure->hWnd, pdata->nID);
				pdata->pCustomButtonList->AddEntry (new CControlListEntry (pcontrol));
			}

			break;
	}

	if (!pcontrol)
	{
		WRITELOG (L"Control type not available: %d", nControlType);
		return FALSE;
	}

	if (cmp (pparameter, L"visibility"))
	{
		if (cmp (pvalue, L"visible"))
			return pcontrol->Show ();
		else if (cmp (pvalue, L"hidden"))
			return pcontrol->Hide ();
		else
		{
			WRITELOG (L"Unknown visibility value: %s", pvalue);
			return FALSE;
		}
	}
	else if (cmp (pparameter, L"id"))
	{
		return pcontrol->SetID (pvalue);
	}
	
	//JMS 5/5/2010
	//add check for null values on numeric parameters
	else if (cmp (pparameter, L"left"))
	{
		if(pvalue == NULL || pvalue[0] == NULL)
			return pcontrol->SetLeft (0);
		else
		{	// JS can pass in integer values as floats -> check if a string is a float and then transform it to int.
			if (isFloat(pvalue)) return pcontrol->SetLeft (_wtoi (pvalue));
			else
			{
				WRITELOG (L"Unknown left value: %s", pvalue);
				return FALSE;
			}
		}
	}
	else if (cmp (pparameter, L"right"))
	{
		if(pvalue == NULL || pvalue[0] == NULL)
			return pcontrol->SetRight (0);
		else
		{
			// JS can pass in integer values as floats -> check if a string is a float and then transform it to int.
			if (isFloat(pvalue)) return pcontrol->SetRight (_wtoi (pvalue));
			else
			{
				WRITELOG (L"Unknown right value: %s", pvalue);
				return FALSE;
			}
		}
	}
	else if (cmp (pparameter, L"top"))
	{
		if(pvalue == NULL || pvalue[0] == NULL)
			return pcontrol->SetTop (0);
		else
		{
			// JS can pass in integer values as floats -> check if a string is a float and then transform it to int.
			if (isFloat(pvalue)) return pcontrol->SetTop (_wtoi (pvalue));
			else
			{
				WRITELOG (L"Unknown top value: %s", pvalue);
				return FALSE;
			}
		}
	}
	else if (cmp (pparameter, L"width"))
	{
		if(pvalue == NULL || pvalue[0] == NULL)
			return pcontrol->SetWidth (0);
		else
		{
			// JS can pass in integer values as floats -> check if a string is a float and then transform it to int.
			if (isFloat(pvalue)) return pcontrol->SetWidth (_wtoi (pvalue));
			else
			{
				WRITELOG (L"Unknown width value: %s", pvalue);
				return FALSE;
			}
		}
	}
	else if (cmp (pparameter, L"height"))
	{
		if(pvalue == NULL || pvalue[0] == NULL)
			return pcontrol->SetHeight (0);
		else
		{
			// JS can pass in integer values as floats -> check if a string is a float and then transform it to int.
			if (isFloat(pvalue)) return pcontrol->SetHeight (_wtoi (pvalue));
			else
			{
				WRITELOG (L"Unknown height value: %s", pvalue);
				return FALSE;
			}
		}
	}
	

	else if (cmp (pparameter, L"image"))
		return pcontrol->SetImage (pvalue);
	else if (cmp (pparameter, L"imageup"))
		return pcontrol->SetImageUp (pvalue);
	else if (cmp (pparameter, L"imagedown"))
		return pcontrol->SetImageDown (pvalue);
	else if (cmp (pparameter, L"color") || cmp (pparameter, L"colour"))
		return pcontrol->SetColour (pvalue);
	else if (cmp (pparameter, L"click"))
		return pcontrol->SetClick (pvalue);
	else if (cmp (pparameter, L"border"))
	{
		if (cmp (pvalue, L"visible"))
			return pcontrol->SetBorder (TRUE);
		else if (cmp (pvalue, L"hidden"))
			return pcontrol->SetBorder (FALSE);
		else
		{
			WRITELOG (L"Unknown border value: %s", pvalue);
			return FALSE;
		}
	}
	else
	{
		// See if the control wants any non-standard parameter not handled above
		if (pcontrol->SetMiscValue (pparameter, pvalue))
			return TRUE;

		WRITELOG (L"Unknown parameter: %s", pparameter);
		return FALSE;
	}

	return TRUE;
}