void copy_chunk_data(FILE *fin,
	const uint32_t chunk_index,  //[0, end) 标识为第几个Chunk
	FILE *fout,  
	int num,
	CMp4_root_box root
	)
{
	_fseeki64(fin, root.co[num].chunk_offset_from_file_begin[chunk_index],
		SEEK_SET);

	//获取当前chunk中有多少个sample
	uint32_t sample_num_in_cur_chunk_ = get_sample_num_in_cur_chunk(root.sc[num], chunk_index+1);  //@a mark获取chunk中sample的数目
	uint32_t sample_index_ =  get_sample_index(root.sc[num], chunk_index+1);//chunk中第一个sample的序号
	unsigned int cur=_ftelli64(fin);
	for(int i = 0; i < sample_num_in_cur_chunk_; i++)
	{
		uint32_t sample_size_ = get_sample_size(root.sz[num], sample_index_+i);//获取当前sample的大小
		_fseeki64(fin,cur,SEEK_SET);
		char *ptr=new char [sample_size_];
		fread(ptr, sample_size_, 1, fin);
		fwrite(ptr, sample_size_, 1, fout);
		delete [] ptr;
		cur+=sample_size_;
	}
}