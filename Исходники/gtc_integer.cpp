	int perf()
	{
		int Error = 0;
		std::size_t const Count(100000000);

		{
			std::vector<int> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(int i = 0; i < static_cast<int>(Count); ++i)
				Result[i] = glm::log2(static_cast<int>(i));

			std::clock_t End = clock();

			printf("glm::log2<int>: %ld clocks\n", End - Begin);
		}

		{
			std::vector<glm::ivec4> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(int i = 0; i < static_cast<int>(Count); ++i)
				Result[i] = glm::log2(glm::ivec4(i));

			std::clock_t End = clock();

			printf("glm::log2<ivec4>: %ld clocks\n", End - Begin);
		}

#		if GLM_HAS_BITSCAN_WINDOWS
		{
			std::vector<glm::ivec4> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
			{
				glm::tvec4<unsigned long, glm::defaultp> Tmp(glm::uninitialize);
				_BitScanReverse(&Tmp.x, i);
				_BitScanReverse(&Tmp.y, i);
				_BitScanReverse(&Tmp.z, i);
				_BitScanReverse(&Tmp.w, i);
				Result[i] = glm::ivec4(Tmp);
			}

			std::clock_t End = clock();

			printf("glm::log2<ivec4> inlined: %ld clocks\n", End - Begin);
		}


		{
			std::vector<glm::tvec4<unsigned long, glm::defaultp> > Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
			{
				_BitScanReverse(&Result[i].x, i);
				_BitScanReverse(&Result[i].y, i);
				_BitScanReverse(&Result[i].z, i);
				_BitScanReverse(&Result[i].w, i);
			}

			std::clock_t End = clock();

			printf("glm::log2<ivec4> inlined no cast: %ld clocks\n", End - Begin);
		}


		{
			std::vector<glm::ivec4> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
			{
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result[i].x), i);
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result[i].y), i);
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result[i].z), i);
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result[i].w), i);
			}

			std::clock_t End = clock();

			printf("glm::log2<ivec4> reinterpret: %ld clocks\n", End - Begin);
		}
#		endif//GLM_HAS_BITSCAN_WINDOWS

		{
			std::vector<float> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(std::size_t i = 0; i < Count; ++i)
				Result[i] = glm::log2(static_cast<float>(i));

			std::clock_t End = clock();

			printf("glm::log2<float>: %ld clocks\n", End - Begin);
		}

		{
			std::vector<glm::vec4> Result;
			Result.resize(Count);

			std::clock_t Begin = clock();

			for(int i = 0; i < static_cast<int>(Count); ++i)
				Result[i] = glm::log2(glm::vec4(i));

			std::clock_t End = clock();

			printf("glm::log2<vec4>: %ld clocks\n", End - Begin);
		}

		return Error;
	}