	unsigned int componentMaskToInt(ComponentMask mask)
	{
		return (unsigned int)log2(mask.to_ulong());
	}