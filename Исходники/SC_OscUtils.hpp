static bool dumpOSCmsg(int inSize, char* inData, bool skipStatus = false)
{
	int size;
	const char *data;

	if (inData[0]) {
		const char *addr = inData;
		if (skipStatus) {
			if (strcmp(addr, "/status") == 0 || strcmp(addr, "status") == 0) // skip /status messages
				return false; // nothing has been printed
		}

		data = OSCstrskip(inData);
		size = inSize - (data - inData);
		scprintf("[ \"%s\",", addr);
	} else {
		scprintf("[ %d,", OSCint(inData));
		data = inData + 4;
		size = inSize - 4;
	}

	sc_msg_iter msg(size, data);

	while (msg.remain())
	{
		char c = msg.nextTag('i');
		switch(c)
		{
		case 'i' :
			scprintf(" %d", msg.geti());
			break;
		case 'f' :
			scprintf(" %g", msg.getf());
			break;
		case 'd' :
			scprintf(" %g", msg.getd());
			break;
		case 's' :
			scprintf(" \"%s\"", msg.gets());
			break;
		case '[' :
			scprintf(" [");
			msg.count ++;
			break;
		case ']' :
			scprintf(" ]");
			msg.count ++;
			break;
		case 'b' :
			scprintf(" DATA[%zu]", msg.getbsize());
			msg.skipb();
			break;
		case 'm' : {
			char midi [4];
			msg.getb (midi, 4);
			scprintf(" MIDI[0x%02x 0x%02x 0x%02x 0x%02x]", midi[0], midi[1], midi[2], midi[3]);
			break;
		}
		case 'c' :
			scprintf(" %c", (char)msg.geti());
			break;
		case 't' :
			scprintf(" %" PRId64 "", msg.gett());
			break;
		case 'T' :
			scprintf(" true");
			msg.count ++;
			break;
		case 'F' :
			scprintf(" false");
			msg.count ++;
			break;
		case 'I' :
			scprintf(" infinitum");
			msg.count ++;
			break;
		case 'N' :
			scprintf(" nil");
			msg.count ++;
			break;
		default :
			scprintf(" !unknown tag '%c' 0x%02x !", isprint(c)?c:'?', (unsigned char)c & 255);
			goto leave;
		}
		if (msg.remain() && (c!= '[')) scprintf(",");
	}
leave:
	scprintf(" ]");
	return true;  // something has been printed
}