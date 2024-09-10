void SvcFlagsUnloadModule()
{
	//Uninit message winsow
	for (int i = 0; i < gMsgWndList.getCount(); i++) {
		//this should not happen
		delete gMsgWndList[i];
		gMsgWndList.remove(i);
	}
	gMsgWndList.destroy();

	// Uninit misc
	UninitIcons();
}