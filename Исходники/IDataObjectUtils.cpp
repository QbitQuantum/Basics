HRESULT IDataObjectUtils::STGMEDIUMToDataBlock(const STGMEDIUM & med, pfc::array_t<t_uint8> & out) {
	switch(med.tymed) {
		case TYMED_HGLOBAL:
			{
				CGlobalLockScope lock(med.hGlobal);
				out.set_data_fromptr( (const t_uint8*) lock.GetPtr(), lock.GetSize() );
			}
			return S_OK;
		case TYMED_ISTREAM:
			{
				HRESULT state;
				IStream * stream = med.pstm;
				LARGE_INTEGER offset = {};
				STATSTG stats = {};
				if (FAILED( state = stream->Stat(&stats,STATFLAG_NONAME ) ) ) return state;
				t_size toRead = pfc::downcast_guarded<t_size>(stats.cbSize.QuadPart);
				out.set_size(toRead);
				if (FAILED( state = stream->Seek(offset,STREAM_SEEK_SET,NULL) ) ) return state;
				ULONG cbRead = 0;
				if (FAILED( state = stream->Read(out.get_ptr(), pfc::downcast_guarded<ULONG>(toRead), &cbRead) ) ) return state;
				if (cbRead != toRead) return E_UNEXPECTED;
			}
			return S_OK;
		default:
			return DV_E_TYMED;
	}
}