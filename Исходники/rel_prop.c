char *
propvalue2string( prop *p)
{
	char buf [BUFSIZ];

	if (p->value) {
		switch(p->kind) {
		case PROP_JOINIDX: {
			   sql_idx *i = p->value;

			   snprintf(buf, BUFSIZ, "%s.%s.%s", i->t->s->base.name, i->t->base.name, i->base.name);
			   return _STRDUP(buf);
			}
		case PROP_REMOTE: {
			   char *uri = p->value;

			   return _STRDUP(uri);
			}
		default:
			break;
		}
	}
	return "";
}