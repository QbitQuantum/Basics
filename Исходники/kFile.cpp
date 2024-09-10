		void kFile::printf(const char* format, ...)const
		{
			va_list args;
			va_start( args, format );
			vfprintf_s(mp_Fp,format,args);
			va_end( args );
		}