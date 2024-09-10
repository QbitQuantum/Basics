void fixSerial::sFillList()
{
  _serial->clear();

  QApplication::setOverrideCursor( QCursor(Qt::WaitCursor) );

  QString sql = "SELECT nspname ||'.' ||relname AS tablename, nspname, relname, attname, "
		"	TRIM(quote_literal('\"''') FROM"
		"	  SUBSTRING(pg_catalog.pg_get_expr(d.adbin, d.adrelid)"
		"	  FROM '[' || quote_literal('\"''') || "
		"               '].*[' || quote_literal('\"''') || ' ]')) AS seq"
		"  FROM pg_catalog.pg_attribute a, pg_catalog.pg_class,"
		"       pg_catalog.pg_attrdef d, pg_catalog.pg_namespace   "
		"  WHERE a.attnum > 0"
                "    AND pg_namespace.oid = pg_class.relnamespace"
		"    AND NOT a.attisdropped"
		"    AND a.attnotnull"
		"    AND a.attrelid = pg_class.oid"
		"    AND d.adrelid = a.attrelid"
		"    AND d.adnum = a.attnum"
		"    AND pg_catalog.pg_get_expr(d.adbin, d.adrelid) ~* 'nextval'"
		"    AND a.atthasdef "
		"ORDER BY relname;" ;

  XSqlQuery relq;
  relq.prepare(sql);

  QString maxStr = "SELECT MAX(<? literal(\"attname\" ?>) AS maxval "
		   "FROM <? literal(\"tablename\") ?>;" ;
  XSqlQuery maxq;

  QString seqStr = "SELECT last_value AS currval FROM <? literal(\"seq\") ?>;" ;
  XSqlQuery seqq;

  XTreeWidgetItem *last = 0;
  int rows	= 0;
  int maxval	= 0;
  int currval	= 0;
  int errors	= 0;

  relq.exec();
  while (relq.next())
  {
    ParameterList params;
    params.append("attname",	relq.value("attname").toString());
    params.append("tablename",	relq.value("tablename").toString());
    params.append("seq",	relq.value("seq").toString());

    MetaSQLQuery maxMql = MetaSQLQuery(maxStr);
    maxq = maxMql.toQuery(params);
    if (maxq.first())
      maxval = maxq.value("maxval").toInt();
    else if (maxq.lastError().type() != QSqlError::NoError)
    {
      systemError(this, maxq.lastError().databaseText(), __FILE__, __LINE__);
      continue;
    }

    MetaSQLQuery seqMql = MetaSQLQuery(seqStr);
    seqq = seqMql.toQuery(params);
    if (seqq.first())
      currval = seqq.value("currval").toInt();
    else if (seqq.lastError().type() != QSqlError::NoError)
    {
      systemError(this, seqq.lastError().databaseText(), __FILE__, __LINE__);
      continue;
    }

    rows++;

    if (maxval > currval)
      errors++;

    if ((_showProblems->isChecked() && maxval > currval) ||
	! _showProblems->isChecked())
    {
      last = new XTreeWidgetItem(_serial, last, rows, maxval > currval ? 1 : 0,
				 relq.value("nspname"),
                                 relq.value("relname"),
				 relq.value("attname"),
				 relq.value("seq"),
				 maxval,
				 currval);

      if (maxval > currval)
	last->setTextColor("red");
    }
  }

  QApplication::restoreOverrideCursor();
  if (relq.lastError().type() != QSqlError::NoError)
  {
    systemError(this, relq.lastError().databaseText(), __FILE__, __LINE__);
    return;
  }

  if (errors > 0)
    _statusLit->setText(QObject::tr("Found %1 tables with mismatched serial values.")
			.arg(errors));
  else
    _statusLit->setText(QObject::tr("No problems found"));

  _fixAll->setEnabled(errors > 0);
}