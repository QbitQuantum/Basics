int EmdMaxExporter::DoExport( const MCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts/* =FALSE */, DWORD options/* =0 */ )
{

	typedef int(*ExportFunc)( const MCHAR*, ExpInterface*, Interface*, BOOL, DWORD );

	// Get full path of .dll which shares same path with .dle
	TCHAR binFullPath[_MAX_PATH];
	TCHAR szDrive[_MAX_DRIVE] = { 0 },
		  szDir[_MAX_DIR] = { 0 },
		  szFNAME[_MAX_FNAME] = { 0 },
		  szExt[_MAX_EXT] = { 0 };

	GetModuleFileName( hInstance, binFullPath, sizeof(binFullPath) );

#ifdef UNICODE
	_wsplitpath( binFullPath, szDrive, szDir, NULL, NULL );
#else
	_splitpath( binFullPath, szDrive, szDir, NULL, NULL );
#endif

	TCHAR dllFullPath[_MAX_PATH] = { 0 };

#ifdef UNICODE

	wcscat( dllFullPath, szDrive );
	wcscat( dllFullPath, szDir );
#ifdef _DEBUG
	wcscat( dllFullPath, _T("EmdExporterMax2011_d.dll") );
#else
	wcscat( dllFullPath, _T("EmdExporterMax2011.dll") );
#endif	// #ifdef DEBUG

#else

	strcat( dllFullPath, szDrive );
	strcat( dllFullPath, szDir );
#ifdef _DEBUG
	strcat( dllFullPath, _T("EmdExporterMax2011_d.dll") );
#else
	strcat( dllFullPath, _T("EmdExporterMax2011.dll") );
#endif	// #ifdef DEBUG

#endif	// #ifdef UNICODE

	// Load exporter dll here and do the export
	HINSTANCE hDLL;
	hDLL = LoadLibrary( dllFullPath );

	ExportFunc exportFunc = (ExportFunc)GetProcAddress( hDLL, "DoExport" );

	// well, we don't have a DoExport method...
	if ( !exportFunc ) return FALSE;

	BOOL result = (*exportFunc)( name, ei, i, suppressPrompts, options );

	FreeLibrary( hDLL );

	return result;
}