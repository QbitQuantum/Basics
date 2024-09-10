*/	RL_API int RL_Do_Binary(int *exit_status, const REBYTE *bin, REBINT length, REBCNT flags, REBCNT key, RXIARG *result)
/*
**	Evaluate an encoded binary script such as compressed text.
**
**	Returns:
**		The datatype of the result or zero if error in the encoding.
**	Arguments:
**		bin - by default, a REBOL compressed UTF-8 (or ASCII) script.
**		length - the length of the data.
**		flags - special flags (set to zero at this time).
**		key - encoding, encryption, or signature key.
**		result - value returned from evaluation.
**	Notes:
**		As of A104, only compressed scripts are supported, however,
**		rebin, cloaked, signed, and encrypted formats will be supported.
**
***********************************************************************/
{
	REBSER *text;
#ifdef DUMP_INIT_SCRIPT
	int f;
#endif
	int do_result;

	text = Decompress(bin, length, -1, FALSE, FALSE);
	if (!text) return FALSE;
	Append_Codepoint_Raw(text, 0);

#ifdef DUMP_INIT_SCRIPT
	f = _open("host-boot.r", _O_CREAT | _O_RDWR, _S_IREAD | _S_IWRITE );
	_write(f, STR_HEAD(text), LEN_BYTES(STR_HEAD(text)));
	_close(f);
#endif

	PUSH_GUARD_SERIES(text);
	do_result = RL_Do_String(exit_status, text->data, flags, result);
	DROP_GUARD_SERIES(text);

	Free_Series(text);
	return do_result;
}