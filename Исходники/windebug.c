/***********************************************************************
 *           WinNotify       (WINDEBUG.3)
 *  written without _any_ docu
 */
void WINAPI WinNotify16(CONTEXT86 *context)
{
	FIXME("(AX=%04x):stub.\n", AX_reg(context));
	switch (AX_reg(context))
	{
		case 0x000D:
		case 0x000E:
		case 0x0060:	/* do nothing */
				break;
		case 0x0062:
				break;
		case 0x0063:	/* do something complicated */
				break;
		case 0x0064:	/* do something complicated */
				break;
		case 0x0065:	/* do something complicated */
				break;
		case 0x0050:	/* do something complicated, now just return error */
				SET_CFLAG(context);
				break;
		case 0x0052:	/* do something complicated */
				break;
		default:
				break;
	}
}