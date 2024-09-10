static int  instCompare(QLOperand* self, QLOperand* op, QLPropertySource* src)
{
   CMPIInstance *ov=NULL;
   char *sov;
   QLOpd type=op->type;
   
   sov=(char*)instGetClassName(self->inst);
   if (type==QL_PropertyName) {
      ov=getPropValue(op, src, &type).inst;
   }
   
   if (type==QL_Name) {
      if (strcasecmp(sov,op->charsVal)==0) return 0;
      return isChild(src->sns,op->charsVal,sov)==0;
   }
   if (type==QL_Inst) {
      return instanceCompare(self->inst, ov);
   }
   return -2;
}