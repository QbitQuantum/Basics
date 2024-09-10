void InitParamHashTable(int MaxLenDualMem_i, int MaxLenCutMem_i, int LenHashTab_i, int CutsofSol_i, int MaxSolDualAg_i)
{
  int i = 0;

  MaxLenDualMem = MaxLenDualMem_i;
  MaxLenCutMem  = MaxLenCutMem_i;
  LenHashTab    = LenHashTab_i;
  CutsofSol     = CutsofSol_i;
  MaxSolDualAg  = ((float) MaxSolDualAg_i / 100);

  DualMem = (DualType *) malloc(MaxLenDualMem * sizeof(DualType));
  memset( DualMem, 0, MaxLenDualMem * sizeof(DualType));
  CutMem  = (CutType *) malloc(MaxLenCutMem * sizeof(CutType));
  memset( CutMem, 0, MaxLenCutMem * sizeof(CutType));
  first_free  = LenHashTab;
  for (i = 0; i < LenHashTab; i++)
    CutMem[i] = (CutType) {FALSE,FALSE,0,NULL,0,i,-1,-1,0};
  for (i = LenHashTab; i < MaxLenCutMem-1; i++)
    CutMem[i] = (CutType) {FALSE,FALSE,0,NULL,0,i,-1,i+1,0};
  CutMem[i] = (CutType) {FALSE,FALSE,0,NULL,0,i,-1,-1,0};
  
  LocalTime(&lost_time_cron);
}