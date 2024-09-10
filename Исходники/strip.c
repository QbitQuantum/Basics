 ////////////////////////////////////////////////////////////
// Strip_Setup : Sizes and masks the strip and loads the skin
/// ARGS ////////////////////////////////////////////////////
// dlg : Handle of the window to apply all this to
void Strip_Setup(HWND dlg){
	unsigned char i=0,q=0,r=0;
	unsigned int hky=0;
	HBITMAP bmp;
	HRGN rgn;
//
// Get the number of rows
	if(vr.btns%cf.cols){
		vr.rows=(vr.btns/cf.cols)+1;
	}else{vr.rows=vr.btns/cf.cols;}
// Size the window
	if(vr.btns>cf.cols){ // Calculate row count
		vr.rct.right=mx.arx+(cf.cols*mx.bnx);
		vr.rct.bottom=mx.iny+(mx.bny*vr.rows);
	}else{ // 1 row
		vr.rct.right=mx.arx+(vr.btns*mx.bnx);
		vr.rct.bottom=mx.bny+mx.iny;
	}
// Mask out the un-needed part
	rgn=CreateRectRgn(0,0,vr.rct.right,vr.rct.bottom);
	CombineRgn(rgn,rgn,CreateRectRgn(0,mx.ary,mx.arx,vr.rct.bottom),RGN_DIFF);
	if(vr.btns>cf.infw&&cf.cols>cf.infw){ // Only mask out the info section if there is space to hide
		CombineRgn(rgn,rgn,CreateRectRgn(0,vr.rct.bottom-mx.iny,vr.rct.right-(mx.bnx*cf.infw),vr.rct.bottom),RGN_DIFF);
	}
	SetWindowRgn(dlg,rgn,1);
// Move to the right side
	Strip_Position(dlg);
// Load the theme stuff
	// Skin
	vr.gfx=CreateCompatibleDC(GetDC(dlg));
/*
 *  The code below creates a memory leak
 * \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/
 */
	if(Bio_IsFile(cf.skin)){
		bmp=LoadImage(GetModuleHandle(0),cf.skin,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	}else{bmp=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(BMP_GFX));}
	DeleteObject(SelectObject(vr.gfx,bmp));
	DeleteObject(bmp);
	// Font
	DeleteObject(SelectObject(GetDC(dlg),CreateFont(mx.txt,0,0,0,(mx.txa&KS_TXA_BOLD)?FW_BOLD:0,(mx.txa&KS_TXA_ITALIC)?1:0,0,0,0,0,0,0,0,cf.fnt)));
/*
 * /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\
 *  The code above creates a memory leak
 */
	SetTextColor(GetDC(dlg),mx.txc);
	SetBkMode(GetDC(dlg),TRANSPARENT);
	SetStretchBltMode(GetDC(dlg),HALFTONE);
// Create buttons
	vr.arw=CreateWindow("bncls","Arrow",WS_VISIBLE|WS_CHILD,0,0,mx.arx,mx.ary,dlg,0,GetModuleHandle(0),0);
	for(i=0;i<vr.btns;i++){
		itm[i].wnd=CreateWindow("bncls","Button",WS_VISIBLE|WS_CHILD,mx.arx+(mx.bnx*q),mx.bny*r,mx.bnx,mx.bny,dlg,0,GetModuleHandle(0),0);
		q++;if(q>=cf.cols){r++;q=0;}
	}
// Set hotkey
	if(cf.disp==KS_DSP_KEY){
		// Translate the modifier key types
		if(HIBYTE(cf.hkey)&HOTKEYF_ALT){hky|=MOD_ALT;}
		if(HIBYTE(cf.hkey)&HOTKEYF_SHIFT){hky|=MOD_SHIFT;}
		if(HIBYTE(cf.hkey)&HOTKEYF_CONTROL){hky|=MOD_CONTROL;}
		RegisterHotKey(dlg,1,hky,LOBYTE(cf.hkey));
	}
}