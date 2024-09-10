void ExecuteCommand(u32 _Address)
{
	IPCCommandResult result = IWII_IPC_HLE_Device::GetNoReply();

	IPCCommandType Command = static_cast<IPCCommandType>(Memory::Read_U32(_Address));
	s32 DeviceID = Memory::Read_U32(_Address + 8);

	std::shared_ptr<IWII_IPC_HLE_Device> pDevice = (DeviceID >= 0 && DeviceID < IPC_MAX_FDS) ? g_FdMap[DeviceID] : nullptr;

	INFO_LOG(WII_IPC_HLE, "-->> Execute Command Address: 0x%08x (code: %x, device: %x) %p", _Address, Command, DeviceID, pDevice.get());

	switch (Command)
	{
	case IPC_CMD_OPEN:
	{
		u32 Mode = Memory::Read_U32(_Address + 0x10);
		DeviceID = getFreeDeviceId();

		std::string DeviceName = Memory::GetString(Memory::Read_U32(_Address + 0xC));

		WARN_LOG(WII_IPC_HLE, "Trying to open %s as %d", DeviceName.c_str(), DeviceID);
		if (DeviceID >= 0)
		{
			if (DeviceName.find("/dev/es") == 0)
			{
				u32 j;
				for (j=0; j<ES_MAX_COUNT; j++)
				{
					if (!es_inuse[j])
					{
						es_inuse[j] = true;
						g_FdMap[DeviceID] = es_handles[j];
						result = es_handles[j]->Open(_Address, Mode);
						Memory::Write_U32(DeviceID, _Address+4);
						break;
					}
				}

				if (j == ES_MAX_COUNT)
				{
					Memory::Write_U32(FS_EESEXHAUSTED, _Address + 4);
					result = IWII_IPC_HLE_Device::GetDefaultReply();
				}
			}
			else if (DeviceName.find("/dev/") == 0)
			{
				pDevice = GetDeviceByName(DeviceName);
				if (pDevice)
				{
					g_FdMap[DeviceID] = pDevice;
					result = pDevice->Open(_Address, Mode);
					INFO_LOG(WII_IPC_FILEIO, "IOP: ReOpen (Device=%s, DeviceID=%08x, Mode=%i)",
						pDevice->GetDeviceName().c_str(), DeviceID, Mode);
					Memory::Write_U32(DeviceID, _Address+4);
				}
				else
				{
					WARN_LOG(WII_IPC_HLE, "Unimplemented device: %s", DeviceName.c_str());
					Memory::Write_U32(FS_ENOENT, _Address+4);
					result = IWII_IPC_HLE_Device::GetDefaultReply();
				}
			}
			else
			{
				pDevice = CreateFileIO(DeviceID, DeviceName);
				result = pDevice->Open(_Address, Mode);

				INFO_LOG(WII_IPC_FILEIO, "IOP: Open File (Device=%s, ID=%08x, Mode=%i)",
						pDevice->GetDeviceName().c_str(), DeviceID, Mode);
				if (Memory::Read_U32(_Address + 4) == (u32)DeviceID)
				{
					g_FdMap[DeviceID] = pDevice;
				}
			}
		}
		else
		{
			Memory::Write_U32(FS_EFDEXHAUSTED, _Address + 4);
			result = IWII_IPC_HLE_Device::GetDefaultReply();
		}
		break;
	}
	case IPC_CMD_CLOSE:
	{
		if (pDevice)
		{
			result = pDevice->Close(_Address);

			for (u32 j=0; j<ES_MAX_COUNT; j++)
			{
				if (es_handles[j] == g_FdMap[DeviceID])
				{
					es_inuse[j] = false;
				}
			}

			g_FdMap[DeviceID].reset();
		}
		else
		{
			Memory::Write_U32(FS_EINVAL, _Address + 4);
			result = IWII_IPC_HLE_Device::GetDefaultReply();
		}
		break;
	}
	case IPC_CMD_READ:
	{
		if (pDevice)
		{
			result = pDevice->Read(_Address);
		}
		else
		{
			Memory::Write_U32(FS_EINVAL, _Address + 4);
			result = IWII_IPC_HLE_Device::GetDefaultReply();
		}
		break;
	}
	case IPC_CMD_WRITE:
	{
		if (pDevice)
		{
			result = pDevice->Write(_Address);
		}
		else
		{
			Memory::Write_U32(FS_EINVAL, _Address + 4);
			result = IWII_IPC_HLE_Device::GetDefaultReply();
		}
		break;
	}
	case IPC_CMD_SEEK:
	{
		if (pDevice)
		{
			result = pDevice->Seek(_Address);
		}
		else
		{
			Memory::Write_U32(FS_EINVAL, _Address + 4);
			result = IWII_IPC_HLE_Device::GetDefaultReply();
		}
		break;
	}
	case IPC_CMD_IOCTL:
	{
		if (pDevice)
		{
			result = pDevice->IOCtl(_Address);
		}
		break;
	}
	case IPC_CMD_IOCTLV:
	{
		if (pDevice)
		{
			result = pDevice->IOCtlV(_Address);
		}
		break;
	}
	default:
	{
		_dbg_assert_msg_(WII_IPC_HLE, 0, "Unknown IPC Command %i (0x%08x)", Command, _Address);
		break;
	}
	}

	// Ensure replies happen in order
	const s64 ticks_until_last_reply = last_reply_time - CoreTiming::GetTicks();
	if (ticks_until_last_reply > 0)
		result.reply_delay_ticks += ticks_until_last_reply;
	last_reply_time = CoreTiming::GetTicks() + result.reply_delay_ticks;

	if (result.send_reply)
	{
		// The original hardware overwrites the command type with the async reply type.
		Memory::Write_U32(IPC_REP_ASYNC, _Address);
		// IOS also seems to write back the command that was responded to in the FD field.
		Memory::Write_U32(Command, _Address + 8);
		// Generate a reply to the IPC command
		EnqueueReply(_Address, (int)result.reply_delay_ticks);
	}
}