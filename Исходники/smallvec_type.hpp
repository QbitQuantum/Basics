	/**
	 * Append an item and return it.
	 * @param to_add the number of items to append
	 * @return pointer to newly allocated item
	 */
	FORCEINLINE T *Append(uint to_add = 1)
	{
		uint begin = this->items;
		this->items += to_add;

		if (this->items > this->capacity) {
			this->capacity = Align(this->items, S);
			this->data = ReallocT(this->data, this->capacity);
		}

		return &this->data[begin];
	}