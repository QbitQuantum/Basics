void EditorAssetLibraryItemDownload::_close() {

	DirAccess *da = DirAccess::create(DirAccess::ACCESS_FILESYSTEM);
	da->remove(download->get_download_file()); //clean up removed file
	memdelete(da);
	queue_delete();
}