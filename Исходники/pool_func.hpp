/**
 * Resizes the pool so 'index' can be addressed
 * @param index index we will allocate later
 * @pre index >= this->size
 * @pre index < Tmax_size
 */
DEFINE_POOL_METHOD(inline void)::ResizeFor(size_t index)
{
	assert(index >= this->size);
	assert(index < Tmax_size);

	size_t new_size = ::min(Tmax_size, Align(index + 1, Tgrowth_step));

	this->data = ReallocT(this->data, new_size);
	MemSetT(this->data + this->size, 0, new_size - this->size);

	this->size = new_size;
}