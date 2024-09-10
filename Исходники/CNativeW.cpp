void CNativeW::Replace( const wchar_t* pszFrom, int nFromLen, const wchar_t* pszTo, int nToLen )
{
	CNativeW	cmemWork;
	int			nBgnOld = 0;
	int			nBgn = 0;
	while( nBgn <= GetStringLength() - nFromLen ){
		if( 0 == wmemcmp( &GetStringPtr()[nBgn], pszFrom, nFromLen ) ){
			if( nBgnOld == 0 && nFromLen <= nToLen ){
				cmemWork.AllocStringBuffer( GetStringLength() );
			}
			if( 0  < nBgn - nBgnOld ){
				cmemWork.AppendString( &GetStringPtr()[nBgnOld], nBgn - nBgnOld );
			}
			cmemWork.AppendString( pszTo, nToLen );
			nBgn = nBgn + nFromLen;
			nBgnOld = nBgn;
		}else{
			nBgn++;
		}
	}
	if( nBgnOld != 0 ){
		if( 0  < GetStringLength() - nBgnOld ){
			cmemWork.AppendString( &GetStringPtr()[nBgnOld], GetStringLength() - nBgnOld );
		}
		SetNativeData( cmemWork );
	}else{
		if( this->GetStringPtr() == NULL ){
			this->SetString(L"");
		}
	}
}