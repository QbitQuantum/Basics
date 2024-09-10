int chmod_( BBString *path,int mode ){
	if( _bbusew ) return _wchmod( bbTmpWString(path),mode );
	return _chmod( bbTmpCString(path),mode );
}