bool HashMap::add(const char * name, void * value) {
	
	string lname = name;
	transform(lname.begin(), lname.end(), lname.begin(), tolower);
	
	if(fill >= (size * 3) / 4) {
		// TODO recreate the table
		//size <<= 1;
		//mask = size - 1;
		//data = (Entry *)realloc(data, size * sizeof(Entry));
		return false;
	}
	
	size_t hash = getHash(lname.c_str());
	size_t h1 = FuncH1(hash);
	size_t h2 = FuncH2(hash);
	
	for(size_t i = 0; i < size; i++) {
		
		h1 &= mask;
		
		if (!data[h1].name) {
			data[h1].name = strdup(lname.c_str());
			data[h1].value = value;
			assert(data[h1].name);
			fill++;
			return true;
		}
		
		h1 += h2;
	}
	
	return false;
}