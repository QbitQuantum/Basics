/*! \brief Write the body of the STK archive
 * \param stk STK/ITK archive file
 * \param chunks Chunk list
 *
 * This function writes the body of the STK archive by storing or compressing
 * (or skipping duplicate files) the files. It also updates the chunk information
 * with the size of the chunk in the archive, the compression method (if modified),
 * ...
 */
void CompressGob::writeBody(Common::Filename *inpath, Common::File &stk, Chunk *chunks) {
	Chunk *curChunk = chunks;
	Common::File src;

	while (curChunk) {
		inpath->setFullName(curChunk->name);
		src.open(*inpath, "rb");

		if (curChunk->packed == 2)
			print("Identical file %12s\t(compressed size %d bytes)", curChunk->name, curChunk->replChunk->size);

		curChunk->offset = stk.pos();
		if (curChunk->packed == 1) {
			curChunk->size = writeBodyPackFile(stk, src);
			if (curChunk->size >= curChunk->realSize) {
// If compressed size >= realsize, compression is useless
// => Store instead
				curChunk->packed = 0;
				stk.seek(curChunk->offset, SEEK_SET);
				src.rewind();
			} else
				print("Compressing %12s\t%d -> %d bytes", curChunk->name, curChunk->realSize, curChunk->size);

		}

		if (curChunk->packed == 0) {
			curChunk->size = writeBodyStoreFile(stk, src);
			print("Storing %12s\t%d bytes", curChunk->name, curChunk->size);
		}
		curChunk = curChunk->next;
	}
}