/* variable management */
static void
stack_set(mvc *sql, int var, const char *name, sql_subtype *type, sql_rel *rel, sql_table *t, int view, int frame)
{
	sql_var *v;
	if (var == sql->sizevars) {
		sql->sizevars <<= 1;
		sql->vars = RENEW_ARRAY(sql_var,sql->vars,sql->sizevars);
	}
	v = sql->vars+var;
	v->name = NULL;
	v->value.vtype = 0;
	v->rel = rel;
	v->t = t;
	v->view = view;
	v->frame = frame;
	v->type.type = NULL;
	if (type) {
		int tpe = type->type->localtype;
		VALinit(&sql->vars[var].value, tpe, ATOMnilptr(tpe));
		v->type = *type;
	}
	if (name)
		v->name = _STRDUP(name);
}