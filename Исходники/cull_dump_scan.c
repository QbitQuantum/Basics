/****** cull/dump_scan/lUndumpElemFp() ******************************************
*  NAME
*     lUndumpElemFp() -- Read element from FILE stream 
*
*  SYNOPSIS
*     lListElem* lUndumpElemFp(FILE *fp, const lDescr *dp) 
*
*  FUNCTION
*     Read element from FILE stream 
*
*  INPUTS
*     FILE *fp         - file stream 
*     const lDescr *dp - descriptor 
*
*  RESULT
*     lListElem* - Read element 
******************************************************************************/
lListElem *lUndumpElemFp(FILE *fp, const lDescr *dp) 
{
   lListElem *ep;
   int n, i;
   int ret = 0;
   char *str;
   u_long32 dummy;

   DENTER(CULL_LAYER, "lUndumpElemFp");

   if (!fp) {
      LERROR(LEFILENULL);
      DEXIT;
      return NULL;
   }
   if (!dp) {
      LERROR(LEDESCRNULL);
      DEXIT;
      return NULL;
   }
   if (!(ep = lCreateElem(dp))) {
      LERROR(LECREATEELEM);
      DEXIT;
      return NULL;
   }

   if ((n = lCountDescr(dp)) <= 0) {
      LERROR(LECOUNTDESCR);
      lFreeElem(&ep);
      DEXIT;
      return NULL;
   }

   /* read bra */
   if (fGetBra(fp)) {
      printf("bra is missing\n");
      LERROR(LESYNTAX);
      lFreeElem(&ep);
      DEXIT;
      return NULL;
   }

   for (i = 0; i < n && ret == 0; i++) {
      switch (mt_get_type(dp[i].mt)) {
      case lIntT:
         ret = fGetInt(fp, &(ep->cont[i].i));
         break;
      case lUlongT:
         ret = fGetUlong(fp, &(ep->cont[i].ul));
         break;
      case lStringT:
         ret = fGetString(fp, &str);
         if (ret == 0) {
            lSetPosString(ep, i, str);
            free(str);             /* fGetString strdup's */
         }
         break;
      case lHostT:
         ret = fGetHost(fp, &str);
         if (ret == 0) {
            lSetPosHost(ep, i, str);
            free(str);             /* fGetHost strdup's */
         }
         break;
      case lFloatT:
         ret = fGetFloat(fp, &(ep->cont[i].fl));
         break;
      case lDoubleT:
         ret = fGetDouble(fp, &(ep->cont[i].db));
         break;
      case lLongT:
         ret = fGetLong(fp, &(ep->cont[i].l));
         break;
      case lCharT:
         ret = fGetChar(fp, &(ep->cont[i].c));
         break;
      case lBoolT:
         ret = fGetBool(fp, &(ep->cont[i].b));
         break;
      case lRefT:
         /* we will not undump references! But we have to skip the line! */
         ret = fGetUlong(fp, &dummy);
         ep->cont[i].ref = NULL;
         break;
      case lObjectT:
         ret = fGetObject(fp, &(ep->cont[i].obj));
         break;
      case lListT:
         ret = fGetList(fp, &(ep->cont[i].glp));
         break;
      default:
         lFreeElem(&ep);
         unknownType("lUndumpElemFp");
      }
   }

   /* error handling for loop */
   if (ret != 0) {
      lFreeElem(&ep);
      LERROR(LEFIELDREAD);
      DEXIT;
      return NULL;
   }

   /* read ket */
   if (fGetKet(fp)) {
      lFreeElem(&ep);
      printf("ket is missing\n");
      LERROR(LESYNTAX);
      DEXIT;
      return NULL;
   }

   DEXIT;
   return ep;
}