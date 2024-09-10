std::wstring wstringOf( const void* lpvEStr , int iESize ) 
	//	ワイドかマルチバイトか分からない文字列をワイド文字列に変換します
{
	if ( IsTextUnicode( (CONST LPVOID)lpvEStr , iESize , NULL ) ){
		return( wstringOf( (LPCWSTR)lpvEStr ) );
	}
	return ( wstringOf( (LPCSTR)lpvEStr ) ) ;
}