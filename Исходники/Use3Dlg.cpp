void CUse3Dlg::OnBnClickedButton6()		// 智能指针的释放
{
	::CoInitialize( NULL );		// 如果在这里进行 COM 初始化，要注意智能指针的释放

	CComQIPtr < IFun, &IID_IFun > spFun;

	HRESULT hr = spFun.CoCreateInstance( CLSID_Fun );
	ASSERT( SUCCEEDED( hr ) );
	// 为了简单起见，不再使用 if 判断 HRESULT 了。IFun::Add() 也没有调用

	CComBSTR s1( "Hello" ), s2( " world" ), s3;
	hr = spFun->Cat( s1, s2, &s3 );
	ASSERT( SUCCEEDED( hr ) );
	CString sMsg( s3 );
	AfxMessageBox( sMsg );

//	spFun->Release();	// 大错特错！！！
	spFun.Release();	// 正解

	::CoUninitialize();
}