static INT_PTR destroyAvatar(WPARAM wParam, LPARAM)
{
	flash_avatar_item key(((FLASHAVATAR*)wParam)->hContact, *(FLASHAVATAR*)wParam, NULL);

	Lock l(cs);

	flash_avatar_item *item = FlashList.find(&key);
	if (item) {
		if (item->pFlash)
			item->pFlash->Release();
		if (item->hFA.hWindow)
			DestroyWindow(item->hFA.hWindow);
		mir_free(item->hFA.cUrl);
		FlashList.remove(item);
		delete item;
	}
	return 0;
}