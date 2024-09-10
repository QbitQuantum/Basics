ValPtr
VALcopy(ValPtr d, const ValRecord *s)
{
	if (!ATOMextern(s->vtype)) {
		*d = *s;
	} else if (s->val.pval == 0) {
		d->val.pval = ATOMnil(s->vtype);
		d->vtype = s->vtype;
	} else if (s->vtype == TYPE_str) {
		d->vtype = TYPE_str;
		d->val.sval = GDKstrdup(s->val.sval);
		d->len = strLen(d->val.sval);
	} else if (s->vtype == TYPE_bit) {
		d->vtype = s->vtype;
		d->len = 1;
		d->val.btval = s->val.btval;
	} else {
		ptr p = s->val.pval;

		d->vtype = s->vtype;
		d->len = ATOMlen(d->vtype, p);
		d->val.pval = GDKmalloc(d->len);
		memcpy(d->val.pval, p, d->len);
	}
	return d;
}