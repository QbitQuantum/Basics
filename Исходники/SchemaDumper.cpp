void SchemaDumper::dumpColumn (QStringList &output, const QString &name, const QString &type, const QString &null, const QString &key, const QString &extra)
{
	output << qnotr ("  - name: \"%1\"").arg (name);
	output << qnotr ("    type: \"%1\"").arg (type);
	output << qnotr ("    nullok: \"%1\"").arg (null);
	if (key==notr ("PRI"))
		output << qnotr ("    primary_key: true");
	if (!isBlank (extra))
		output << qnotr ("    extra: \"%1\"").arg (extra);
}