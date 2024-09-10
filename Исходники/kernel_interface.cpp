status_t
udf_rewind_dir(fs_volume *volume, fs_vnode *vnode, void *cookie)
{
	TRACE(("udf_rewind_dir: volume = %p, vnode = %p, cookie = %p\n",
		volume, vnode, cookie));

	if (!volume || !vnode || !cookie)
		RETURN(B_BAD_VALUE);

	Icb *dir = (Icb *)vnode->private_node;
	DirectoryIterator *iterator = (DirectoryIterator *)cookie;

	if (dir != iterator->Parent()) {
		PRINT(("udf_rewind_dir: icb does not match parent Icb of given "
			"DirectoryIterator! (iterator->Parent = %p)\n", iterator->Parent()));
		return B_BAD_VALUE;
	}

	iterator->Rewind();

	return B_OK;
}