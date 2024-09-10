void SitesView::setupModel(QString& whereQryPart)
{
	QSqlDatabase db = Database::database();
	model = new QSqlQueryModel(this);
	model->setQuery(QString("SELECT site_name, url FROM sites %1").arg(whereQryPart), db);
	createTable();

}