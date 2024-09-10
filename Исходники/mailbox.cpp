void Mailbox::postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t link /*= LINK_OWNER*/, bool isNewItem /*=true*/)
{
	getParent()->postAddNotification(thing, oldParent, index, LINK_PARENT, isNewItem);
}