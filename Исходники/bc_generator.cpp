int BC_GEN::findPos(const QChar &bc)
{
	for(int index=0;index<(CODE39_SIZE);++index)
		if(bc.toUpper().toLatin1()==code39_table[index])
			return index;
	return -1;
}