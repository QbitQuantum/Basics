// static
void LLFloaterGesture::onClickEdit(void* data)
{
	LLFloaterGesture* self = (LLFloaterGesture*)data;

	LLCtrlListInterface *list = self->childGetListInterface("gesture_list");
	if (!list) return;
	const LLUUID& item_id = list->getCurrentID();

	LLInventoryItem* item = gInventory.getItem(item_id);
	if (!item) return;

	std::string title("Gesture: ");
	title.append(item->getName());

	LLPreviewGesture* previewp = LLPreviewGesture::show(title, item_id, LLUUID::null);
	if (!previewp->getHost())
	{
		previewp->setRect(gFloaterView->findNeighboringPosition(self, previewp));
	}
}