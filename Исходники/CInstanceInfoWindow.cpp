void CInstanceInfoWindow::OnDoubleClickListItem()
{
	int itemIndex = ListBox_GetCurSel(mInstancesListBox);
	if (itemIndex != LB_ERR)
	{
		u32 id = ListBox_GetItemData(mInstancesListBox, itemIndex);
		EditorScene* scene = EditorScene::getInstance();
		EditorWindow* window = EditorWindow::getInstance();

		if (scene->SelectObject(id))
		{
			scene->FocusSelectedObject();
			window->ShowNodeInfo(id);
		}
		SetFocus(mParentHwnd);
	}
}