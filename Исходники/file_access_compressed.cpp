void FileAccessCompressed::close(){

	if (!f)
		return;


	if (writing) {
		//save block table and all compressed blocks

		CharString mgc = magic.utf8();
		f->store_buffer((const uint8_t*)mgc.get_data(),mgc.length()); //write header 4
		f->store_32(cmode); //write compression mode 4
		f->store_32(block_size); //write block size 4
		f->store_32(write_max); //max amount of data written 4
		int bc=(write_max/block_size)+1;

		for(int i=0;i<bc;i++) {
			f->store_32(0); //compressed sizes, will update later
		}


		Vector<int> block_sizes;
		for(int i=0;i<bc;i++) {

			int bl = i==(bc-1) ? write_max % block_size : block_size;
			uint8_t *bp = &write_ptr[i*block_size];

			Vector<uint8_t> cblock;
			cblock.resize(Compression::get_max_compressed_buffer_size(bl,cmode));
			int s = Compression::compress(cblock.ptr(),bp,bl,cmode);

			f->store_buffer(cblock.ptr(),s);
			block_sizes.push_back(s);
		}

		f->seek(16); //ok write block sizes
		for(int i=0;i<bc;i++)
			f->store_32(block_sizes[i]);
		f->seek_end();
		f->store_buffer((const uint8_t*)mgc.get_data(),mgc.length()); //magic at the end too

		buffer.clear();

	} else {


		comp_buffer.clear();
		buffer.clear();
		read_blocks.clear();
	}

	memdelete(f);
	f=NULL;

}