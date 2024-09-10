	int KinectInternalData::SendCommand(unsigned short command, unsigned char *commandbuffer, unsigned int commandbufferlength, unsigned char *replybuffer, unsigned int replybufferlength)
	{
		int i, j, ret = 0;
		uint8_t obuf[0x2000];
		uint8_t ibuf[0x2000];
		ZeroMemory(obuf, 0x2000);
		ZeroMemory(ibuf, 0x2000);

		cam_hdr *chdr = (cam_hdr *)obuf;
		cam_hdr *rhdr = (cam_hdr *)ibuf;		

		chdr->cmd = command;
		chdr->tag = mCommandTag;
		chdr->len = commandbufferlength / 2;
		chdr->magic[0] = 0x47;
		chdr->magic[1] = 0x4d;


		memcpy (obuf + sizeof (*chdr), commandbuffer, commandbufferlength);


		ret = usb_control_msg(mDeviceHandle, 0x40, 0, 0, 0, (char*)obuf, commandbufferlength + sizeof (cam_hdr), 1600);
		//ret = usb_control_msg(mDeviceHandle, 0x40, 0, 0, 0, (char*)ibuf, 0x200, 1600);
		if (ret < 0)
		{
			ErrorMessage("SendCommand: Failed to send control message! (%d)\n", ret);

			return ret;
		}

		do
		{

			ret = usb_control_msg(mDeviceHandle, 0xc0, 0, 0, 0, (char*)ibuf, 0x200, 1600);
			Sleep(10);
		}
		while (ret == 0);

		TraceMessage("Control reply: %d\n", ret);
		if (ret < sizeof (cam_hdr))
		{
			ErrorMessage ("SendCommand: Input control transfer failed (%d)\n", ret);
			return ret;
		}
		ret -= sizeof (cam_hdr);

		if (rhdr->magic[0] != 0x52 || rhdr->magic[1] != 0x42)
		{
			ErrorMessage ("SendCommand: Bad magic %02x %02x\n", rhdr->magic[0], rhdr->magic[1]);
			return -1;
		}
		if (rhdr->cmd != chdr->cmd)
		{
			ErrorMessage ("SendCommand: Bad cmd %02x != %02x\n", rhdr->cmd, chdr->cmd);
			return -1;
		}
		if (rhdr->tag != chdr->tag)
		{
			ErrorMessage ("SendCommand: Bad tag %04x != %04x\n", rhdr->tag, chdr->tag);
			return -1;
		}
		if (rhdr->len != (ret / 2))
		{
			ErrorMessage ("SendCommand: Bad len %04x != %04x\n", rhdr->len, (int) (ret / 2));
			return -1;
		}

		if (ret > replybufferlength)
		{
			WarningMessage ("SendCommand: Data buffer is %d bytes long, but got %d bytes\n", replybufferlength, ret);
			memcpy (replybuffer, ibuf + sizeof (*rhdr), replybufferlength);
		}
		else
		{
			memcpy (replybuffer, ibuf + sizeof (*rhdr), ret);
		}
	

		mCommandTag++;

		return ret;
	};