void TcodecsPage::init(void)
{
 cfg2dlg();
 enableWindow(IDC_CHB_XVID,config.isLibavcodec || config.isXviD);enableWindow(IDC_CHB_XVID_XVID,config.isXviD);
 enableWindow(IDC_CHB_DIV3,config.isLibavcodec);
 enableWindow(IDC_CHB_DIVX,config.isLibavcodec || config.isXviD);enableWindow(IDC_CHB_DIVX_XVID,config.isXviD);
 enableWindow(IDC_CHB_DX50,config.isLibavcodec || config.isXviD);enableWindow(IDC_CHB_DX50_XVID,config.isXviD);
 enableWindow(IDC_CHB_BLZ0,config.isLibavcodec || config.isXviD);enableWindow(IDC_CHB_BLZ0_XVID,config.isXviD);
 enableWindow(IDC_CHB_MP43,config.isLibavcodec);
 enableWindow(IDC_CHB_MP42,config.isLibavcodec);
 enableWindow(IDC_CHB_MP41,config.isLibavcodec);
 enableWindow(IDC_CHB_H263,config.isLibavcodec);
 enableWindow(IDC_CHB_WMV1,config.isLibavcodec);

}