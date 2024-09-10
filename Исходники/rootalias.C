//______________________________________________________________________________
void bexec2(char *macro)
{
   printf("in bexec dir=%s\n",pwd());
   if (gROOT->IsBatch()) printf("Processing benchmark: %s\n",macro);
   TPaveText *summary = (TPaveText*)bench->GetPrimitive("TPave");
   TText *tmacro = summary->GetLineWith(macro);
   if (tmacro) tmacro->SetTextColor(4);
   bench->Modified(); bench->Update();

   gROOT->Macro(macro);

   TPaveText *summary2 = (TPaveText*)bench->GetPrimitive("TPave");
   TText *tmacro2 = summary2->GetLineWith(macro);
   if (tmacro2) tmacro2->SetTextColor(2);
   bench->Modified(); bench->Update();
}