int MOD_OPT(ChkMix)(Option *Opt,Model *Mod)
{
  TYPEOPT* ptOpt=( TYPEOPT*)(Opt->TypeOpt);
  TYPEMOD* ptMod=( TYPEMOD*)(Mod->TypeModel);
  int status=OK;

  if (ptOpt->Maturity.Val.V_DATE<=ptMod->T.Val.V_DATE)
    {
      Fprintf(TOSCREENANDFILE,"Current date greater than maturity!\n");
      status+=1;
    };
  if ((ptOpt->DownOrUp).Val.V_BOOL==DOWN)
    {

      if ( ((ptOpt->Limit.Val.V_NUMFUNC_1)->Compute)((ptOpt->Limit.Val.V_NUMFUNC_1)->Par,ptMod->T.Val.V_DATE)>ptMod->S0.Val.V_PDOUBLE)
        {
          Fprintf(TOSCREENANDFILE,"Limit Down greater than spot!\n");
          status+=1;
        };


    }
  if ((ptOpt->DownOrUp).Val.V_BOOL==UP)
    {
      if ( ((ptOpt->Limit.Val.V_NUMFUNC_1)->Compute)((ptOpt->Limit.Val.V_NUMFUNC_1)->Par,ptMod->T.Val.V_DATE)<ptMod->S0.Val.V_PDOUBLE)
        {
          Fprintf(TOSCREENANDFILE,"Limit Up lower than spot!\n");
          status+=1;
        };

    }
  return status;
}