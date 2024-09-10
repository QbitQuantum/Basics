bool Criterion::look(File& file){
	int size;
	Comparator com (op);
	if(attribute=="size"){

		std::istringstream ss(value);
		ss>>size;
		return  com( file.getFileSize(),size);
	}