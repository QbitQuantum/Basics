bool HashTableT<Key_t, Val_t>::load ( char* filename , char **tbuf , long *tsize ) {
	reset();
	File f;
	f.set ( filename );
	if ( ! f.doesExist() ) return true;
	log(LOG_INFO,"admin: Loading hashtable from %s",filename);
	if ( ! f.open ( O_RDONLY) ) return false;
	long numSlots;
	long numSlotsUsed;
	long off = 0;
	if ( ! f.read ( &numSlots     , 4 , off ) ) return false;
	off += 4;
	if ( ! f.read ( &numSlotsUsed , 4 , off ) ) return false;
	off += 4;
	if ( ! setTableSize ( numSlots , NULL , 0 ) ) return false;
	long ks = sizeof(Key_t);
	long vs = sizeof(Val_t);
	// corruption check
	if ( f.getFileSize() < ks * numSlots + vs * numSlots - 8 ) return false;
	if ( ! f.read ( m_keys        , numSlots * ks , off ) ) return false;
	off += numSlots * ks;
	if ( ! f.read ( m_vals        , numSlots * vs , off ) ) return false;
	off += numSlots * vs;
	m_numSlotsUsed = numSlotsUsed;
	// done if no text buf
	if ( ! tbuf ) { f.close(); return true; }
	// read in the tbuf size, next 4 bytes
	if ( ! f.read (  tsize     , 4 , off ) ) return false;
	off += 4;
	// alloc mem for reading in the contents of the text buf
	*tbuf = (char *)mmalloc ( *tsize , "HTtxtbuf" );
	if ( ! *tbuf ) return false;
	// read in the contents of the text buf
	if ( ! f.read ( *tbuf     , *tsize , off ) ) return false;
	off += *tsize;
	// close the file, we are done
	f.close();
	return true;
}