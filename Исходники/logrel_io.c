static
void WriteLogicalRelation(FILE *f,
		          CONST struct logrelation *lr,
			  CONST struct Instance *ref)
{
  switch(LogRelRelop(lr)){
  case e_boolean_eq:
  case e_boolean_neq:
    WriteLogSide(f,lr,1,ref);
    PUTC(' ',f);
    WriteLogOp(f,LogRelRelop(lr));
    PUTC(' ',f);
    WriteLogSide(f,lr,0,ref);
    break;
  default:
    FPRINTF(ASCERR,"Unexpected Relop in WriteLogicalRelation\n");
    break;
  }
}