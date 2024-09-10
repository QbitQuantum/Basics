/*!	\brief Changes the current interface.
	
	If this fails it will set the interface's \a ID to \c PPP_UNDEFINED_INTERFACE_ID.
	
	\param ID The ID of the new interface.
	
	\return
		- \c B_OK: Object could be initialized successfully and the interface exists.
		- \c B_BAD_INDEX: The interface does not exist.
		- any other value: The PPP stack could not be loaded.
	
	\sa Control()
*/
status_t
PPPInterface::SetTo(ppp_interface_id ID)
{
	// printf("Set To %ld begin=============================\n", ID);
	if (fFD < 0) {
		printf("No fFD\n");
		return B_ERROR;
	}

	fID = ID;
	
	ppp_interface_info_t info;
	// printf("SetTo info:%p\n", &info);
	if (GetInterfaceInfo(&info)) {
		fName = info.info.name;
		fID = ID;
		// printf("%s fine: name:%s, fID:%ld\n", __func__, info.info.name, fID);
	} else {
		fName = "";
		fID = PPP_UNDEFINED_INTERFACE_ID;
		// printf("%s fail: name:%s, fID:%ld\n", __func__, "", fID);
		return B_ERROR;
	}
	
	// printf("Set To %ld end =============================\n", ID);

	return B_OK;
}