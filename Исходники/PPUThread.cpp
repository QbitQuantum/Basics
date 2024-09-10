void PPUThread::cpu_task()
{
	//SetHostRoundingMode(FPSCR_RN_NEAR);

	if (custom_task)
	{
		if (check_status()) return;

		return custom_task(*this);
	}

	g_tls_log_prefix = []
	{
		const auto cpu = static_cast<PPUThread*>(get_current_cpu_thread());

		return fmt::format("%s [0x%08x]", cpu->get_name(), cpu->pc);
	};

	const auto base = vm::_ptr<const u8>(0);

	// Select opcode table
	const auto& table = *(
		g_cfg_ppu_decoder.get() == ppu_decoder_type::precise ? &s_ppu_interpreter_precise.get_table() :
		g_cfg_ppu_decoder.get() == ppu_decoder_type::fast ? &s_ppu_interpreter_fast.get_table() :
		throw std::logic_error("Invalid PPU decoder"));

	v128 _op;
	decltype(&ppu_interpreter::UNK) func0, func1, func2, func3;

	while (true)
	{
		if (UNLIKELY(state.load()))
		{
			if (check_status()) return;
		}

		// Reinitialize
		{
			const auto _ops = _mm_shuffle_epi8(_mm_lddqu_si128(reinterpret_cast<const __m128i*>(base + pc)), _mm_set_epi8(12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3));
			_op.vi = _ops;
			const v128 _i = v128::fromV(_mm_and_si128(_mm_or_si128(_mm_slli_epi32(_op.vi, 6), _mm_srli_epi32(_op.vi, 26)), _mm_set1_epi32(0x1ffff)));
			func0 = table[_i._u32[0]];
			func1 = table[_i._u32[1]];
			func2 = table[_i._u32[2]];
			func3 = table[_i._u32[3]];
		}

		while (LIKELY(func0(*this, { _op._u32[0] })))
		{
			if (pc += 4, LIKELY(func1(*this, { _op._u32[1] })))
			{
				if (pc += 4, LIKELY(func2(*this, { _op._u32[2] })))
				{
					pc += 4;
					func0 = func3;

					const auto _ops = _mm_shuffle_epi8(_mm_lddqu_si128(reinterpret_cast<const __m128i*>(base + pc + 4)), _mm_set_epi8(12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3));
					_op.vi = _mm_alignr_epi8(_ops, _op.vi, 12);
					const v128 _i = v128::fromV(_mm_and_si128(_mm_or_si128(_mm_slli_epi32(_op.vi, 6), _mm_srli_epi32(_op.vi, 26)), _mm_set1_epi32(0x1ffff)));
					func1 = table[_i._u32[1]];
					func2 = table[_i._u32[2]];
					func3 = table[_i._u32[3]];

					if (UNLIKELY(state.load()))
					{
						break;
					}
					continue;
				}
				break;
			}
			break;
		}
	}
}