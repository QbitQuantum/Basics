PExpVal TExp::EvalExpOp(
 const PExpEnv& ExpEnv, const bool& DbgP, TChA& DbgChA){
  PExpVal OutExpVal;
  TExpOp _ExpOp=TExpOp(int(ExpOp));
  switch (_ExpOp){
    case eoUPlus:
    case eoUMinus:
    case eoNot:{
      PExpVal ExpVal=ArgExpV[0]->EvalExp(ExpEnv, DbgP, DbgChA);
      TExpValType ExpValType=ExpVal->GetValType();
      if (ExpValType==evtFlt){
        TFlt Flt;
        switch (_ExpOp){
          case eoUPlus: Flt=ExpVal->GetFltVal(); break;
          case eoUMinus: Flt=-ExpVal->GetFltVal(); break;
          case eoNot: Flt=double(ExpVal->GetFltValAsInt()==0);
          default: Fail; Flt=0;
        }
        OutExpVal=TExpVal::New(Flt);
      } else {
        TExcept::Throw("Bad argument types.");
      }
      break;}
    case eoPlus:
    case eoMinus:
    case eoMul:
    case eoDiv:
    case eoIDiv:
    case eoMod:
    case eoAnd:
    case eoOr:{
      PExpVal LExpVal=ArgExpV[0]->EvalExp(ExpEnv, DbgP, DbgChA);
      PExpVal RExpVal=ArgExpV[1]->EvalExp(ExpEnv, DbgP, DbgChA);
      TExpValType LExpValType=LExpVal->GetValType();
      TExpValType RExpValType=RExpVal->GetValType();
      if ((LExpValType==evtFlt)&&(RExpValType==evtFlt)){
        // check left expression
        double LVal=LExpVal->GetFltVal();
        int LValExpon; frexp(LVal, &LValExpon);
        if (LValExpon>150){LExpVal=TExpVal::GetZeroExpVal();}
        // check right expression
        double RVal=LExpVal->GetFltVal();
        int RValExpon; frexp(RVal, &RValExpon);
        if (RValExpon>150){RExpVal=TExpVal::GetZeroExpVal();}
        // calculate
        TFlt Flt;
        switch (_ExpOp){
          case eoPlus: Flt=LExpVal->GetFltVal()+RExpVal->GetFltVal(); break;
          case eoMinus: Flt=LExpVal->GetFltVal()-RExpVal->GetFltVal(); break;
          case eoMul: Flt=LExpVal->GetFltVal()*RExpVal->GetFltVal(); break;
          case eoDiv:
            if (RExpVal->GetFltVal()==0){TExcept::Throw("Division by zero.");}
            else {Flt=LExpVal->GetFltVal()/RExpVal->GetFltVal();}
            break;
          case eoIDiv:
            if (RExpVal->GetFltValAsInt()==0){TExcept::Throw("Division by zero.");}
            else {Flt=LExpVal->GetFltValAsInt()/RExpVal->GetFltValAsInt();}
            break;
          case eoMod:
            if (RExpVal->GetFltValAsInt()==0){TExcept::Throw("Division by zero.");}
            else {Flt=LExpVal->GetFltValAsInt()%RExpVal->GetFltValAsInt();}
            break;
          case eoAnd:
            Flt=(LExpVal->GetFltValAsInt()!=0)&&(RExpVal->GetFltValAsInt()!=0); break;
          case eoOr:
            Flt=(LExpVal->GetFltValAsInt()!=0)||(RExpVal->GetFltValAsInt()!=0); break;
          default: Fail; Flt=0;
        }
        OutExpVal=TExpVal::New(Flt);
      } else
      if ((_ExpOp==eoPlus)&&(LExpValType==evtStr)&&(RExpValType==evtStr)){
        TStr Str=LExpVal->GetStrVal()+RExpVal->GetStrVal();
        OutExpVal=TExpVal::New(Str);
      } else {
        TExcept::Throw("Bad argument types.");
      }
      break;}
    case eoEq:
    case eoNEq:
    case eoLss:
    case eoGtr:
    case eoLEq:
    case eoGEq:{
      PExpVal LExpVal=ArgExpV[0]->EvalExp(ExpEnv, DbgP, DbgChA);
      PExpVal RExpVal=ArgExpV[1]->EvalExp(ExpEnv, DbgP, DbgChA);
      TExpValType LExpValType=LExpVal->GetValType();
      TExpValType RExpValType=RExpVal->GetValType();
      if ((LExpValType==evtFlt)&&(RExpValType==evtFlt)){
        TFlt Flt;
        switch (_ExpOp){
          case eoEq: Flt=double(LExpVal->GetFltVal()==RExpVal->GetFltVal()); break;
          case eoNEq: Flt=double(LExpVal->GetFltVal()!=RExpVal->GetFltVal()); break;
          case eoLss: Flt=double(LExpVal->GetFltVal()<RExpVal->GetFltVal()); break;
          case eoGtr: Flt=double(LExpVal->GetFltVal()>RExpVal->GetFltVal()); break;
          case eoLEq: Flt=double(LExpVal->GetFltVal()<=RExpVal->GetFltVal()); break;
          case eoGEq: Flt=double(LExpVal->GetFltVal()>=RExpVal->GetFltVal()); break;
          default: Fail; Flt=0;
        }
        OutExpVal=TExpVal::New(Flt);
      } else
      if ((LExpValType==evtStr)&&(RExpValType==evtStr)){
        TFlt Flt;
        switch (_ExpOp){
          case eoEq: Flt=double(LExpVal->GetStrVal()==RExpVal->GetStrVal()); break;
          case eoNEq: Flt=double(LExpVal->GetStrVal()!=RExpVal->GetStrVal()); break;
          case eoLss: Flt=double(LExpVal->GetStrVal()<RExpVal->GetStrVal()); break;
          case eoGtr: Flt=double(LExpVal->GetStrVal()>RExpVal->GetStrVal()); break;
          case eoLEq: Flt=double(LExpVal->GetStrVal()<=RExpVal->GetStrVal()); break;
          case eoGEq: Flt=double(LExpVal->GetStrVal()>=RExpVal->GetStrVal()); break;
          default: Fail; Flt=0;
        }
        OutExpVal=TExpVal::New(Flt);
      } else {
        TExcept::Throw("Bad argument types.");
      }
      break;}
    case eoIf:{
      PExpVal CondExpVal=ArgExpV[0]->EvalExp(ExpEnv, DbgP, DbgChA);
      TExpValType CondExpValType=CondExpVal->GetValType();
      if (CondExpValType==evtFlt){
        PExpVal ExpVal;
        if (CondExpVal->GetFltVal()!=0){
          ExpVal=ArgExpV[1]->EvalExp(ExpEnv, DbgP, DbgChA);
        } else {
          ExpVal=ArgExpV[2]->EvalExp(ExpEnv, DbgP, DbgChA);
        }
        OutExpVal=ExpVal;
      } else {
        TExcept::Throw("Bad argument types.");
      }
      break;}
    default: Fail; OutExpVal=NULL;
  }
  if (DbgP){
    DbgChA+="['"; DbgChA+=TExp::GetExpOpStr(_ExpOp);
    DbgChA+="'='"; DbgChA+=OutExpVal->GetStr(); DbgChA+="'] ";
  }
  return OutExpVal;
}