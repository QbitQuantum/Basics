bool cmem::pop(cmem &in, uint32 size){
	in.realloc(size);
	in.pop(in.data, size);
	return true;
}