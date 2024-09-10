/*-------------------------------------------
	main関数
--------------------------------------------*/
int wmain(int argc, WCHAR* argv[])
{
	HRESULT hr;

	// ロケールを設定
	_wsetlocale(LC_ALL, L"Japanese");

	// **********************************************************
	// Direct3D11デバイスの作成
	hr = CreateDevice();

	// **********************************************************
	// コンピュート・シェーダの作成
	if (SUCCEEDED(hr))
		hr = CreateShader();

	// **********************************************************
	// 定数バッファの作成
	if (SUCCEEDED(hr))
		hr = CreateCBuffer();

	// **********************************************************
	// リソースの作成
	if (SUCCEEDED(hr))
		hr = CreateResource();

	// **********************************************************
	// シェーダ リソース ビューの作成
	if (SUCCEEDED(hr))
		hr = CreateSRV();

	// **********************************************************
	// アンオーダード・アクセス・ビューの作成
	if (SUCCEEDED(hr))
		hr = CreateUAV();

	// **********************************************************
	// コンピュート・シェーダを使った演算
	if (SUCCEEDED(hr))
		ComputeShader();

	// **********************************************************
	// 開放
	SAFE_RELEASE(g_pUAV[1]);
	SAFE_RELEASE(g_pUAV[0]);
	SAFE_RELEASE(g_pSRV[1]);
	SAFE_RELEASE(g_pSRV[0]);
	SAFE_RELEASE(g_pReadBackBuffer);
	SAFE_RELEASE(g_pBuffer[1]);
	SAFE_RELEASE(g_pBuffer[0]);
	SAFE_RELEASE(g_pCBuffer);
	SAFE_RELEASE(g_pComputeShader);
	SAFE_RELEASE(g_pImmediateContext);
	SAFE_RELEASE(g_pD3DDevice);

	return 0;
}