int FixMethod(Planning *pt_plan, PricingMethod *pt_method)
{
  int i,j;
  char msg,answer;

  if (pt_plan->NumberOfMethods == 0)
    return OK;

  for (j=0; j<pt_plan->VarNumber && pt_plan->Par[j].Location->Vtype!=PREMIA_NULLTYPE; ++j){
    for (i=0; pt_method->Par[i].Vtype!=PREMIA_NULLTYPE; ++i){ 
      if (!strcmp(pt_method->Par[i].Vname,pt_plan->Par[j].Location->Vname))
	{
	  pt_plan->Par[j].Location = &pt_method->Par[i];
	  pt_method->Par[i].Viter=ALREADYITERATED+j;  
	  return DONOTITERATE; 
	}
      else if (CompareParameterNames(pt_method->Par[i].Vname,pt_plan->Par[j].Location->Vname)==OK)
	{
	  Fprintf(TOSCREEN,"\nWould you like to iterate \"%s\" like \"%s\" \n\t\t (ok: Return, no: n) ? \t",pt_method->Par[i].Vname, pt_plan->Par[j].Location->Vname);
	  answer = (char)tolower(fgetc(stdin));
	  msg = answer;
	  while( (answer != '\n') && (answer != EOF))
	    answer = (char)fgetc(stdin);
	  if (msg=='\n')
	    {
	      pt_plan->Par[j].Location = &pt_method->Par[i];
	      pt_method->Par[i].Viter=ALREADYITERATED+j;
	      return DONOTITERATE; 
	    }
	}
      else if  (pt_method->Par[i].Vtype == pt_plan->Par[j].Location->Vtype)
	{
	  Fprintf(TOSCREEN,"\nWould you like to iterate \"%s\" like \"%s\" \n\t\t (ok: Return, no: n) ? \t",pt_method->Par[i].Vname, pt_plan->Par[j].Location->Vname);
	  answer = (char)tolower(fgetc(stdin));
	  msg = answer;
	  while( (answer != '\n') && (answer != EOF))
	    answer = (char)fgetc(stdin);
	  if (msg=='\n')
	    {
	      pt_plan->Par[j].Location = &pt_method->Par[i];
	      pt_method->Par[i].Viter=ALREADYITERATED+j;
	      return DONOTITERATE;
	    }
	}
    }
  }
  return OK;
}