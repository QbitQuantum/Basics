void ObjectBarDialog::OnRClickObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION Pos = objects.GetFirstSelectedItemPosition();
	int Item = objects.GetNextSelectedItem(Pos);

	// Check if we're right clicking a blank space
	if (Item == -1)
	{
		POINT MousePosition;
		GetCursorPos(&MousePosition);

		CExtPopupMenuWnd * popup = new CExtPopupMenuWnd;

		//object filter
		CExtPopupMenuWnd * objfilterlist = new CExtPopupMenuWnd;
		for (int i=0 ; i < application->object_folders.size(); i++)
		{
			int sel = (i==folderfilter)?3:0;
			if (folderfilter==-1 && application->object_folders[i].name == "Default")
				sel = 3;
			objfilterlist->ItemInsertCommand(100+i, -1, application->object_folders[i].name, NULL, NULL, false, sel);
		}

		popup->LoadMenu(m_hWnd, IDR_BLANK, true, false);
		popup->ItemRemove(0);

		UINT item = 0;

		if (parent.m_tabs.SelectionGet() == 0 && parent.m_tabs.ItemGetCount() == 2)
		{
			popup->ItemInsertCommand(1, -1, "Insert an object", NULL, NULL);
			popup->ItemInsert();
		}

		if (view == ob_large_icons)
		{
			popup->ItemInsertCommand(2, -1, "Show large icons", NULL, NULL, false, 3);
			popup->ItemInsertCommand(3, -1, "Show small icons", NULL, NULL, false, 0);
			popup->ItemInsertCommand(4, -1, "Show small icons (horizontal)", NULL, NULL, false, 0);
			//popup->ItemInsertCommand(5, -1, "Show object tree", NULL, NULL, false, 0);
		}

		else if (view == ob_small_icons)
		{
			popup->ItemInsertCommand(2, -1, "Show large icons", NULL, NULL, false, 0);
			popup->ItemInsertCommand(3, -1, "Show small icons", NULL, NULL, false, 3);
			popup->ItemInsertCommand(4, -1, "Show small icons (horizontal)", NULL, NULL, false, 0);
			//popup->ItemInsertCommand(5, -1, "Show object tree", NULL, NULL, false, 0);
		}

		else if (view == ob_small_icons_horizontal)
		{
			popup->ItemInsertCommand(2, -1, "Show large icons", NULL, NULL, false, 0);
			popup->ItemInsertCommand(3, -1, "Show small icons", NULL, NULL, false, 0);
			popup->ItemInsertCommand(4, -1, "Show small icons (horizontal)", NULL, NULL, false, 3);
			//popup->ItemInsertCommand(5, -1, "Show object tree", NULL, NULL, false, 0);
		}

		else
		{
			popup->ItemInsertCommand(2, -1, "Show large icons", NULL, NULL, false, 0);
			popup->ItemInsertCommand(3, -1, "Show small icons", NULL, NULL, false, 0);
			popup->ItemInsertCommand(4, -1, "Show small icons (horizontal)", NULL, NULL, false, 0);
		//	popup->ItemInsertCommand(5, -1, "Show object tree", NULL, NULL, false, 3);
		}

		popup->ItemInsert();

		if (sorting == ob_sort_az)
		{
			popup->ItemInsertCommand(6, -1, "Sort A-Z", NULL, NULL, false, 3);
			popup->ItemInsertCommand(7, -1, "Sort Z-A", NULL, NULL, false, 0);
			popup->ItemInsertCommand(8, -1, "Sort by Z-Order", NULL, NULL, false, 0);
		}

		else if (sorting == ob_sort_za)
		{
			popup->ItemInsertCommand(6, -1, "Sort A-Z", NULL, NULL, false, 0);
			popup->ItemInsertCommand(7, -1, "Sort Z-A", NULL, NULL, false, 3);
			popup->ItemInsertCommand(8, -1, "Sort by Z-Order", NULL, NULL, false, 0);
		}

		else
		{
			popup->ItemInsertCommand(6, -1, "Sort A-Z", NULL, NULL, false, 0);
			popup->ItemInsertCommand(7, -1, "Sort Z-A", NULL, NULL, false, 0);
			popup->ItemInsertCommand(8, -1, "Sort by Z-Order", NULL, NULL, false, 3);
		}

		popup->ItemInsert();

		if (show_only_selected_layer)
			popup->ItemInsertCommand(9, -1, "Show only objects on the selected layer", NULL, NULL, false, 1);
		else
			popup->ItemInsertCommand(9, -1, "Show only objects on the selected layer", NULL, NULL, false, 0);

		if (show_nonlayout_objects)
			popup->ItemInsertCommand(10, -1, "Show non-layout objects", NULL, NULL, false, 1);
		else
			popup->ItemInsertCommand(10, -1, "Show non-layout objects", NULL, NULL, false, 0);

		if (folderfilter > -2)
			popup->ItemInsertCommand(99, -1, "Use Folders", NULL, NULL, false, 1);
		else
			popup->ItemInsertCommand(99, -1, "Use Folders", NULL, NULL, false, 0);

		popup->ItemInsertSpecPopup(objfilterlist, -1, "Filter by Object Folder", NULL);

		// show menu
		popup->TrackPopupMenu(TPMX_DO_MESSAGE_LOOP | TPMX_NO_WM_COMMAND | TPMX_NO_CMD_UI, MousePosition.x, MousePosition.y, NULL, NULL, NULL, &item);
			
		if (item == 1)
			parent.layout_editor[0][0]->OnFrameAction(IDFR_INSERT);

		else if (item == 2)
		{
			view = ob_large_icons;
			ListView_SetView(objects.m_hWnd, LV_VIEW_ICON);		
			
			objects.ShowWindow(SW_SHOW);
			object_tree.ShowWindow(SW_HIDE);
		}

		else if (item == 3)
		{
			view = ob_small_icons;
			ListView_SetView(objects.m_hWnd, LV_VIEW_DETAILS);		
			
			objects.ShowWindow(SW_SHOW);
			object_tree.ShowWindow(SW_HIDE);
		}

		else if (item == 4)
		{
			view = ob_small_icons_horizontal;
			ListView_SetView(objects.m_hWnd, LV_VIEW_LIST);		

			objects.ShowWindow(SW_SHOW);
			object_tree.ShowWindow(SW_HIDE);
		}

		else if (item == 5)
		{
			view = ob_object_tree;
			
			objects.ShowWindow(SW_HIDE);
			object_tree.ShowWindow(SW_SHOW);
		}

		else if (item == 6)
		{
			sorting = ob_sort_az;
			Refresh();
		}

		else if (item == 7)
		{
			sorting = ob_sort_za;
			Refresh();
		}

		else if (item == 8)
		{
			sorting = ob_sort_zorder;
			Refresh();
		}

		else if (item == 9)
		{
			show_only_selected_layer = !show_only_selected_layer;
			Refresh();
		}

		else if (item == 10)
		{
			show_nonlayout_objects = !show_nonlayout_objects;
			Refresh();
		}

		else if (item == 99)
		{
			if(folderfilter == -2)
				folderfilter=-1;
			else
				folderfilter=-2;
			g_MainFrame->m_INI.WriteInt("General", "ObjectFolder", folderfilter);
			Refresh();
		}
		else if (item >= 100)
		{
			folderfilter=item-100;
			if(application->object_folders[folderfilter].name=="Default")
				folderfilter=-1;
			g_MainFrame->m_INI.WriteInt("General", "ObjectFolder", -1);
			Refresh();
		}
	}

	else
	{
		if (parent.m_tabs.SelectionGet() == 0 && parent.m_tabs.ItemGetCount() == 2)
		{
			parent.layout_editor[0][0]->m_sel.RemoveAll();

			CObjType* pType;
			long ID = objects.GetItemData(Item);

			if (ID == -1)
				return; //folder

			application->object_types.Lookup(ID, pType);

			CLayout* pLayout = parent.layout_editor[0][0]->layout;

			// Iterate each instance
			POSITION instancePos = pLayout->objects.GetStartPosition();
			long unused = 0;

			while (instancePos)
			{
				CObj* pObj;
				pLayout->objects.GetNextAssoc(instancePos, unused, pObj);

				// Add 
				if (pObj->editObject->ObjectIdentifier == pType->ObjectIdentifier)
					parent.layout_editor[0][0]->m_sel.AddTail(unused);
			}

			parent.layout_editor[0][0]->OnRButtonUp(0, CPoint(0,0));
		}
	}
}