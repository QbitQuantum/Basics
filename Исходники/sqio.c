void
SeqinfoCopy(SQINFO *sq1, SQINFO *sq2)
{
  sq1->flags = sq2->flags;
  if (sq2->flags & SQINFO_NAME)  strcpy(sq1->name, sq2->name);
  if (sq2->flags & SQINFO_ID)    strcpy(sq1->id,   sq2->id);
  if (sq2->flags & SQINFO_ACC)   strcpy(sq1->acc,  sq2->acc);
  if (sq2->flags & SQINFO_DESC)  strcpy(sq1->desc, sq2->desc);
  if (sq2->flags & SQINFO_LEN)   sq1->len    = sq2->len;
  if (sq2->flags & SQINFO_START) sq1->start  = sq2->start;
  if (sq2->flags & SQINFO_STOP)  sq1->stop   = sq2->stop;
  if (sq2->flags & SQINFO_OLEN)  sq1->olen   = sq2->olen;
  if (sq2->flags & SQINFO_TYPE)  sq1->type   = sq2->type;
  if (sq2->flags & SQINFO_SS)    sq1->ss     = Strdup(sq2->ss);
  if (sq2->flags & SQINFO_SA)    sq1->sa     = Strdup(sq2->sa);
}