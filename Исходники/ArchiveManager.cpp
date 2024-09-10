/* ArchiveManager::closeArchive
 * Closes the archive at index, and removes it from the list if the
 * index is valid. Returns false on invalid index, true otherwise
 *******************************************************************/
bool ArchiveManager::closeArchive(int index)
{
	// Check for invalid index
	if (index < 0 || index >= (int) open_archives.size())
		return false;

	// Announce archive closing
	MemChunk mc;
	int32_t temp = index;
	mc.write(&temp, 4);
	announce("archive_closing", mc);

	// Delete any bookmarked entries contained in the archive
	deleteBookmarksInArchive(open_archives[index].archive);

	// Remove from resource manager
	theResourceManager->removeArchive(open_archives[index].archive);

	// Delete any embedded configuration
	//theGameConfiguration->removeEmbeddedConfig(open_archives[index].archive->getFilename());

	// Close any open child archives
	// Clear out the open_children vector first, lest the children try to
	// remove themselves from it
	vector<Archive*> open_children = open_archives[index].open_children;
	open_archives[index].open_children.clear();
	for (size_t a = 0; a < open_children.size(); a++)
	{
		int ci = archiveIndex(open_children[a]);
		if (ci >= 0)
			closeArchive(ci);
	}

	// Remove ourselves from our parent's open-child list
	ArchiveEntry* parent = open_archives[index].archive->getParent();
	if (parent)
	{
		Archive* gp = parent->getParent();
		if (gp)
		{
			int pi = archiveIndex(gp);
			if (pi >= 0)
			{
				vector<Archive*>& children = open_archives[pi].open_children;
				for (vector<Archive*>::iterator it = children.begin();
					it < children.end();
					it++)
				{
					if (*it == open_archives[index].archive)
					{
						children.erase(it, it + 1);
						break;
					}
				}
			}
		}
	}

	// Close the archive
	open_archives[index].archive->close();

	// Delete the archive object
	delete open_archives[index].archive;

	// Remove the archive at index from the list
	open_archives.erase(open_archives.begin() + index);

	// Announce closed
	announce("archive_closed", mc);

	return true;
}