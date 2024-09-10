OP_STATUS CollectionNavigationPane::DropWindowItem(HotlistModelItem* target, DesktopDragObject* drag_object, DesktopDragObject::InsertType insert_type)
{
	DesktopWindowCollection& model = g_application->GetDesktopWindowCollection();
	for (INT32 i = 0; i < drag_object->GetIDCount(); i++)
	{
		DesktopWindowCollectionItem* item = model.GetItemByID(drag_object->GetID(i));
		if (!item || item->GetType() != WINDOW_TYPE_DOCUMENT || !item->GetDesktopWindow())
			continue;

		OpWindowCommander* document = static_cast<DocumentDesktopWindow*>(item->GetDesktopWindow())->GetWindowCommander();
		BookmarkItemData item_data;
		RETURN_IF_ERROR(item_data.name.Set(document->GetCurrentTitle()));
		RETURN_IF_ERROR(item_data.url.Set(document->GetCurrentURL(FALSE)));
		g_desktop_bookmark_manager->DropItem(item_data, target ? target->GetID() : -1, insert_type, TRUE, drag_object->GetType());
	}

	return OpStatus::OK;
}