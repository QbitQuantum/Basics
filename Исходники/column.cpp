void Column::Resize(size_t num) {
	num_tuples_ = num;
	const size_t new_num_blocks = CEIL(num, kNumTuplesPerBlock);
	const size_t old_num_blocks = blocks_.size();
	if (new_num_blocks > old_num_blocks) {    // need to add blocks
		// fill up the last block
		blocks_[old_num_blocks - 1]->Resize(kNumTuplesPerBlock);
		// append new blocks
		for (size_t bid = old_num_blocks; bid < new_num_blocks; bid++) {
			ColumnBlock* new_block = CreateNewBlock();
			new_block->Resize(kNumTuplesPerBlock);
			blocks_.push_back(new_block);
		}
	} else if (new_num_blocks < old_num_blocks) {   // need to remove blocks
		for (size_t bid = old_num_blocks - 1; bid > new_num_blocks; bid--) {
			delete blocks_.back();
			blocks_.pop_back();
		}
	}
	// now the number of block is desired
	// correct the size of the last block
	size_t num_tuples_last_block = num % kNumTuplesPerBlock;
	if (0 < num_tuples_last_block) {
		blocks_.back()->Resize(num_tuples_last_block);
	}

	assert(blocks_.size() == new_num_blocks);
}