SimpleFilter* createSimpleFilter
				(
				CalpontSystemCatalog*& csc,
				const CalpontSystemCatalog::TableColName& tcn,
				const string& opstr,
				ConstantColumn* cc
				)
{
	SimpleFilter* lsf = new SimpleFilter();

	Operator* op = new Operator();
	op->data(opstr);
	CalpontSystemCatalog::ColType ccct;
	ccct = op->resultType();
	ccct.colDataType = cc->resultType().colDataType;
	op->operationType(ccct);

	SOP sop(op);
	lsf->op(sop);

	CalpontSystemCatalog::OID oid = csc->lookupOID(tcn);
	CalpontSystemCatalog::ColType ct = csc->colType(oid);

	SimpleColumn* sc = new SimpleColumn();
	sc->schemaName(tcn.schema);
	sc->tableName(tcn.table);
	sc->tableAlias(tcn.table);
	sc->columnName(tcn.column);
	sc->oid(oid);
	sc->resultType(ct);
	sc->alias(tcn.toString());

	lsf->lhs(sc);
	lsf->rhs(cc);

	return lsf;
}