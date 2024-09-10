// Move constructor
ColumnBundle::ColumnBundle(ColumnBundle&& Y)
{	std::swap(ncols, Y.ncols);
	std::swap(col_length, Y.col_length);
	std::swap(qnum, Y.qnum);
	std::swap(basis, Y.basis);
	memMove((ManagedMemory&&)Y); //cannibalize Y's data
}