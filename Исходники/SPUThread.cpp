void SPUThread::do_dma_transfer(u32 cmd, spu_mfc_arg_t args)
{
	if (cmd & (MFC_BARRIER_MASK | MFC_FENCE_MASK))
	{
		_mm_mfence();
	}

	u32 eal = VM_CAST(args.ea);

	if (eal >= SYS_SPU_THREAD_BASE_LOW && m_type == CPU_THREAD_SPU) // SPU Thread Group MMIO (LS and SNR)
	{
		const u32 index = (eal - SYS_SPU_THREAD_BASE_LOW) / SYS_SPU_THREAD_OFFSET; // thread number in group
		const u32 offset = (eal - SYS_SPU_THREAD_BASE_LOW) % SYS_SPU_THREAD_OFFSET; // LS offset or MMIO register

		const auto group = tg.lock();

		if (group && index < group->num && group->threads[index])
		{
			auto& spu = static_cast<SPUThread&>(*group->threads[index]);

			if (offset + args.size - 1 < 0x40000) // LS access
			{
				eal = spu.offset + offset; // redirect access
			}
			else if ((cmd & MFC_PUT_CMD) && args.size == 4 && (offset == SYS_SPU_THREAD_SNR1 || offset == SYS_SPU_THREAD_SNR2))
			{
				spu.push_snr(SYS_SPU_THREAD_SNR2 == offset, read32(args.lsa));
				return;
			}
			else
			{
				throw EXCEPTION("Invalid MMIO offset (cmd=0x%x, lsa=0x%x, ea=0x%llx, tag=0x%x, size=0x%x)", cmd, args.lsa, args.ea, args.tag, args.size);
			}
		}
		else
		{
			throw EXCEPTION("Invalid thread type (cmd=0x%x, lsa=0x%x, ea=0x%llx, tag=0x%x, size=0x%x)", cmd, args.lsa, args.ea, args.tag, args.size);
		}
	}

	switch (cmd & ~(MFC_BARRIER_MASK | MFC_FENCE_MASK))
	{
	case MFC_PUT_CMD:
	case MFC_PUTR_CMD:
	{
		memcpy(vm::get_ptr(eal), vm::get_ptr(offset + args.lsa), args.size);
		return;
	}

	case MFC_GET_CMD:
	{
		memcpy(vm::get_ptr(offset + args.lsa), vm::get_ptr(eal), args.size);
		return;
	}
	}

	throw EXCEPTION("Invalid command %s (cmd=0x%x, lsa=0x%x, ea=0x%llx, tag=0x%x, size=0x%x)", get_mfc_cmd_name(cmd), cmd, args.lsa, args.ea, args.tag, args.size);
}