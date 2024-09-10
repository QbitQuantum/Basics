	int count_trailing_ones_hw(span<std::uint32_t const> buf)
	{
		auto const num = int(buf.size());
		std::uint32_t const* ptr = buf.data();

		TORRENT_ASSERT(num >= 0);
		TORRENT_ASSERT(ptr != nullptr);

		for (int i = num - 1; i >= 0; i--)
		{
			if (ptr[i] == 0xffffffff) continue;

#if TORRENT_HAS_BUILTIN_CTZ
			std::uint32_t const v = ~aux::network_to_host(ptr[i]);
			return (num - i - 1) * 32 + __builtin_ctz(v);
#elif defined _MSC_VER
			std::uint32_t const v = ~aux::network_to_host(ptr[i]);
			DWORD pos;
			_BitScanForward(&pos, v);
			return (num - i - 1) * 32 + pos;
#else
			TORRENT_ASSERT_FAIL();
			return -1;
#endif
		}

		return num * 32;
	}