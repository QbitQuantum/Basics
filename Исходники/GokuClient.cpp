static int split_next(const wstring &src, wstring &des, char ch, int start){
	int pos = 0;
	pos = src.find(ch, start);
	des.clear();
	if(pos < start){
		pos = src.length();
	}
	if(pos > start){
		des.assign(src, start, pos - start);
	}
	return pos;
}