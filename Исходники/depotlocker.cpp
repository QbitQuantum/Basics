void DepotLocker::postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, bool isCompleteRemoval, cylinderlink_t link /*= LINK_OWNER*/)
{
	if (getParent() != NULL) {
		getParent()->postRemoveNotification(thing, newParent, index, isCompleteRemoval, LINK_PARENT);
	}
}