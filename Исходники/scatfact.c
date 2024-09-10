int CompleteSF_Info(T_SF_Info *SFI, int LblExact, int Set_f_stol_0)
{
  int          m;
  const char   *lt, *li;
  int          iSFT;
  T_SF_Tables  *SFT;


  if (SFI->SFT || SFI->CAA || SFI->f_stol_0 != -1.)
    InternalError("CompleteSF_Info(): SFI already set");

  SFT = SF_Tables;

  for (iSFT = 0; iSFT < nSF_Tables; iSFT++, SFT++)
  {
    if (str_icmp(SFT->Label, SFI->Lbl) == 0)
    {
      SFI->SFT = SFT;
      break;
    }
  }

  if (SFI->SFT == NULL && LblExact == 0)
  {
    SFT = SF_Tables;

    for (iSFT = 0; iSFT < nSF_Tables; iSFT++, SFT++)
    {
      m = 0;

      for (lt = SFT->Label, li = SFI->Lbl; isalpha(*lt); lt++, li++)
      {
        if (toupper(*lt) != toupper(*li))
        {
          m = 0;
          break;
        }

        m++;
      }

      if (m)
      {
        SFI->SFT = SFT;
        break;
      }
    }
  }

  if (SFI->SFT)
  {
    if (Set_f_stol_0)
    {
      if (SFI->SFT->Tab[0].stol != 0.)
      {
        char  buf[128];

        Sprintf(buf,
          "ScatteringFactor %.60s: missing entry for sinTovL = 0",
          SFI->SFT->Label);

        progerror(buf);
      }

      SFI->f_stol_0 = SFI->SFT->Tab[0].f;
    }
  }
  else
  {
    if (ModeScatteringFactorTable == 0)
    {
      SFI->CAA = FindSF_WK95_CAA(SFI->Lbl, LblExact);
      // printf("atom: %s -> using xray scattering factors from WK95\n", SFI->Lbl);
      if (NULL == SFI->CAA)
        return -1;
  
      if (Set_f_stol_0)
        SFI->f_stol_0 = CalcSF_WK95_CAA(SFI->CAA, 0.);
    }
 //   else if (ModeScatteringFactorTable == 1)
 //   {
 //     SFI->CAA = FindSF_IT92_CAA(SFI->Lbl, LblExact);
 //     printf("%s -> using scattering factors from IT92\n", SFI->Lbl);
 //     if (NULL == SFI->CAA)
 //       return -1;
 // 
 //     if (Set_f_stol_0)
 //       SFI->f_stol_0 = CalcSF_IT92_CAA(SFI->CAA, 0.);
 //   }
    else if (ModeScatteringFactorTable == 2)
    {
      SFI->CAA = FindSF_IT4322(SFI->Lbl, LblExact); // StefS 
      // printf("atom: %s -> using electron scattering factors from IT 4.3.2.2\n", SFI->Lbl); 
      if (NULL == SFI->CAA)
        return -1;
  
      if (Set_f_stol_0)
        SFI->f_stol_0 = CalcSF_IT4322(SFI->CAA, 0.);
    }
    else if (ModeScatteringFactorTable == 3)
    {
      SFI->CAA = FindSF_IT4323(SFI->Lbl, LblExact); // StefS 
      // printf("atom: %s -> using electron scattering factors from IT 4.3.2.3\n", SFI->Lbl); 
      if (NULL == SFI->CAA)
        return -1;
  
      if (Set_f_stol_0)
        SFI->f_stol_0 = CalcSF_IT4323(SFI->CAA, 0.);
    }
  }

  return 0;
}