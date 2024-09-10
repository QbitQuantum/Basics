		MemUnzip*		MemUnzip::fromFile(const wcs& filepath)
		{
			FILE* fp=NULL;
			_wfopen_s(&fp,filepath.c_str(),L"rb");
			if(!fp)
				return NULL;
			MemUnzip* unzip=new MemUnzip(_filelength(_fileno(fp)));
			int ret=0;
			if(unzip->_buffer.size())
				ret=(int)fread(&unzip->_buffer[0],unzip->_buffer.size(),1,fp);
			fclose(fp);

			if(ret!=1)
			{
				delete unzip;
				return NULL;
			}

			unzip->__init(unzip->__openUnzip("1"));

			return unzip;
		}