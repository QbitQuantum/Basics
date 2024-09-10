int DjvuPic::SetBuffer(CString& fullName,bool check)
{	
	int err=ERR_OK;

	Buffer->Destroy(); 
	Buffer->Create(Parent, Foreground->INFO.bmiHeader.biWidth, Foreground->INFO.bmiHeader.biHeight, 8); 
	Buffer->CreateGrayPallete();			
	CImage TT; TT.Load(FrgFile); TT.BitBlt(Buffer->GetDC(),0,0);
	return err;
}