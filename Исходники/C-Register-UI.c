__saveds __asm ULONG GROM_Generate (a2 Object *Win, a1 SW_IDATA **idata)
{
   UBYTE fspec[FMSIZE];
   BPTR  fp = NULL;
   ULONG x, Cost1 = (ULONG)(idata[2]), Cost2 = (ULONG)(idata[3]);
   UBYTE DoneText[] = "\33c\33bDone:\33n Registration form saved to file %s\n\n"
                      "Email to " SRK_EMAIL " or send by postal mail to:\n\n"
                      "   %s Registration\n"
                      "   405 Pulsar St.\n"
                      "   Fort Collins, CO 80525 USA\n\n"
                      "See the above file for more information.\n\n"
                      "Thank you for registering %s!";
   UBYTE ErrText[]  = "\33c\33bError:\33n Unable to open registration file %s.";
   UBYTE *Prog = (UBYTE *)(idata[1]);

   AddPart(strcpy(fspec, "RAM:"), Prog, FMSIZE);
   strcat(fspec, ".Regform");

   for (x=0; RG_ParseTable[x].Keyword; x++) {
      UBYTE *Val;
      get((*idata)->Gads[x], MUIA_String_Contents, &Val);

      if (RG_ParseTable[x].Required && (!Val || !Val[0])) {
         MUI_Request(Win, (*idata)->RegWin, 0,NULL, "*_Ok",(char *)
                     "\33c\33bError:\33n No value suppled for required "
                     "field '%s'\n",
                     RG_ParseTable[x].Keyword, NULL);
         goto Done;
      }
   }


   if (!(fp = Open(fspec, MODE_NEWFILE))) {
      MUI_Request(Win, (*idata)->RegWin, 0,NULL, "*_Ok",(char *)ErrText,
                  fspec, NULL, NULL);
      goto Done;
   }

   FPrintf(fp, "E-mail this form to %s with the subject line:\n"
               "  CMD REGISTER %s\n\n"
               "Registration cost is US $%ld for E-Mail registration and\n"
               "US $%ld for postal mail registration.  E-Mail registration\n"
               "will receive a keyfile shortly.  Postal registration should\n"
               "allow 4 weeks and include a disk and self addressed stamped\n"
               "envelope.  Checks can be made payable to ShadowWorks Software.\n\n"
               "Registration request for %s\n\n",

           SRK_EMAIL, Prog, Cost1, Cost2, Prog);

   for (x=0; RG_ParseTable[x].Keyword; x++) {
      UBYTE *Val;
      
      get((*idata)->Gads[x], MUIA_String_Contents, &Val);

      if (Val && Val[0])
         FPrintf(fp, "%-10s = %s\n", RG_ParseTable[x].Keyword, Val);
   }

   Close(fp); fp = NULL;

   MUI_Request(Win, (*idata)->RegWin, 0,NULL, "*_Ok",(char *)DoneText,
               fspec, Prog, Prog);

   set(Win, MUIA_Window_Open, FALSE);

  Done:
   if (fp) Close(fp);

   return 0;
}