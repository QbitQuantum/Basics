// static
LLPreviewGesture* LLPreviewGesture::show(const std::string& title, const LLUUID& item_id, const LLUUID& object_id, BOOL take_focus)
{
	LLPreviewGesture* previewp = (LLPreviewGesture*)LLPreview::find(item_id);
	if (previewp)
	{
		previewp->open();   /*Flawfinder: ignore*/
		if (take_focus)
		{
			previewp->setFocus(TRUE);
		}
		return previewp;
	}

	LLPreviewGesture* self = new LLPreviewGesture();

	// Finish internal construction
	self->init(item_id, object_id);

	// Builds and adds to gFloaterView
	LLUICtrlFactory::getInstance()->buildFloater(self, "floater_preview_gesture.xml");
	self->setTitle(title);

	// Move window to top-left of screen
	LLMultiFloater* hostp = self->getHost();
	if (hostp == NULL)
	{
		LLRect r = self->getRect();
		LLRect screen = gFloaterView->getRect();
		r.setLeftTopAndSize(0, screen.getHeight(), r.getWidth(), r.getHeight());
		self->setRect(r);
	}
	else
	{
		// re-add to host to update title
		hostp->addFloater(self, TRUE);
	}

	// Start speculative download of sounds and animations
	const LLUUID animation_folder_id = gInventory.findCategoryUUIDForType(LLFolderType::FT_ANIMATION);
	LLInventoryModelBackgroundFetch::instance().start(animation_folder_id);

	const LLUUID sound_folder_id = gInventory.findCategoryUUIDForType(LLFolderType::FT_SOUND);
	LLInventoryModelBackgroundFetch::instance().start(sound_folder_id);

	// this will call refresh when we have everything.
	LLViewerInventoryItem* item = (LLViewerInventoryItem*)self->getItem();
	if(item && !item->isFinished())
	{
		LLInventoryGestureAvailable* observer;
		observer = new LLInventoryGestureAvailable();
		observer->watchItem(item_id);
		gInventory.addObserver(observer);
		item->fetchFromServer();
	}
	else
	{
		// not sure this is necessary.
		self->refresh();
	}

	if (take_focus)
	{
		self->setFocus(TRUE);
	}

	return self;
}