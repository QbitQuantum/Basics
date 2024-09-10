		void compress(compress_output_type &dst, const compress_input_type &src)
		{
			uint64_t length = dst.size();
			int ok = ::compress(&dst[0], (uLongf *)&length, &src[0], src.size());
			if(Z_OK != ok) throw salm::exception("zip library error", salm::UNKNOWN_ERROR);
						
			dst.resize(length + sizeof(uint64_t));

			//byte order 처리(리틀 엔디안으로 저장한다.)
			if (salm::is_big_endian()) *(reinterpret_cast<uint64_t*>(&dst[length])) = _byteswap_uint64(static_cast<uint64_t>(src.size()));
			else *(reinterpret_cast<uint64_t*>(&dst[length])) = static_cast<uint64_t>(src.size());
		}