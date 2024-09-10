void TfiltersPage::setPPchbs(void)
{
 int ppmode;
 if (cfgGet(IDFF_ppIsCustom)) 
  {
   enableWindow(IDC_CHB_DEBLOCKV_LUM  ,true);
   enableWindow(IDC_CHB_DEBLOCKH_LUM  ,true);
   enableWindow(IDC_CHB_DEBLOCKV_CHROM,true);
   enableWindow(IDC_CHB_DEBLOCKH_CHROM,true);
   enableWindow(IDC_CHB_DERING_LUM    ,true);
   enableWindow(IDC_CHB_DERING_CHROM  ,true);
   ppmode=cfgGet(IDFF_ppcustom);
  }
 else
  {
   enableWindow(IDC_CHB_DEBLOCKV_LUM  ,false);
   enableWindow(IDC_CHB_DEBLOCKH_LUM  ,false);
   enableWindow(IDC_CHB_DEBLOCKV_CHROM,false);
   enableWindow(IDC_CHB_DEBLOCKH_CHROM,false);
   enableWindow(IDC_CHB_DERING_LUM    ,false);
   enableWindow(IDC_CHB_DERING_CHROM  ,false);
   deci->getPPmode(&ppmode);
  };
 setCheck(IDC_CHB_DEBLOCKV_LUM  ,ppmode&LUM_V_DEBLOCK);
 setCheck(IDC_CHB_DEBLOCKH_LUM  ,ppmode&LUM_H_DEBLOCK);
 setCheck(IDC_CHB_DEBLOCKV_CHROM,ppmode&CHROM_V_DEBLOCK);
 setCheck(IDC_CHB_DEBLOCKH_CHROM,ppmode&CHROM_H_DEBLOCK);
 setCheck(IDC_CHB_DERING_LUM    ,ppmode&LUM_DERING);
 setCheck(IDC_CHB_DERING_CHROM  ,ppmode&CHROM_DERING);
}