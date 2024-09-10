BOOL GetEdit1TextAsMPZ(HWND hDlg, mpz_t _P)
{
 char b[2048];
 LPSTR buf=(LPSTR)b;
 GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), &buf[0], 2047);
 INT ii=(INT)SendMessage(GetDlgItem(hDlg, IDC_BASE_LIST), LB_GETCURSEL, 0, 0);
 UINT i, Base, Bits, Trues;
 BOOL Success=TRUE;
  switch(ii)
  {
   case 0: Base=10; break;
   case 1: case 2: Base=16; break;
   case 3: Base=32; break;
   case 4: Base=62; break;
   default: Success=FALSE; break;
  }
  //uint32_t ulMaxBits=2*sizeof(uint32_t)*8 + mp_bits_per_limb;mpz_init2(FFmpzTMP, ulMaxBits);
  Success &= (mpz_init_set_str(_P, (char*)buf, Base)!=-1);
   if(Success)
   {
    Bits=mpz_sizeinbase(_P, 2);
    Trues=0;
      for(i=0; i<Bits; i++)
       if(mpz_tstbit(_P, i))Trues++;
    SetLabelUI(hDlg, IDC_BITS_STT,  Bits);
    SetLabelUI(hDlg, IDC_TRUES_STT, Trues);
   }
   else
   {
    SetLabelUI(hDlg, IDC_BITS_STT, 0xFFFFFFFF);
    SetLabelUI(hDlg, IDC_TRUES_STT, 0xFFFFFFFF);
   }
  return Success;
}//--//