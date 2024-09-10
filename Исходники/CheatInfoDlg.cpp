INT_PTR ACheatInfoDlg::OnMouseMove(int key,int x,int y)
{
	if(m_bDragging){
		POINT pt = {x,y};
		::ClientToScreen(this->GetHwnd(),&pt);
		::ScreenToClient(m_CheatsList->GetHwnd(),&pt);

		LVHITTESTINFO lvht = {0};
		int iItem=-1;
		lvht.pt = pt;
		ImageList_DragMove(pt.x,pt.y);
		if((iItem = m_CheatsList->HitTest(&lvht))!=-1 && lvht.flags&LVHT_ONITEM){
			//m_CheatsList->SendMessage(LVM_SETHOTITEM,iItem);
			m_CheatsList->SetItemState(iItem,LVIS_SELECTED,LVIS_SELECTED);
		}else{
			m_CheatsList->SetItemState(-1,0,LVIS_SELECTED);

		}
		return SetDlgResult(0);
	}
	return 0;
}