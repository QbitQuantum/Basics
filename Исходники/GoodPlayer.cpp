void OnDropFiles(HDROP hDrop)
{
	char path[256];

	DragQueryFile(hDrop, 0, path, sizeof(path));
	DragFinish(hDrop);
	OpenMedia(path);
}