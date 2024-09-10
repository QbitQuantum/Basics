// ----------------------------------------------------------------------------
// ArchiveEntryList::labelEdited
//
// Called when a label has been edited
// ----------------------------------------------------------------------------
void ArchiveEntryList::labelEdited(int col, int index, string new_label)
{
	if (undo_manager)
		undo_manager->beginRecord("Rename Entry");

	// Rename the entry
	ArchiveEntry* entry = getEntry(index);
	if (entry->getParent())
		entry->getParent()->renameEntry(entry, new_label);
	else
		entry->rename(new_label);

	if (undo_manager)
		undo_manager->endRecord(true);
}