	bool Close(bool success=false)
	{
		void* mem;
		size_t size, offset_ctrl, offset_data;
		int bzerror;
		if(_bzpatch) BZ2_bzWriteClose(&bzerror, _bzpatch, 0, NULL, NULL);
		if(_stub) fclose(_stub);

		if(success)
		{
			//
			if(!ReadFile(_stubname.c_str(), mem, size)) return false;
			fseek(_patch, 0, SEEK_END);
			offset_data = ftell(_patch);
			fwrite(mem, 1, size, _patch);
			free(mem);

			//
			offset_ctrl = 16;
			fseek(_patch, 8, SEEK_SET);
			fwrite(&offset_ctrl, 1, 4, _patch);
			fwrite(&offset_data, 1, 4, _patch);
			if(_unlink(_stubname.c_str())!=0) return false;
		}

		if(_patch) fclose(_patch);
		_patch = NULL;
		_bzpatch = NULL;
		_stub = NULL;
		return true;
	}