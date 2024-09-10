int
mvc_set_schema(mvc *m, char *schema)
{
	int ret = 0;
	sql_schema *s = find_sql_schema(m->session->tr, schema);

	if (s) {
		if (m->session->schema_name)
			_DELETE(m->session->schema_name);
		m->session->schema_name = _STRDUP(schema);
		m->type = Q_TRANS;
		if (m->session->active) 
			m->session->schema = s;
		ret = 1;
	}
	return ret;
}