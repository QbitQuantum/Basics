bool CTar32::readdir_TAR(CTar32FileStatus &stat)
{
	HEADER tar_header;
	if(!readTarHeader(tar_header))return false;

	//get tar format : GNU or POSIX
	int tar_format=tar_header.getFormat();

	// HP-UX's tar command create 100chars filename part. fixed on 2003.12.19
	char tmp_name[COUNTOF(tar_header.dbuf.name)+1];
	strncpy(tmp_name, tar_header.dbuf.name, COUNTOF(tar_header.dbuf.name));
	tmp_name[COUNTOF(tar_header.dbuf.name)] = '\0';
	stat.filename	=	tmp_name; /* tar_header.dbuf.name; */

	stat.original_size = parseOctNum(tar_header.dbuf.size,COUNTOF(tar_header.dbuf.size));
	if(tar_header.dbuf.typeflag == LNKTYPE){
		// Fixed on 2003/11/28. For "spencer_pwb.tar.gz". Thanks to rollo-san.
		stat.original_size = 0;
	}
	stat.blocksize  =   512;
	if(tar_header.dbuf.typeflag == LONGLINK){	// tar_header.dbuf.name == "././@LongLink"
		//NOTE:TAR32.DLL earlier than 2.33 makes LONGLINK entry with POSIX header
		tar_format=TAR_FORMAT_GNU;

		//char longfilename[2000] = "";
		std::vector<char> longfilename;
		size64 readsize = (size_t(stat.original_size-1)/512+1)*512;
		longfilename.resize((size_t)readsize+1);	//TODO:size lost
		size64 ret = m_pfile->read(&longfilename[0], readsize);
		if(ret == 0){
			throw CTar32Exception("can't get filename(LongLink)",ERROR_HEADER_BROKEN);
		}
		longfilename[(size_t)stat.original_size]='\0';	//TODO:size lost
		if(!readTarHeader(tar_header))return false;
		stat.filename = &longfilename[0];
		stat.original_size		=	parseOctNum(tar_header.dbuf.size, COUNTOF(tar_header.dbuf.size));
	}

	bool bPaxFilenameSupplied=false;
	time_t pax_atime=0,pax_ctime=0,pax_mtime=0;
	if(tar_header.dbuf.typeflag == PAX_GLOBAL || tar_header.dbuf.typeflag == PAX_ENTRTY){
		std::vector<char> content;
		size64 readsize = (size_t(stat.original_size-1)/512+1)*512;
		content.resize((size_t)readsize+1);	//TODO:size lost
		size64 ret = m_pfile->read(&content[0], readsize);
		if(ret == 0){
			throw CTar32Exception("can't get PAX Extended Global Header",ERROR_HEADER_BROKEN);
		}
		content[(size_t)stat.original_size]='\0';	//TODO:size lost
		if(!readTarHeader(tar_header))return false;
		stat.original_size		=	parseOctNum(tar_header.dbuf.size, COUNTOF(tar_header.dbuf.size));
		strncpy(tmp_name, tar_header.dbuf.name, COUNTOF(tar_header.dbuf.name));
		tmp_name[COUNTOF(tar_header.dbuf.name)] = '\0';
		stat.filename	=	tmp_name; /* tar_header.dbuf.name; */

		std::string extFilename;
		size64 filesize;
		if(!parsePaxExtHeader(&content[0],content.size(),extFilename,filesize,pax_atime,pax_ctime,pax_mtime)){
			if(tar_header.dbuf.typeflag == PAX_GLOBAL){
				throw CTar32Exception("Broken PAX Extended Global Header",ERROR_HEADER_BROKEN);
			}else{
				throw CTar32Exception("Broken PAX Extended Header",ERROR_HEADER_BROKEN);
			}
		}
		if(tar_header.dbuf.typeflag == PAX_GLOBAL){
			//global header
			//TODO:need test
			//if(filesize!=-1)m_currentfile_status.original_size=filesize;
		}else{
			//entry header
			//TODO:need test
			//if(filesize!=-1)stat.original_size=filesize;
			if(!extFilename.empty()){
				bPaxFilenameSupplied=true;
				stat.filename=extFilename;
			}
		}
	}

	//charset conversion
	if(m_archive_charset!=CHARSET_DONTCARE && !bPaxFilenameSupplied){
		if(m_archive_charset==CHARSET_UNKNOWN){
			//detect charset
			m_archive_charset=detect_charset(stat.filename.c_str());
		}

		switch(m_archive_charset){
		case CHARSET_EUCJP:
			stat.filename=CConvertCharsetHelper::getInstance().eucjp_to_sjis(stat.filename.c_str(),stat.filename.size());
			break;
		case CHARSET_UTF8N:	//FALLTHROUGH
		case CHARSET_UTF8:
			stat.filename=CConvertCharsetHelper::getInstance().utf8_to_sjis(stat.filename.c_str(),stat.filename.size());
			break;
		case CHARSET_JIS:
			//FALLTHROUGH
			/*
			 force to extract even if charset is not supported.
			 */
			//throw CTar32Exception("tar header charset error.",ERROR_NOT_SUPPORT);
			//break;
		case CHARSET_SJIS:	//FALLTHROUGH
		default:
			//nothing to do
			break;
		}
	}


	stat.mode		=   strtol(tar_header.dbuf.mode, NULL, 8);
	stat.uid		=   strtol(tar_header.dbuf.uid , NULL, 8);
	stat.gid		=   strtol(tar_header.dbuf.gid , NULL, 8);
	stat.mtime		=   strtol(tar_header.dbuf.mtime , NULL, 8);
	stat.chksum		=   strtol(tar_header.dbuf.chksum , NULL, 8);
	stat.typeflag	=   tar_header.dbuf.typeflag;
	stat.linkname	=	tar_header.dbuf.linkname;
	strncpy(stat.magic_version, tar_header.dbuf.magic,8);
	strncpy(stat.uname, tar_header.dbuf.uname, 32);
	strncpy(stat.gname, tar_header.dbuf.gname, 32);
	stat.devmajor	=   strtol(tar_header.dbuf.devmajor , NULL, 8);
	stat.devminor	=   strtol(tar_header.dbuf.devminor , NULL, 8);
	if(tar_format==TAR_FORMAT_GNU){
		stat.atime		=   strtol(tar_header.dbuf.exthead.gnu.atime , NULL, 8);
		stat.ctime		=   strtol(tar_header.dbuf.exthead.gnu.ctime , NULL, 8);
		stat.offset		=   parseOctNum(tar_header.dbuf.exthead.gnu.offset , COUNTOF(tar_header.dbuf.exthead.gnu.offset));
	}else{	//POSIX
		int length=min(COUNTOF(tar_header.dbuf.exthead.posix.prefix),strlen(tar_header.dbuf.exthead.posix.prefix));
		if(length>0){
			std::string prefix(tar_header.dbuf.exthead.posix.prefix,tar_header.dbuf.exthead.posix.prefix+length);

			stat.filename= prefix + '/' + stat.filename;
		}
	}

	if(pax_atime!=0)stat.atime=pax_atime;
	if(pax_ctime!=0)stat.ctime=pax_ctime;
	if(pax_mtime!=0)stat.mtime=pax_mtime;

	if(stat.typeflag == DIRTYPE){
		stat.mode &= ~_S_IFMT;
		stat.mode |= _S_IFDIR;
	}
	if((stat.mode & _S_IFMT) == _S_IFDIR){
		const char * f = stat.filename.c_str();
		if((char*)max(_mbsrchr((unsigned char*)f, '/'), _mbsrchr((unsigned char*)f,'\\')) != f+strlen(f)-1){
			stat.filename = stat.filename + "/";
		}
	}
	return true;
}