PF_Err			
AEFX_AppendText(	
	A_char					*srcAC,				/* >> */
	const A_u_long			dest_sizeLu,		/* >> */
	A_char					*destAC,			/* <> */
	A_u_long				*current_indexPLu)	/* <> */
{
	PF_Err			err = PF_Err_NONE;

	A_u_long		new_strlenLu = strlen(srcAC) + *current_indexPLu;


	if (new_strlenLu <= dest_sizeLu) {
		destAC[*current_indexPLu] = 0x00;

#ifdef AE_OS_WIN
		strncat_s(destAC, dest_sizeLu, srcAC, strlen(srcAC));
#else
		strncat(destAC, srcAC, strlen(srcAC));
#endif
		*current_indexPLu = new_strlenLu;
	} else {
		err = AEFX_ParseError_APPEND_ERROR;
	}

	return err;
}