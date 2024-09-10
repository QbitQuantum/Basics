U1 MIOSystem::LoadFile( FileInfo& info,STD_VECTOR<U8>& data )
{

	

	data.resize(info.compressize);
	LARGE_INTEGER fpos;
	fpos.QuadPart	=	info.offset;
	LARGE_INTEGER oldpos;
	m_CSRead.Enter();
	HANDLE h = GetFileReadHandle(info.idx&0xffff);
	if(h==NULL){
		m_CSRead.Leave();
		return false;
	}
	SetFilePointerEx(h,fpos,&oldpos,FILE_BEGIN);
	DWORD dwRead=0;
	ReadFile(h,&data[0],info.compressize,&dwRead,NULL);
	m_CSRead.Leave();
	return true;
}