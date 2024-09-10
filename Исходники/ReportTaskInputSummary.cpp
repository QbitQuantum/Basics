void ReportTaskInputSummary::UpdateDynamicSummary(void)
{
	int NumForces;
	CFrameWnd* pFrame = GetParentFrame();
	
	CWnd			*mainWnd = (CWnd*)this;

	if (2 >= (NumForces = CountExternalForces() + 2)) {
		GetDlgItem(IDD_OutlineJointLoads)->ShowWindow(SW_HIDE);
		GetDlgItem(IDD_ReportTaskInputSummaryJointLoads)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_JTNAMES)->ShowWindow(SW_HIDE);
		
		WINDOWPLACEMENT lpwndpl;

		mainWnd->GetWindowPlacement(&lpwndpl);
		//lpwndpl.rcNormalPosition.bottom += lpwndpl.rcNormalPosition.bottom - hack_WindowBottom;
		//mainWnd->SetWindowPlacement(&lpwndpl);
		MoveWindow( 0,0,lpwndpl.rcNormalPosition.right, hack_WindowBottom, TRUE );
//		ResizeParentToFit(FALSE);
		//pFrame->SetWindowPos(NULL, 0, 0, lpwndpl.rcNormalPosition.right + 20, hack_WindowBottom,
		pFrame->SetWindowPos(NULL, 0, 0, lpwndpl.rcNormalPosition.right + 16, hack_WindowBottom,
		SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);

		m_JointLoads.Empty();
		m_JointNames.Empty();
		CWnd			*Footer;
		WINDOWPLACEMENT		FooterLoc;
		Footer = GetDlgItem(IDC_Footer);
		Footer->GetWindowPlacement( &FooterLoc );
		FooterLoc.rcNormalPosition.top		= hack_FooterTop + 13;
		FooterLoc.rcNormalPosition.bottom	= hack_FooterTop + 28+15;
		Footer->SetWindowPlacement(&FooterLoc);
				
	}
	else {
		// /*
		CWnd			*Footer, *Joints, *Names, *Outline;
		WINDOWPLACEMENT		FooterLoc, JointsLoc, OutlineLoc, NamesLoc;
		
		// Show the box for the other joints
		GetDlgItem(IDD_OutlineJointLoads)->ShowWindow(SW_SHOW);
		GetDlgItem(IDD_ReportTaskInputSummaryJointLoads)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_JTNAMES)->ShowWindow(SW_SHOW);
		
		// Move the footer down 50 units
		Footer = GetDlgItem(IDC_Footer);
		Footer->GetWindowPlacement( &FooterLoc );
		
		Outline = GetDlgItem(IDD_OutlineJointLoads);
		Outline->GetWindowPlacement( &OutlineLoc );
		
		Joints = GetDlgItem(IDD_ReportTaskInputSummaryJointLoads);
		Joints->GetWindowPlacement( &JointsLoc );
		
		Names = GetDlgItem(IDC_JTNAMES);
		Names->GetWindowPlacement( &NamesLoc );
		
		OutlineLoc.rcNormalPosition.top		= hack_FooterTop + 5;
		OutlineLoc.rcNormalPosition.left	= FooterLoc.rcNormalPosition.left;
		OutlineLoc.rcNormalPosition.right	= FooterLoc.rcNormalPosition.right;
		
		NamesLoc.rcNormalPosition.top		= OutlineLoc.rcNormalPosition.top + 15;
		NamesLoc.rcNormalPosition.left		= OutlineLoc.rcNormalPosition.left + 10;
		NamesLoc.rcNormalPosition.right		= OutlineLoc.rcNormalPosition.left + 105;
		NamesLoc.rcNormalPosition.bottom	= NamesLoc.rcNormalPosition.top + (NumForces * TextHeight) + 15;
		
		JointsLoc.rcNormalPosition.top		= OutlineLoc.rcNormalPosition.top + 15;
		JointsLoc.rcNormalPosition.left		= NamesLoc.rcNormalPosition.right + 5;
		JointsLoc.rcNormalPosition.right	= OutlineLoc.rcNormalPosition.right - 10;
		JointsLoc.rcNormalPosition.bottom	= JointsLoc.rcNormalPosition.top + (NumForces * TextHeight) + 15;
		
		OutlineLoc.rcNormalPosition.bottom	= JointsLoc.rcNormalPosition.bottom + 2.5;
		
		
		Joints->SetWindowPlacement(&JointsLoc);
		Outline->SetWindowPlacement(&OutlineLoc);
		Names->SetWindowPlacement(&NamesLoc);
		
		FooterLoc.rcNormalPosition.top		= OutlineLoc.rcNormalPosition.bottom + 13;
		FooterLoc.rcNormalPosition.bottom	= OutlineLoc.rcNormalPosition.bottom + 28+15;
		Footer->SetWindowPlacement(&FooterLoc);
		
		WINDOWPLACEMENT lpwndpl;
		mainWnd->GetWindowPlacement(&lpwndpl);
//		lpwndpl.rcNormalPosition.bottom = hack_WindowBottom - NumForces * TextHeight - 25;
//		mainWnd->SetWindowPlacement(&lpwndpl);
		MoveWindow( 0,0,lpwndpl.rcNormalPosition.right, hack_WindowBottom + NumForces * TextHeight + 25, TRUE );
//		ResizeParentToFit(FALSE);
		pFrame->SetWindowPos(NULL, 0, 0, lpwndpl.rcNormalPosition.right + 16, hack_WindowBottom + NumForces * TextHeight + 25,
		SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
//		this->OnSize(0, lpwndpl.rcNormalPosition.right, hack_WindowBottom + NumForces * TextHeight + 25);

		DisplayExtForces(&m_JointLoads);
		DisplayExtForceNames(&m_JointNames);
		
	}
}