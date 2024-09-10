/**
   \details Test the SetColumns (0x12) operation

   This function:
   -# Opens the Inbox folder and gets the hierarchy table
   -# Calls the SetColumns operation
   -# Cleans up

   \param mt pointer to the top-level mapitest structure

   \return true on success, otherwise false
 */
_PUBLIC_ bool mapitest_oxctable_SetColumns(struct mapitest *mt)
{
	mapi_object_t		obj_htable;
	struct SPropTagArray	*SPropTagArray;

	/* Step 1. Logon */
	if (! mapitest_common_setup(mt, &obj_htable, NULL)) {
		return false;
	}

	/* Step 2. SetColumns */
	SPropTagArray = set_SPropTagArray(mt->mem_ctx, 0x3,
					  PR_DISPLAY_NAME,
					  PR_FID,
					  PR_FOLDER_CHILD_COUNT);
	SetColumns(&obj_htable, SPropTagArray);
	MAPIFreeBuffer(SPropTagArray);
	mapitest_print_retval(mt, "SetColumns");
	if (GetLastError() != MAPI_E_SUCCESS) {
		return false;
	}

	/* Step 3. Release */
	mapi_object_release(&obj_htable);
	mapitest_common_cleanup(mt);

	return true;
}