	void swap(LongNum &b)
	{
		ilum.swap(b.ilum);
		int c = sign;
		sign = b.sign;
		b.sign = c;
	}