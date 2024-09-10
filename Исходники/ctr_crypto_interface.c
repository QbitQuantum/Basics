//process the current window, and advance to the next one.
//Returns a negative number on a failure, a zero when there are still more windows to go, and a 1 when done.
static inline int process_window(ctr_crypto_interface *io, write_window *window, size_t sector_size, size_t block_size, void (*input_function)(void *io, void *buffer, uint64_t block, size_t block_count), void (*output_function)(void *io, void *buffer, uint64_t block, size_t block_count))
{
	//FIXME what if we try to read more than there is disk? Return zeros?
	size_t sectors_to_read = (window->window_size - window->window_offset) / sector_size;
	int res = ctr_io_read_sector(io->lower_io, window->window + window->window_offset, window->window_size - window->window_offset, window->current_sector, sectors_to_read);
	if (res)
		return -1;

	size_t block_start_offset = window->block_offset;
	uint8_t *pos = window->window + block_start_offset;

	size_t amount_to_copy = window->window_size - window->window_offset;
	if (amount_to_copy > window->buffer_size - window->buffer_offset)
		amount_to_copy = window->buffer_size - window->buffer_offset;

	//In the case that blocks are aligned to sectors, this is not necessary... FIXME
	//only process parts that won't be overwritten completely
	//	from block_start_offset to window->window_offset
	size_t blocks_to_process = CEIL(window->window_offset - block_start_offset, block_size);
	if (!blocks_to_process) blocks_to_process = 1;
	output_function(io, pos, window->block, blocks_to_process);

	//now copy data from buffer
	memcpy(window->window + window->window_offset, window->buffer + window->buffer_offset, amount_to_copy);
	window->buffer_offset += amount_to_copy;

	blocks_to_process = CEIL(amount_to_copy + window->window_offset - block_start_offset, block_size);
	input_function(io, pos, window->block, blocks_to_process);

	//We need to write out the full blocks processed actually, not just the sectors
	size_t sectors_processed = (amount_to_copy + window->window_offset) / sector_size;
	size_t sectors_to_copy = CEIL(blocks_to_process * block_size, sector_size);
	res = ctr_io_write_sector(io->lower_io, window->window, sectors_to_copy * sector_size, window->sector);
	if (res)
		return -2;

	//Copy sector that contain part of next block
	update_window(window, sectors_processed);

	return window->buffer_offset >= window->buffer_size;
}