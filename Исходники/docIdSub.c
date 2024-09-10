void docIdSubOutput(struct docIdSub *el, FILE *f, char sep, char lastSep) 
/* Print out docIdSub.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%d", el->ix);
fputc(sep,f);
fprintf(f, "%d", el->status);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->assembly);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->submitDate);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->md5sum);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->valReport);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->valVersion);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->metaData);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->submitPath);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->submitter);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}