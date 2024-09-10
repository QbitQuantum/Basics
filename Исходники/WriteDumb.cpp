// -----------------------------------------------------------------------------------
// Compress a binary dump file (beginning at offset head_size)
void CompressBinaryDump(const char* file, unsigned int head_size)
{
	// for simplicity ... copy the file into memory again and compress it there
	FILE* p = fopen(file,"r");
	fseek(p,0,SEEK_END);
	const uint32_t size = ftell(p);
	fseek(p,0,SEEK_SET);

	if (size<head_size) {
		fclose(p);
		return;
	}

	uint8_t* data = new uint8_t[size];
	fread(data,1,size,p);

	uLongf out_size = (uLongf)((size-head_size) * 1.001 + 12.);
	uint8_t* out = new uint8_t[out_size];

	compress2(out,&out_size,data+head_size,size-head_size,9);
	fclose(p);
	p = fopen(file,"w");

	fwrite(data,head_size,1,p);
	fwrite(&out_size,4,1,p); // write size of uncompressed data
	fwrite(out,out_size,1,p);

	fclose(p);
	delete[] data;
	delete[] out;
}