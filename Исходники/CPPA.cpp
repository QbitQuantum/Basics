/*! ユーザー定義関数のエラーメッセージの作成

	stdProc, stdIntFunc, stdStrFunc がエラーコードを返した場合、PPAから呼び出される。
	異常終了/不正引数時のエラーメッセージを独自に指定する。
	@author Moca
	@param Err_CD IN  0以外各コールバック関数が設定した値
			 1以上 FuncID + 1
			 0     PPAのエラー
			-1以下 その他ユーザ定義エラー
	@param Err_Mes IN エラーメッセージ

	@date 2003.06.01 Moca
*/
void __stdcall CPPA::stdError( int Err_CD, const char* Err_Mes )
{
	if( false != m_CurInstance->m_bError ){
		return;
	}
	m_CurInstance->m_bError = true; // 関数内で関数を呼ぶ場合等、2回表示されるのを防ぐ

	TCHAR szMes[2048]; // 2048あれば足りるかと
	const TCHAR* pszErr;
	pszErr = szMes;
	if( 0 < Err_CD ){
		int i, FuncID;
		FuncID = Err_CD - 1;
		char szFuncDec[1024];
		szFuncDec[0] = '\0';
		for( i = 0; CSMacroMgr::m_MacroFuncInfoCommandArr[i].m_nFuncID != -1; i++ ){
			if( CSMacroMgr::m_MacroFuncInfoCommandArr[i].m_nFuncID == FuncID ){
				GetDeclarations( CSMacroMgr::m_MacroFuncInfoCommandArr[i], szFuncDec );
				break;
			}
		}
		if( CSMacroMgr::m_MacroFuncInfoArr[i].m_nFuncID != -1 ){
			for( i = 0; CSMacroMgr::m_MacroFuncInfoArr[i].m_nFuncID != -1; i++ ){
				if( CSMacroMgr::m_MacroFuncInfoArr[i].m_nFuncID == FuncID ){
					GetDeclarations( CSMacroMgr::m_MacroFuncInfoArr[i], szFuncDec );
					break;
				}
			}
		}
		if( szFuncDec[0] != '\0' ){
			auto_sprintf( szMes, LS(STR_ERR_DLGPPA2), szFuncDec );
		}else{
			auto_sprintf( szMes, LS(STR_ERR_DLGPPA3), FuncID );
		}
	}else{
		//	2007.07.26 genta : ネスト実行した場合にPPAが不正なポインタを渡す可能性を考慮．
		//	実際には不正なエラーは全てPPA.DLL内部でトラップされるようだが念のため．
		if( IsBadStringPtrA( Err_Mes, 256 )){
			pszErr = LS(STR_ERR_DLGPPA6);
		}else{
			switch( Err_CD ){
			case 0:
				if( '\0' == Err_Mes[0] ){
					pszErr = LS(STR_ERR_DLGPPA4);
				}else{
					pszErr = to_tchar(Err_Mes);
				}
				break;
			default:
				auto_sprintf( szMes, LS(STR_ERR_DLGPPA5), Err_CD, to_tchar(Err_Mes) );
			}
		}
	}
	if( 0 == m_CurInstance->m_cMemDebug.GetStringLength() ){
		MYMESSAGEBOX( m_CurInstance->m_pcEditView->GetHwnd(), MB_OK, LS(STR_ERR_DLGPPA7), _T("%ts"), pszErr );
	}
	else{
		MYMESSAGEBOX( m_CurInstance->m_pcEditView->GetHwnd(), MB_OK, LS(STR_ERR_DLGPPA7), _T("%ts\n%hs"), pszErr, m_CurInstance->m_cMemDebug.GetStringPtr() );
	}
}