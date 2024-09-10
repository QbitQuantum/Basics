CMp4_trak_box CMp4_trak_box::mp4_read_trak_box(FILE *f, int size)
{
	printf("\t+%s\n", "trak");
	CMp4_trak_box trak;
	//trak  = new struct mp4_trak_box;
	trak.size= size;
	trak.type= ('t' | 'r'<<8 | 'a'<<16 | 'k'<<24);
	int k = 0;                                  \
	unsigned char p[5];                         \
	int inner_size = 0;

	int box_size= 0;
	unsigned int cur_pos= _ftelli64(f) ;
	do{
		_fseeki64(f, cur_pos, SEEK_SET);

		box_size= read_uint32_lit(f);
		fread(p, 4, 1, f);
		p[4]= 0;
		std::string name= (char*)p;
		if(name == "tkhd") {
			CMp4_tkhd_box tkhd;
			trak.tkhd= tkhd.mp4_read_tkhd_box(f, box_size);
		}
		else if(name == "mdia"){
			CMp4_mdia_box mdia;
			trak.mdia= mdia.mp4_read_mdia_box(f, box_size);
		} 
		cur_pos    += box_size;
		inner_size += box_size;
	} while(inner_size+8 < size);

	return trak;
}