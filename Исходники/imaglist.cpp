// Remove all images
bool wxImageList::RemoveAll()
{
    // don't use ImageList_RemoveAll() because mingw32 headers don't have it
    return Remove(-1);
}