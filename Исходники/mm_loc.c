void mm_loc_donereading(struct mm_loc *p)
{
	fsetpos(p->fp, &p->pos);
}