/* untuk mengubah panjang suatu file, biasa digunakan saat penulisan pertama */
int simple_truncate(const char* path, off_t size){
	// cari file
	int index;
	try{
		index = searchFile(path);
	}catch(int e){
		return e;
	}
	
	if (index < 0){
		return -ENOENT;
	}
	
	// jika ukuran lebih dari 100 byte, error file too big
	if (size > 100){
		return -EFBIG;
	}
	
	// update ukuran slot
	filesystem.files[index].size = size;
	filesystem.writeFile(index);
	
	return 0;
}