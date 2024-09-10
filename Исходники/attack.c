// Mask and size for the table map. Use 12.5% full
PRIVATE void calculate_table_mask(unsigned int num_elem)
{
	int i;
	size_table = 1;

	// Generate result with all bits less than
	// first bit in num_elem in 1
	while(size_table < num_elem)
		size_table = (size_table << 1) + 1;

	// 3 bits more into account
	for(i = 0; i < 3; i++)
		size_table = (size_table << 1) + 1;

	size_bit_table = (size_table << 1) + 1;
	//size_bit_table = (size_bit_table << 1) + 1;

	_BitScanReverse(&first_bit_size_bit_table, size_bit_table);
	_BitScanReverse(&first_bit_size_table, size_table);
	first_bit_size_bit_table++;
	first_bit_size_table++;

	size_table_see2[0] = size_table_see2[1] = size_table_see2[2] = size_table_see2[3] = size_table;
	size_bit_table_see2[0] = size_bit_table_see2[1] = size_bit_table_see2[2] = size_bit_table_see2[3] = size_bit_table;
}