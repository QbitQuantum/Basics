		int64_t CoreIOReader::Length()
		{
			CoreAssert(this != NULL);
			CoreAssert(IsOpen());

#ifndef __GNUC__
			MutexHolder mh(&m_ioMutex);
#endif

#ifdef HAS_FPOS64
			fpos64_t lastpos, endpos;
#if defined(TARGET_COMPILER_VC) || defined(TARGET_COMPILER_BORLAND) || \
	(defined(TARGET_COMPILER_ICC) && defined(TARGET_OS_WINDOWS))
			lastpos = _ftelli64(m_fileInputPointer);
			_fseeki64(m_fileInputPointer, 0, SEEK_END);
			endpos = _ftelli64(m_fileInputPointer);
			_fseeki64(m_fileInputPointer, lastpos, SEEK_SET);
#elif defined (TARGET_OS_MACOSX) || defined (TARGET_OS_NETBSD) || \
	  defined (TARGET_OS_FREEBSD) || defined (TARGET_OS_OPENBSD) || \
      defined (TARGET_COMPILER_MINGW)
			fgetpos(m_fileInputPointer, &lastpos);
			fseek(m_fileInputPointer, 0, SEEK_END);
			fgetpos(m_fileInputPointer, &endpos);
			fsetpos(m_fileInputPointer, &lastpos);
#else
			fgetpos64(m_fileInputPointer, &lastpos);
			fseeko64(m_fileInputPointer, 0, SEEK_END);
			fgetpos64(m_fileInputPointer, &endpos);
			fsetpos64(m_fileInputPointer, &lastpos);
#endif
#else
			fpos_t lastpos, endpos;
			lastpos = ftell(m_fileInputPointer);
			fseek(m_fileInputPointer, 0, SEEK_END);
			endpos = ftell(m_fileInputPointer);
			fseek(m_fileInputPointer, lastpos, SEEK_SET);
#endif

#if defined (TARGET_OS_WINDOWS) || defined (TARGET_OS_MACOSX) || defined (TARGET_OS_FREEBSD) || \
			defined (TARGET_OS_NETBSD) || defined (TARGET_OS_OPENBSD) || defined (TARGET_COMPILER_CYGWIN) || \
			defined (TARGET_OS_NDSFIRMWARE)
			return endpos;
#elif defined (TARGET_OS_LINUX)
			return endpos.__pos;
#endif
		}