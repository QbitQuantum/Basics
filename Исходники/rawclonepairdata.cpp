size_t fwrite_RawClonePair(const RawClonePair *ary, size_t count, FILE *pOutput)
{
	size_t successfullyWrittenCount = 0;
	for (size_t i = 0; i < count; ++i) {
		RawClonePair data = ary[i];
		flip_endian(data.left.file);
		flip_endian(data.left.begin);
		flip_endian(data.left.end);
		flip_endian(data.right.file);
		flip_endian(data.right.begin);
		flip_endian(data.right.end);
		size_t c = FWRITE(&data, sizeof(RawClonePair), 1, pOutput);
		if (c == 0) {
			break; 
		}
		++successfullyWrittenCount;
	}
	return successfullyWrittenCount;
}