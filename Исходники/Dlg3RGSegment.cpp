/*
	This function update the window layout, the order of statement is significant.
//*/
void CDlg3RGSegment::UpdateLayout( int cx, int cy )
{
	// Compute layout for the window and the image displaying region
	CStatic*	ctrlStatic = NULL;
	CButton*	ctrlButton = NULL;
	CComboBox*	ctrlCombobox = NULL;
	CRect clientRect;
	CRect contrlRect;
	CRect infoRect;
	GetClientRect(&clientRect);

	//////////////////////////////////////////////////////////////////////////
	// Compute the preprocessing group
	contrlRect.left = clientRect.left + SV_3DRG_SPACING;
	contrlRect.bottom = clientRect.bottom - SV_3DRG_SPACING;
	contrlRect.top = clientRect.bottom - SV_3DRG_GRP_HEIGHT;
	contrlRect.right = contrlRect.left + SV_3DRG_GRP_WIDTH;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_3DRG_GRAYGRP);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	// Preprocessing check box
	contrlRect.left += SV_3DRG_SPACING;
	contrlRect.top += SV_3DRG_SPACING * 2;
	contrlRect.right -= SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	m_chkPreproc.MoveWindow(&contrlRect, FALSE);

	// Brightness label
	contrlRect.top = contrlRect.bottom + SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_LBL_BRIGHT);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);


	//Brightness slider
	contrlRect.top = contrlRect.bottom + SV_3DRG_SMALL_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_SMALLSLIDERHEIGHT;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH;
	ctrlStatic =(CStatic*)GetDlgItem(IDC_BR_100);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_SMALLSLIDERWIDTH;
	m_sldBright.MoveWindow(&contrlRect, FALSE);

	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH;
	ctrlStatic =(CStatic*)GetDlgItem(IDC_BR_M100);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	// Contrast label
	contrlRect.top = contrlRect.bottom + SV_3DRG_SPACING;	
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	contrlRect.left = clientRect.left + SV_3DRG_SPACING *2;
	contrlRect.right = clientRect.left + SV_3DRG_SMALLSLIDERWIDTH;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_LBL_CONTRAST);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	// Contrast slider
	contrlRect.top = contrlRect.bottom + SV_3DRG_SMALL_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_SMALLSLIDERHEIGHT;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_CS_100);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_SMALLSLIDERWIDTH;
	m_sldContrast.MoveWindow(&contrlRect, FALSE);

	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH;
	ctrlStatic =(CStatic*)GetDlgItem(IDC_CS_M100);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	//////////////////////////////////////////////////////////////////////////
	// Compute the region growing setting
	contrlRect.left = clientRect.left + SV_3DRG_SPACING*1.5 + SV_3DRG_GRP_WIDTH;
	contrlRect.bottom = clientRect.bottom - SV_3DRG_SPACING;
	contrlRect.top = clientRect.bottom - SV_3DRG_GRP_HEIGHT;
	contrlRect.right = contrlRect.left + SV_3DRG_GRP_WIDTH;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_3DRG_SETTINGGRP);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	// Use default check box
	contrlRect.left += SV_3DRG_SPACING;
	contrlRect.top += SV_3DRG_SPACING * 2;
	contrlRect.right -= SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	m_chkDefaultThres.MoveWindow(&contrlRect, FALSE);

	// Threshold slider label
	contrlRect.top = contrlRect.bottom + SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_LBL_THRES);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	// Threshold  slider
	contrlRect.top = contrlRect.bottom + SV_3DRG_SMALL_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_SMALLSLIDERHEIGHT;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH*2;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_TH_MIN);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	// Slider threshold
	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_SMALLSLIDERWIDTH - 2*SV_3DRG_CHARWIDTH;
	m_sldThreshold.MoveWindow(&contrlRect, FALSE);
	m_rThres = contrlRect;

	// Label current threshold value
	m_sldThreshold.GetThumbRect(&infoRect);
	infoRect += contrlRect.TopLeft();
	infoRect.top += SV_3DRG_SMALLSLIDERHEIGHT; 
	infoRect.bottom += SV_3DRG_SMALLSLIDERHEIGHT; 
	infoRect.right += SV_3DRG_CHARWIDTH *3;
	ctrlStatic =(CStatic*)GetDlgItem(IDC_TH_CUR);
	ctrlStatic->MoveWindow(&infoRect, FALSE);	
	CString str;
	str.Format(_T("%d"), m_sldThreshold.GetPos());
	ctrlStatic->SetWindowText(str);

	// Label max threshold
	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH *2;
	ctrlStatic =(CStatic*)GetDlgItem(IDC_TH_MAX);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);	

	// Label start slice
	contrlRect = m_rThres;
	contrlRect.left -= (SV_3DRG_CHARWIDTH*2 + SV_3DRG_SMALL_SPACING);
	contrlRect.top += (1.5*SV_3DRG_SMALLSLIDERHEIGHT + SV_3DRG_SPACING);
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH*3;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	ctrlStatic = (CStatic*) GetDlgItem(IDC_3DRG_LBLSTART);
	ctrlStatic->MoveWindow(contrlRect);

	// Textbox start slice
	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_TEXTBOXWIDTH;
	CEdit* ctrlEdit = (CEdit*) GetDlgItem(IDC_3DRG_STARSLICE);
	ctrlEdit->MoveWindow(contrlRect);

	// Label end slice
	contrlRect.left = contrlRect.right + SV_3DRG_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH * 3;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_3DRG_LBLEND);
	ctrlStatic->MoveWindow(contrlRect);

	// textbox end slice
	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_TEXTBOXWIDTH;
	ctrlEdit = (CEdit*) GetDlgItem(IDC_3DRG_ENDSLICE);
	ctrlEdit->MoveWindow(contrlRect);
	

	// Boundary threshold label
	contrlRect.left = m_rThres.left - (SV_3DRG_CHARWIDTH*2 + SV_3DRG_SMALL_SPACING);
	contrlRect.top = contrlRect.bottom + SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH*9;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_3DRG_BTHRES);
	ctrlStatic->MoveWindow(contrlRect);

	//
	// Threshold  slider
	contrlRect.top = contrlRect.bottom + SV_3DRG_SMALL_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_SMALLSLIDERHEIGHT;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH*2;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_TH_MINBTHRES);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);
	
	// Slider boundary threshold
	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_SMALLSLIDERWIDTH - 2*SV_3DRG_CHARWIDTH;
 	m_sldBoundThres.MoveWindow(&contrlRect, FALSE);
 	m_rBthres = contrlRect;


	// Label current boundary threshold value
	m_sldBoundThres.GetThumbRect(&infoRect);
	infoRect += contrlRect.TopLeft();
	infoRect.top += SV_3DRG_SMALLSLIDERHEIGHT; 
	infoRect.bottom += SV_3DRG_SMALLSLIDERHEIGHT; 
	infoRect.right += SV_3DRG_CHARWIDTH *3;
	ctrlStatic =(CStatic*)GetDlgItem(IDC_LBL_CURBTHRE);
	ctrlStatic->MoveWindow(&infoRect, FALSE);	
	str.Format(_T("%d"), m_sldBoundThres.GetPos());
	ctrlStatic->SetWindowText(str);
	
	
	// Label max threshold
	contrlRect.left = contrlRect.right + SV_3DRG_SMALL_SPACING;
	contrlRect.right = contrlRect.left + SV_3DRG_CHARWIDTH *2;
	ctrlStatic =(CStatic*)GetDlgItem(IDC_TH_MAXBTHRES);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);	


	//////////////////////////////////////////////////////////////////////////
	// Compute the Operation mode
	contrlRect.left = clientRect.left + SV_3DRG_SPACING*2 + SV_3DRG_GRP_WIDTH *2;
	contrlRect.bottom = clientRect.bottom - SV_3DRG_SPACING;
	contrlRect.top = clientRect.bottom - SV_3DRG_GRP_HEIGHT;
	contrlRect.right = contrlRect.left + SV_3DRG_GRP_WIDTH;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_3DRG_OPPGRP);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	// Cutting mode radio
	contrlRect.left += SV_3DRG_SPACING;
	contrlRect.top += SV_3DRG_SPACING * 2;
	contrlRect.right -= SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	ctrlButton = (CButton*)GetDlgItem(IDC_3DRG_RAD_CUT);
	ctrlButton->MoveWindow(&contrlRect, FALSE);

	// Segmentation mode radio
	contrlRect.top = contrlRect.bottom + SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	ctrlButton = (CButton*)GetDlgItem(IDC_3DRG_RAD_SEG);
	ctrlButton->MoveWindow(&contrlRect, FALSE);

	// Cutting method combobox label
	contrlRect.top = contrlRect.bottom + SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	ctrlStatic = (CStatic*)GetDlgItem(IDC_3DRG_LBL_CUTMED);
	ctrlStatic->MoveWindow(&contrlRect, FALSE);

	// Cutting method combobox
	contrlRect.top = contrlRect.bottom + SV_3DRG_SPACING/2;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	ctrlCombobox = (CComboBox*)GetDlgItem(IDC_3DRG_CB_CUTMODE);
	ctrlCombobox->MoveWindow(&contrlRect, FALSE);

	// Boundary detection check box
	contrlRect.top = contrlRect.bottom + SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_TEXTHEIGHT;
	ctrlButton = (CButton*) GetDlgItem(IDC_3DRG_CHK_BOUND);
	ctrlButton->MoveWindow(&contrlRect, FALSE);

	// Segment start button
	contrlRect.top = contrlRect.bottom + SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_BUTTON_HEIGHT;
	ctrlButton = (CButton*)GetDlgItem(IDC_3DRG_START);
	ctrlButton->MoveWindow(&contrlRect, FALSE);

	//////////////////////////////////////////////////////////////////////////
	// Compute the button set
	// Close button
	contrlRect.right = clientRect.right - SV_3DRG_SPACING;
	contrlRect.left = contrlRect.right - SV_3DRG_BUTTON_WIDTH;
	contrlRect.bottom = clientRect.bottom - SV_3DRG_SPACING;
	contrlRect.top = contrlRect.bottom - SV_3DRG_BUTTON_HEIGHT;
	ctrlButton = (CButton*)GetDlgItem(IDCANCEL);
	ctrlButton->MoveWindow(&contrlRect, FALSE);

	// Save volume button
	contrlRect.bottom = contrlRect.top - SV_3DRG_SPACING*2;
	contrlRect.top = contrlRect.bottom - SV_3DRG_BUTTON_HEIGHT;
	ctrlButton = (CButton*)GetDlgItem(IDC_3DRG_CMD_SAVEVOL);
	ctrlButton->MoveWindow(&contrlRect, FALSE);

	// Save all slice button
	contrlRect.bottom = contrlRect.top - SV_3DRG_SPACING/2;
	contrlRect.top = contrlRect.bottom - SV_3DRG_BUTTON_HEIGHT;
	ctrlButton = (CButton*)GetDlgItem(IDC_3DRG_CMD_SAVEALL);
	ctrlButton->MoveWindow(&contrlRect, FALSE);

	// Save a slice button
	contrlRect.bottom = contrlRect.top - SV_3DRG_SPACING/2;
	contrlRect.top = contrlRect.bottom - SV_3DRG_BUTTON_HEIGHT;
	ctrlButton = (CButton*)GetDlgItem(IDC_3DRG_CMD_SAVESINGLE);
	ctrlButton->MoveWindow(&contrlRect, FALSE);

	//Compute the image output size
	int nHeight = clientRect.Height() - (5*SV_3DRG_SPACING + SV_3DRG_GRP_HEIGHT + SV_3DRG_LARGESLIDERHEIGHT);
	int nWidth = (clientRect.Width() - 3*SV_3DRG_SPACING) /2;
	int nSize = min(nHeight, nWidth);

	m_OrgRegion.left = clientRect.left + SV_3DRG_SPACING;
	m_OrgRegion.top = clientRect.top + SV_3DRG_SPACING;
	m_OrgRegion.right = m_OrgRegion.left + nSize;
	m_OrgRegion.bottom = m_OrgRegion.top + nSize;
	m_ResRegion = m_OrgRegion;
	m_ResRegion.OffsetRect(nSize + SV_3DRG_SPACING, 0);

	ctrlStatic = (CStatic*)GetDlgItem(IDC_3DRG_ORGFRAME);
	ctrlStatic->MoveWindow(&m_OrgRegion, FALSE);
	ctrlStatic = (CStatic*)GetDlgItem(IDC_3DRG_RESFRAME);
	ctrlStatic->MoveWindow(&m_ResRegion, FALSE);

	contrlRect.left = m_OrgRegion.left;
	contrlRect.right = m_ResRegion.right;
	contrlRect.top = m_OrgRegion.bottom + SV_3DRG_SPACING;
	contrlRect.bottom = contrlRect.top + SV_3DRG_LARGESLIDERHEIGHT;
	m_sldSliceNo.MoveWindow(&contrlRect, FALSE);
	m_OrgRegion.InflateRect(-3,-3);
	m_ResRegion.InflateRect(-3,-3);

	// Update frame for the cutting object
	m_oCutter.SetFrame(m_OrgRegion);
}