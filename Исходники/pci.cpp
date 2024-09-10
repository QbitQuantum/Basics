void PCI::scan_devices()
{
	int device_count = 0;
	for (uint32_t bus = 0; bus < 256; bus++)
	{
		for (uint32_t slot = 0; slot < 32; slot++)
		{
			for (uint32_t function = 0; function < 8; function++)
			{
				//根据配置空间的第0个寄存器是否返回0FFFFH值来判断是否存在该PCI设备
				uint32_t vendor = getVendorID(bus, slot, function);
				if (vendor == 0xffff) break;
				uint32_t device = getDeviceID(bus, slot, function);
				uint32_t baseclass = getBaseClass(bus, slot, function);
				uint32_t subclass = getSubClass(bus, slot, function);
				uint32_t progif = getProgIF(bus, slot, function);

				PCI_IDS* pci_ids = get_device_ids(vendor, device, 0, 0);
				PCI_DEVICE_CLASS* pci_class = get_device_class(baseclass, subclass, progif);
				if (pci_ids != NULL)
				{
					printf("%d %02X:%02X:%X device: %s\n",
						device_count++, bus, slot, function, pci_ids->device_name);
				}
				else
				{
					printf("%d %02X:%02X:%X vendor: %x device: %x class: %x subclass: %x \n",
						device_count++, bus, slot, function, vendor, device, baseclass, subclass);
				}
				uint32_t header_type = getHeaderType(bus, slot, function);
				if ( (header_type & 0x80) == 0) break;

				/*pci_device *pdev = (pci_device *)malloc(sizeof(pci_device));
				pdev->vendor = vendor;
				pdev->device = device;
				pdev->func = function;
				pdev->driver = 0;
				add_pci_device(pdev);*/
			}
		}
	}
}