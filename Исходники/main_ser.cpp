	//! This is fundamental to avoid crash, otherwise
	// we copy pointer and we do double delete
	my_struct & operator=(my_struct && my)
	{
		size = my.size;
		my.size = 0;
		str.swap(my.str);
		v.swap(my.v);
		ptr = my.ptr;
		my.ptr = 0;

		return *this;
	}