inline RETCODE RecordFileScan::OpenScan (const RecordFilePtr & fileHandle, AttrType attrType, size_t attrLength, size_t attrOffset, CompOp compOp, void * value) {
	
	if ( _scanInfo.state == Open )
		return RETCODE::INVALIDSCAN;

	_recFile = fileHandle;

	if ( fileHandle == nullptr || !fileHandle->isValidRecordFile ( ) )
		return RETCODE::INVALIDPAGEFILE;

	RecordFile::RecordFileHeader header;

	_recFile->GetHeader (header);

	if ( value != nullptr ) {			// has condition

		if ( attrType != AttrType::INT && attrType != AttrType::FLOAT && attrType != AttrType::STRING )
			return INVALIDSCAN;

		if ( attrOffset + attrLength > header.recordSize || attrOffset < 0 )
			return RETCODE::INVALIDSCAN;

		switch ( compOp ) {
		case EQ_OP:
			_comp = CompMethod::equal;
			break;
		case LT_OP:
			_comp = CompMethod::less_than;
			break;
		case GT_OP:
			_comp = CompMethod::greater_than;
			break;
		case LE_OP:
			_comp = CompMethod::less_than_or_eq_to;
			break;
		case GE_OP:
			_comp = CompMethod::greater_than_or_eq_to;
			break;
		case NE_OP:
			_comp = CompMethod::not_equal;
			break;
		case NO_OP:
			_comp = nullptr;
			break;
		default:
			return RETCODE::INVALIDSCAN;
			break;
		}

		_attrType = attrType;

		_attrLength = attrLength;

		_attrOffset = attrOffset;

		if ( ( attrType == AttrType::INT || attrType == AttrType::FLOAT ) && attrLength != 4 )
			return RETCODE::INVALIDSCAN;

		_attrValue = shared_ptr<void> (reinterpret_cast< void* >( new char[attrLength] ( ) ));

		memcpy_s (_attrValue.get ( ), attrLength, value, attrLength);

	} 

	// initialize the status
	_scanInfo.state = Open;
	_scanInfo.recordsCount = header.recordSize;
	_scanInfo.scanedPage = BeginPage;
	_scanInfo.scanedSlot = 0;
	
	_curPage = nullptr;

	return RETCODE::COMPLETE;
}