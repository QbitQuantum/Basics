bool spu_thread::write_reg(const u32 addr, const u32 value)
{
	auto try_start = [this]()
	{
		if (status.atomic_op([](u32& status)
		{
			if (status & SPU_STATUS_RUNNING)
			{
				return false;
			}

			status = SPU_STATUS_RUNNING;
			return true;
		}))
		{
			state -= cpu_flag::stop;
			thread_ctrl::notify(static_cast<named_thread<spu_thread>&>(*this));
		}
	};

	const u32 offset = addr - RAW_SPU_BASE_ADDR - index * RAW_SPU_OFFSET - RAW_SPU_PROB_OFFSET;

	switch (offset)
	{
	case MFC_LSA_offs:
	{
		if (value >= 0x40000)
		{
			break;
		}

		g_tls_mfc[index].lsa = value;
		return true;
	}

	case MFC_EAH_offs:
	{
		g_tls_mfc[index].eah = value;
		return true;
	}

	case MFC_EAL_offs:
	{
		g_tls_mfc[index].eal = value;
		return true;
	}

	case MFC_Size_Tag_offs:
	{
		g_tls_mfc[index].tag = value & 0x1f;
		g_tls_mfc[index].size = (value >> 16) & 0x7fff;
		return true;
	}

	case MFC_Class_CMD_offs:
	{
		g_tls_mfc[index].cmd = MFC(value & 0xff);

		switch (value & 0xff)
		{
		case MFC_SNDSIG_CMD:
		case MFC_SNDSIGB_CMD:
		case MFC_SNDSIGF_CMD:
		{
			g_tls_mfc[index].size = 4;
			// Fallthrough
		}
		case MFC_PUT_CMD:
		case MFC_PUTB_CMD:
		case MFC_PUTF_CMD:
		case MFC_PUTS_CMD:
		case MFC_PUTBS_CMD:
		case MFC_PUTFS_CMD:
		case MFC_GET_CMD:
		case MFC_GETB_CMD:
		case MFC_GETF_CMD:
		case MFC_GETS_CMD:
		case MFC_GETBS_CMD:
		case MFC_GETFS_CMD:
		{
			if (g_tls_mfc[index].size)
			{
				// Perform transfer immediately
				do_dma_transfer(g_tls_mfc[index]);
			}

			// .cmd should be zero, which is equal to MFC_PPU_DMA_CMD_ENQUEUE_SUCCESSFUL
			g_tls_mfc[index] = {};

			if (value & MFC_START_MASK)
			{
				try_start();
			}

			return true;
		}
		case MFC_BARRIER_CMD:
		case MFC_EIEIO_CMD:
		case MFC_SYNC_CMD:
		{
			g_tls_mfc[index] = {};
			_mm_mfence();
			return true;
		}
		}

		break;
	}

	case Prxy_QueryType_offs:
	{
		// TODO
		// 0 - no query requested; cancel previous request
		// 1 - set (interrupt) status upon completion of any enabled tag groups
		// 2 - set (interrupt) status upon completion of all enabled tag groups

		if (value > 2)
		{
			break;
		}

		if (value)
		{
			int_ctrl[2].set(SPU_INT2_STAT_DMA_TAG_GROUP_COMPLETION_INT); // TODO
		}

		return true;
	}

	case Prxy_QueryMask_offs:
	{
		mfc_prxy_mask = value;
		return true;
	}

	case SPU_In_MBox_offs:
	{
		ch_in_mbox.push(*this, value);
		return true;
	}

	case SPU_RunCntl_offs:
	{
		if (value == SPU_RUNCNTL_RUN_REQUEST)
		{
			try_start();
		}
		else if (value == SPU_RUNCNTL_STOP_REQUEST)
		{
			status &= ~SPU_STATUS_RUNNING;
			state += cpu_flag::stop;
		}
		else
		{
			break;
		}

		run_ctrl = value;
		return true;
	}

	case SPU_NPC_offs:
	{
		if ((value & 2) || value >= 0x40000)
		{
			break;
		}

		npc = value;
		return true;
	}

	case SPU_RdSigNotify1_offs:
	{
		push_snr(0, value);
		return true;
	}

	case SPU_RdSigNotify2_offs:
	{
		push_snr(1, value);
		return true;
	}
	}

	LOG_ERROR(SPU, "RawSPUThread[%d]: Write32(0x%x, value=0x%x): unknown/illegal offset (0x%x)", index, addr, value, offset);
	return false;
}