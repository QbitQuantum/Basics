error_code sys_memory_get_page_attribute(u32 addr, vm::ptr<sys_page_attr_t> attr)
{
	sys_memory.trace("sys_memory_get_page_attribute(addr=0x%x, attr=*0x%x)", addr, attr);

	if (!vm::check_addr(addr))
	{
		return CELL_EINVAL;
	}

	if (!vm::check_addr(attr.addr(), attr.size()))
	{
		return CELL_EFAULT;
	}

	attr->attribute = 0x40000ull; // SYS_MEMORY_PROT_READ_WRITE (TODO)
	attr->access_right = 0xFull; // SYS_MEMORY_ACCESS_RIGHT_ANY (TODO)

	if (vm::check_addr(addr, 1, vm::page_1m_size))
	{
		attr->page_size = 0x100000;
	}
	else if (vm::check_addr(addr, 1, vm::page_64k_size))
	{
		attr->page_size = 0x10000;
	}
	else
	{
		attr->page_size = 4096;
	}
	
	return CELL_OK;
}