void DialogHeap::collect_blocks(edb::address_t start_address, edb::address_t end_address) {
	model_->clearResults();

	if(IProcess *process = edb::v1::debugger_core->process()) {
		const int min_string_length = edb::v1::config().min_string_length;

		if(start_address != 0 && end_address != 0) {
	#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_OPENBSD)
			malloc_chunk<Addr> currentChunk;
			malloc_chunk<Addr> nextChunk;
			edb::address_t currentChunkAddress = start_address;

			model_->setUpdatesEnabled(false);

			const edb::address_t how_many = end_address - start_address;
			while(currentChunkAddress != end_address) {
				// read in the current chunk..
				process->read_bytes(currentChunkAddress, &currentChunk, sizeof(currentChunk));

				// figure out the address of the next chunk
				const edb::address_t nextChunkAddress = next_chunk(currentChunkAddress, currentChunk);

				// is this the last chunk (if so, it's the 'top')
				if(nextChunkAddress == end_address) {

					const Result r(
						currentChunkAddress,
						currentChunk.chunk_size(),
						tr("Top"));

					model_->addResult(r);

				} else {

					// make sure we aren't following a broken heap...
					if(nextChunkAddress > end_address || nextChunkAddress < start_address) {
						break;
					}

					QString data;

					// read in the next chunk
					process->read_bytes(nextChunkAddress, &nextChunk, sizeof(nextChunk));

					// if this block is a container for an ascii string, display it...
					// there is a lot of room for improvement here, but it's a start
					QString asciiData;
					QString utf16Data;
					int asciisz;
					int utf16sz;
					if(edb::v1::get_ascii_string_at_address(
							block_start(currentChunkAddress),
							asciiData,
							min_string_length,
							currentChunk.chunk_size(),
							asciisz)) {

						data = QString("ASCII \"%1\"").arg(asciiData);
					} else if(edb::v1::get_utf16_string_at_address(
							block_start(currentChunkAddress),
							utf16Data,
							min_string_length,
							currentChunk.chunk_size(),
							utf16sz)) {
						data = QString("UTF-16 \"%1\"").arg(utf16Data);
					} else {

						using std::memcmp;

						quint8 bytes[16];
						process->read_bytes(block_start(currentChunkAddress), bytes, sizeof(bytes));

						if(memcmp(bytes, "\x89\x50\x4e\x47", 4) == 0) {
							data = "PNG IMAGE";
						} else if(memcmp(bytes, "\x2f\x2a\x20\x58\x50\x4d\x20\x2a\x2f", 9) == 0) {
							data = "XPM IMAGE";
						} else if(memcmp(bytes, "\x42\x5a", 2) == 0) {
							data = "BZIP FILE";
						} else if(memcmp(bytes, "\x1f\x9d", 2) == 0) {
							data = "COMPRESS FILE";
						} else if(memcmp(bytes, "\x1f\x8b", 2) == 0) {
							data = "GZIP FILE";
						}

					}

					const Result r(
						currentChunkAddress,
						currentChunk.chunk_size() + sizeof(unsigned int),
						nextChunk.prev_inuse() ? tr("Busy") : tr("Free"),
						data);

					model_->addResult(r);
				}

				// avoif self referencing blocks
				if(currentChunkAddress == nextChunkAddress) {
					break;
				}

				currentChunkAddress = nextChunkAddress;

				ui->progressBar->setValue(util::percentage(currentChunkAddress - start_address, how_many));
			}

			detect_pointers();
			model_->setUpdatesEnabled(true);


	#else
		#error "Unsupported Platform"
	#endif
		}
	}
}