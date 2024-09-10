void ImportProcessor::ProcessImportedMeasurements()
{
	try
	{
		//	These are all the events that have data we want to check out
		StartupImpDlg StartUpDlg;
		StartUpDlg.DoIt("Find New Measurements . . .");

		// now, must identify those that are new, mark them
		POSITION pos = pM->GetHeadPosition();
		while( pos != NULL )
		{
			MEvent* p = (MEvent*)pM->GetNext( pos );
			p->Match();  // finds the closest match in time that matches the identity settings
		}

		/* case 1:	marked events match measurement timestamps found in the database
					but do they match the detector, or item id?
		   case 2:	unmarked events do not match on timestamp, may match on facility, mtype (B or (V,C))item id (or not)	

		   put up an editable dialog that shows all of these events with the matching components and unknown or unmatching
		   then for each row, allow these operations
		       fill in missing data for a matching entry (if entry)
			   
			   subclasses of data probably require some subtlety

			   for a new measurement, require a declaration to be entered into the database and what about the measurement plan?

			   The primary step now is to build the UI component and get it to work

			   use the original editable init file id class to get this going

		 */

		// put up import editor dialog that lets each measurement event be identified, then process them.

		bool bNewToProcess = false;
		bool bExistingToUpdate = false;
		bool bBkgToProcess = false;
		pos = pM->GetHeadPosition();
		CFDMSApp* pApp = (CFDMSApp*)AfxGetApp();
		StartUpDlg.SetCount(pM->GetCount());
		StartUpDlg.BumpCount();

		while( pos != NULL )
		{
			MEvent* p = (MEvent*)pM->GetNext( pos );
			if (p->GetMark())
			{
				if (!p->m_bExactMatch[eisMP])
				{
					bExistingToUpdate = true;
					pApp->AppendToLogF("* existing %s", p->Image());
				}
				else
				{
					pApp->AppendToLogF("== exact %s", p->Image());
				}
			}
			else if (p->GetAssayType() == eBackgroundAssay)
			{
				pApp->AppendToLogF("background %s [BKG]", p->Image());
				bBkgToProcess = true;
				StartUpDlg.BumpCount();
				Sleep(150);
			}
			else // 
			{
				pApp->AppendToLogF("new      %s [%d]", p->Image(), p->m_iGIndex[eisMP]);
				bNewToProcess = true;
				StartUpDlg.BumpCount();
				Sleep(150);
			}
		}
		StartUpDlg.DestroyWindow();
		if (!bExistingToUpdate && !bNewToProcess)
		{
			CFDMSApp* pApp = (CFDMSApp*)AfxGetApp();
			CString s, msg;
			s = "Imported Events from Radiation Review";
			msg = "No new or updated measurements were found in the imported events from Radiation Review.";
			pApp->MyMessageBox( msg, MB_OK | MB_ICONEXCLAMATION, (UINT)-1, s);
			bBkgToProcess = false;
		}

		if (bBkgToProcess)
		{
			BkgEventDlg x(true, pM, pB, AfxGetMainWnd());  // display all the bkg events, user operates upon and chooses the events to add to the MP
			x.DoModal();
		}
		if (bNewToProcess)
		{
			NewEventDlg y(true, pM, pB, AfxGetMainWnd());  // display all the new events in a dialog, user operates upon and chooses the events to add to the MP
			y.DoModal();
		}
		if (bExistingToUpdate)
		{
			MatchingEventDlg z(false, pM, pB, AfxGetMainWnd()); // display all the events that had a real match, user operates and chooses said same self serk
			z.DoModal();
		}
		// alternate technique: gather the matching items and the new items from the pM list and do the final storage here
	}
	catch( CMemoryException* theException )
	{
		theException->Delete();
	}
	catch (const _com_error& comerr) 
	{
		handlecomerr(comerr);				
	}
	catch (...)
	{
	}

}