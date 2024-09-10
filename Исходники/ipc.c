int send_msg (int id, int mode, int partner, wchar_t *format, ...) {

	struct message msg;
	struct msqid_ds msgstat;
	va_list arglist;

	va_start(arglist,format);
	msg.prio = partner;
	vswprintf(msg.text, MSGLEN, format, arglist);

	if (mode == IPC_NOWAIT) {
		msgsnd(id, &msg, MSGLEN, mode);
//		wprintf (L"SEND -- free: %d / self: %d / partner: %d\n", 16 - msgstat.msg_qnum, getpid(), partner);
	}
/*
ushort msg_cbytes;    // Anzahl belegten Bytes in Queue
ushort msg_qnum;      // Anzahl der Nachrichten in Queue
ushort msg_qbytes;    // Max. Anzahl Bytes der Queue
*/
	else {
		while (1) {
			msgctl(id, IPC_STAT, &msgstat);
			if ((((msgstat.msg_qbytes - msgstat.msg_cbytes) * 100) / msgstat.msg_qbytes) > QRESERVE) {
//				wprintf (L"SEND -- free: %d / self: %d / partner: %d\n", 16 - msgstat.msg_qnum, getpid(), partner);
				msgsnd(id, &msg, MSGLEN, mode);
				break;
			}
//			else wprintf(L"HOLD -- free: %d / self: %d / partner: %d\n", 16 - msgstat.msg_qnum, getpid(), partner);
			usleep (FREQUENCY);
		}
	}
	return 0;
}