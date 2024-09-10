 static void
msgput(msginfo *m, const char *b, int n)
{
	char *msg, *msg0, *msgend;
	const char *be;
	ftnlen msglen0;

	msg = m->msg;
	msgend = m->msgend;
	be = b + n;
	while(b < be) {
		if (msg >= msgend) {
			msglen0 = m->msglen;
			msg0 = m->msg0 = (char*)
				Realloc(m->msg0, m->msglen += MSGGULP);
			msg = msg0 + msglen0;
			m->msgend = msg0 + m->msglen;
			}
		*msg++ = *b++;
		}
	m->msg = msg;
	}