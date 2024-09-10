HRESULT __stdcall VF_ReadDataFunc_Blen( 
	VF_FileHandle hFileHandle,
	DWORD dwStream,void *lpData )
{
	char req[256];
	char buf[256];
	SOCKET s_in;
	int width;
	int height;
	int y;
	int rval;
	unsigned char * framebuf;

	conndesc * c = (conndesc*) hFileHandle;
	LPVF_ReadData_Video v = (LPVF_ReadData_Video) lpData;

	if (c == 0 || dwStream != VF_STREAM_VIDEO || v == 0) { 
		return VF_ERROR;
	}

	s_in = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s_in < 0) {
		return VF_ERROR;
	}

	if (connect(s_in, (struct sockaddr*) &c->addr,
		    sizeof(c->addr)) < 0) {
		goto errout;
	}

	sprintf(req, "GET /images/ppm/%d.ppm HTTP/1.0\n\n",
		(int) (v->dwFrameNumberL) + c->start);

	my_send(s_in, req);

	do {
		if (my_gets(s_in, buf, 256) <= 0) {
			goto errout;
		}
	} while (strcmp(buf, "P6\n") != 0);

	do {
                rval = my_gets(s_in, buf, 256); 
        } while ( (buf[0] == '#' || buf[0] == '\n') && rval >= 0);

        if (sscanf(buf, "%d %d\n", &width, &height) != 2) {
		goto errout;
        }

	if (width != c->width || height != c->height) {
		goto errout;
	}

	my_gets(s_in, buf, 256); /* 255 */

	framebuf = (unsigned char*) v->lpData;

	for (y = 0; y < height; y++) {
		unsigned char * p = framebuf + v->lPitch * y;
		unsigned char * e = p + width * 3;

		my_recv(s_in, (char*) p, width * 3);
		while (p != e) {
			unsigned char tmp = p[2];
			p[2] = p[0];
			p[0] = tmp;

			p += 3;
		}
	}
	closesocket(s_in);
	return VF_OK;
 errout:
	closesocket(s_in);
	return VF_ERROR;
}