int OpenDevice (char *name, int unit, void *ioreq, uint32 flags)
{
	void *elf;
	struct Device *device;
	struct StdIOReq *stdreq = ioreq;
	struct IOMReq iomreq;
	struct Resident *resident;
	int rc;
	
	
	if (GetPID() != iomanager_pid)
	{
		/* Send message to IO Manager task */
	
		iomreq.device = &iomanager_device;
		iomreq.unitp = NULL;
		iomreq.as = &kernel_as;
		iomreq.cmd = IOM_CMD_OPENDEVICE;
		iomreq.od_name = name;
		iomreq.od_unit = unit;
		iomreq.od_ioreq = ioreq;
		iomreq.od_flags = flags;
		
		DoIO (&iomreq, NULL);
		
		if (iomreq.rc != 0);
			SetError (iomreq.error);
		
		return iomreq.rc;
	}
	else
	{
		/* Execute nested opendevice() on IOManager task context */
	
				
		if ((device = FindDevice (name)) != NULL)
		{
			stdreq->device = device;
			rc = device->opendevice (unit, ioreq, flags);
			return rc;
		}
		else
		{
			/* Use absolute or /sys/dev prefix for pathname */		
		
			if ((elf = LoadDevice (name)) != NULL)
			{
				if ((resident = FindElfResident (elf)) != NULL)
				{
					if (resident->type == RTYPE_DEVICE &&
						resident->flags & RFLG_AUTOINIT && resident->init(elf) != -1)
					{
						if ((device = resident->data) != NULL)
						{
							stdreq->device = device;
							rc = device->opendevice (unit, ioreq, flags);
							return rc;
						}
					}
				}
				
				UnloadDevice (elf);
			}
		}
	}
	
	return -1;
}