	AlignedPODArray& operator = (const AlignedPODArray& that)
	{
		void* tmp_data = that._data_copy();
		_cleanup();
		_count = that._count;
		_sizeof = that._sizeof;
		_data = tmp_data;
		_delete = that._delete;
		_dup = that._dup;
		return *this;
	}