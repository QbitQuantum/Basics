int CBgDisp2::CheckMultiTexOk( LPDIRECT3DDEVICE9 pd3ddev )
{

	HRESULT hr;
	D3DCAPS9 caps8;
	hr = pd3ddev->GetDeviceCaps( &caps8 );
	if( hr != D3D_OK ){
		DbgOut( "bgdisp2 : checkmultitexok : GetDeviceCaps error !!!\n" );
		_ASSERT( 0 );
		return 1;
	}

	WORD maxtexblendnum = (WORD)( caps8.FVFCaps & D3DFVFCAPS_TEXCOORDCOUNTMASK );
	DWORD maxstages = caps8.MaxTextureBlendStages;
	DWORD maxsimu = caps8.MaxSimultaneousTextures;
	DWORD modu = caps8.TextureOpCaps & D3DTEXOPCAPS_MODULATE;

	DbgOut( "bgdisp2 : CheckMultiTexOk : caps : maxtexcoord %d, maxstages %d, maxsimu %d, moduleop %d\n", maxtexblendnum, maxstages, maxsimu, modu );

	if( (maxtexblendnum >= 2) && (maxstages >= 2) && (maxsimu >= 2) && (modu > 0) ){
		multitexok = 1;
	}else{
		multitexok = 0;
	}


	DbgOut( "bgdisp2 : multitexok %d\n", multitexok );


	return 0;
}