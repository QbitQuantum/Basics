void showDiags ARGS2(
	HTStream *, 		target,
	diagnosticRecord **, 	d)
{
  long i;

  for (i = 0; d[i] != NULL; i++) {
    if (d[i]->ADDINFO != NULL) {
      PUTS("Diagnostic code is ");
      PUTS(d[i]->DIAG);
      PUTC(' ');
      PUTS(d[i]->ADDINFO);
      PUTC('\n'); ;
    }
  }
}