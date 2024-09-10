void
SavedFrame::updatePrivateParent()
{
    setReservedSlot(JSSLOT_PRIVATE_PARENT, PrivateValue(getParent()));
}