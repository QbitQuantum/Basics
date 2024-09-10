void CShowPageDlg::OnLbnSelchangeListPage()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_OwnerListBox.GetCurSel();
	if(index==CB_ERR)return;
	map<int,UINT>::const_iterator itera = m_map_index.find(index);
	if(itera!=m_map_index.end())
	{
		list<CTrackContrl*>::const_iterator trakItera = theApp.m_pView->m_list_trackCtrl.begin();
		for(trakItera;trakItera!=theApp.m_pView->m_list_trackCtrl.end();trakItera++)
		{
			CTrackContrl* ptrackCtr = *trakItera;
			if(ptrackCtr->GetSerialID()==itera->second && ptrackCtr->GetSerialID()==0)
			{
				CButton* pDelButton = (CButton*)GetDlgItem(IDC_BN_DELPAGE);
				pDelButton->EnableWindow(FALSE);
// 				if(theApp.m_pView->m_pTrackCtrl!=NULL)
// 					theApp.m_pView->m_pTrackCtrl->SetAllCtrlHide();//原来的隐藏
// 				theApp.m_pView->m_pTrackCtrl = ptrackCtr;
// 				theApp.m_pView->m_pTrackCtrl->SetAllCtrlShow();
				theApp.m_pView->ShowPage(ptrackCtr->GetSerialID());
//				theApp.m_pView->Invalidate(TRUE);
				break;
			}
			else if(ptrackCtr->GetSerialID()==itera->second && ptrackCtr->GetSerialID()!=0)
			{
				theApp.m_pView->ShowPage(ptrackCtr->GetSerialID());
				CButton* pDelButton = (CButton*)GetDlgItem(IDC_BN_DELPAGE);
				pDelButton->EnableWindow(TRUE);
// 				if(theApp.m_pView->m_pTrackCtrl!=NULL)
// 					theApp.m_pView->m_pTrackCtrl->SetAllCtrlHide();//原来的隐藏
// 				theApp.m_pView->m_pTrackCtrl = ptrackCtr;
// 				theApp.m_pView->m_pTrackCtrl->SetAllCtrlShow();
// 				theApp.m_pView->Invalidate(TRUE);
				break;
			}
			/*
			if(ptrackCtr->GetSerialID()==0)//主页面不能删除
			{
				CButton* pDelButton = (CButton*)GetDlgItem(IDC_BN_DELPAGE);
				pDelButton->EnableWindow(FALSE);
			}
			else
			{
				CButton* pDelButton = (CButton*)GetDlgItem(IDC_BN_DELPAGE);
				pDelButton->EnableWindow(TRUE);
			}
			if(ptrackCtr->GetSerialID()==itera->second)
			{
				theApp.m_pView->m_pTrackCtrl->SetAllCtrlHide();//原来的隐藏
				theApp.m_pView->m_pTrackCtrl = ptrackCtr;
				theApp.m_pView->m_pTrackCtrl->SetAllCtrlShow();
				theApp.m_pView->Invalidate(TRUE);
				break;
			}
			*/
		}
	}
}