// 读取PAL文件转换为RGB并显示
void CRGB2YUVView::OnReadPAL() 
{
	// TODO: Add your command handler code here
	CDC *pDC = GetDC();
	CRect rect;
	CBrush brush(RGB(128,128,128));
	GetClientRect(&rect);
	pDC->FillRect(&rect, &brush);

	// PAL 720x576 : 中国的电视标准为PAL制	
	int CurrentXRes = 720;
	int CurrentYRes = 576;
	int size        = CurrentXRes * CurrentYRes;
    
	// 分配内存
	byte *Video_Field0 = (byte*)malloc(CurrentXRes*CurrentYRes);  
	byte *Video_Field1 = (byte*)malloc(CurrentXRes*CurrentYRes);

	// 保存内存指针
	byte *Video_Field0_ = Video_Field0;
	byte *Video_Field1_ = Video_Field1;

	// 初始化内存
	ZeroMemory(Video_Field0, CurrentXRes*CurrentYRes);
	ZeroMemory(Video_Field1, CurrentXRes*CurrentYRes);

	byte yuv_y0, yuv_u0, yuv_v0; // yuv_v1;  // {y0, u0, v0, v1};
	byte r, g, b;
	byte bufRGB[3];  // 临时保存{R,G,B}
	byte bufYUV[3];  // 临时保存{Y,U,V}
	
	// 初始化数组空间
	memset(bufRGB,0, sizeof(byte)*3); 
	memset(bufYUV,0, sizeof(byte)*3); 
    
    char strFileName[MAX_PATH]="720bmp.pal";
 
    // 分配图片像素内存
    RGBTRIPLE *rgb;
	rgb = new RGBTRIPLE[CurrentXRes*CurrentYRes];

	memset(rgb,0, sizeof(RGBTRIPLE)*CurrentXRes*CurrentYRes); // 初始化内存空间

	CFile* f;
	f = new CFile();
	f->Open(strFileName, CFile::modeRead);
	f->SeekToBegin();
	f->Read(Video_Field0, CurrentXRes*CurrentYRes);
	f->Read(Video_Field1, CurrentXRes*CurrentYRes);

	// 上场  (1,3,5,7...行)
	for ( int i = CurrentYRes-1; i>=0; i--) {
		for ( int j = 0; j<CurrentXRes; j++) {
			if(!(i%2)==0) 
			{
				// UYVY标准  [U0 Y0 V0 Y1] [U1 Y2 V1 Y3] [U2 Y4 V2 Y5] 每像素点两个字节，[内]为四个字节 
				if ((j%2)==0) 
				{
					yuv_u0 = *Video_Field0;  
					Video_Field0++;
				} 
				else
				{
					yuv_v0 = *Video_Field0;  
					Video_Field0++;
				}
				yuv_y0 = *Video_Field0;      
				Video_Field0++;

				bufYUV[0] = yuv_y0;  //	Y
				bufYUV[1] = yuv_u0;  // U
				bufYUV[2] = yuv_v0;  // V

				// RGB转换为YUV
				YUV2RGB(bufRGB,bufYUV);
				r = bufRGB[0];   // y
				g = bufRGB[1];   // u
				b = bufRGB[2];   // v
				if (r>255) r=255; if (r<0) r=0;
				if (g>255) g=255; if (g<0) g=0;
				if (b>255) b=255; if (b<0) b=0;

				for (int k=0; k<1000; k++) ;  //延时
				// 视图中显示
				pDC->SetPixel(j, CurrentYRes-1-i, RGB(r, g, b));

			}// end if i%2
		}
	}

    // 下场 (2,4,6,8...行)
	for ( int i_ = CurrentYRes-1; i_>=0; i_--) {
		for ( int j_ = 0; j_<CurrentXRes; j_++) {
			if((i_%2)==0) 
			{
				// UYVY标准  [U0 Y0 V0 Y1] [U1 Y2 V1 Y3] [U2 Y4 V2 Y5] 每像素点两个字节，[内]为四个字节 
				if ((j_%2)==0) 
				{
					yuv_u0 = *Video_Field1;  
					Video_Field1++;
				} 
				else
				{
					yuv_v0 = *Video_Field1;  
					Video_Field1++;
				}
				yuv_y0 = *Video_Field1;      
				Video_Field1++;

				bufYUV[0] = yuv_y0;  //	Y
				bufYUV[1] = yuv_u0;  // U
				bufYUV[2] = yuv_v0;  // V

				// RGB转换为YUV
				YUV2RGB(bufRGB,bufYUV);
				r = bufRGB[0];   // y
				g = bufRGB[1];   // u
				b = bufRGB[2];   // v
				if (r>255) r=255; if (r<0) r=0;
				if (g>255) g=255; if (g<0) g=0;
				if (b>255) b=255; if (b<0) b=0;

				for (int k=0; k<1000; k++) ;  //延时
				// 视图中显示
				pDC->SetPixel(j_, CurrentYRes-1-i_, RGB(r, g, b));
			}
		}
	}
	
	// 提示完成
	char buffer[80];
	sprintf(buffer,"完成读取PAL文件：%s ", strFileName);
	MessageBox(buffer, "提示信息", MB_OK | MB_ICONINFORMATION);

    // 关闭PAL电视场文件
	f->Close();
	// WriteYUV(Video_Field0_, Video_Field1_, size);
	
	// 释放内存
	free( Video_Field0_ ); 
	free( Video_Field1_ );
	delete f;
	delete rgb;
}