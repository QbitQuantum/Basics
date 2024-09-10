static	void
TermThread(
	TermNode	*term)
{
	PacketClass klass;

ENTER_FUNC;
	klass = RecvPacketClass(term->fp);
	switch (klass) {
	case WFC_TERM_INIT:
		TermInit(term);
		break;
	case WFC_TERM:
		TermSession(term);
		break;
	case WFC_API:
		APISession(term);
		break;
	}
	FreeQueue(term->que);
	xfree(term);
LEAVE_FUNC;
}