void WriteBufferValidUTF8::nextImpl()
{
	char *p = &memory[0];
	char *valid_start = p;

	while (p < pos)
	{
#ifdef __x86_64__
		/// Быстрый пропуск ASCII
		static constexpr size_t SIMD_BYTES = 16;
		const char * simd_end = p + (pos - p) / SIMD_BYTES * SIMD_BYTES;

		while (p < simd_end && !_mm_movemask_epi8(_mm_loadu_si128(reinterpret_cast<const __m128i*>(p))))
			p += SIMD_BYTES;

		if (!(p < pos))
			break;
#endif

		size_t len = 1 + static_cast<size_t>(trailingBytesForUTF8[static_cast<unsigned char>(*p)]);

		if (len > 4)
		{
			/// Невалидное начало последовательности. Пропустим один байт.
			putValid(valid_start, p - valid_start);
			putReplacement();
			++p;
			valid_start = p;
		}
		else if (p + len > pos)
		{
			/// Еще не вся последовательность записана.
			break;
		}
		else if (Poco::UTF8Encoding::isLegal(reinterpret_cast<unsigned char*>(p), len))
		{
			/// Валидная последовательность.
			p += len;
		}
		else
		{
			/// Невалидная последовательность. Пропустим только первый байт.
			putValid(valid_start, p - valid_start);
			putReplacement();
			++p;
			valid_start = p;
		}
	}

	putValid(valid_start, p - valid_start);

	size_t cnt = pos - p;
	/// Сдвинем незаконченную последовательность в начало буфера.
	for (size_t i = 0; i < cnt; ++i)
		memory[i] = p[i];

	working_buffer = Buffer(&memory[cnt], &memory[0] + memory.size());
}