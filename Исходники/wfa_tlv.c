BOOL wfaDecodeTLV(BYTE *tlv_data, int tlv_len, WORD *ptag, int *pval_len, BYTE *pvalue)
{ 
   wfaTLV *data = (wfaTLV *)tlv_data;

   if(pvalue == NULL)
   {
        sigma_dut_print(DUT_MSG_ERROR, "Parm buf invalid\n");
       return FALSE;
   }
   *ptag = data->tag; 
   *pval_len = data->len;

   if(tlv_len < *pval_len)
       return FALSE;

   if(*pval_len != 0 && *pval_len < MAX_PARMS_BUFF)
   {
      wMEMCPY(pvalue, tlv_data+4, *pval_len);
   }

   return TRUE;
}