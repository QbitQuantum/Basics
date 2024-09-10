DetailTitleMgrView::DetailTitleMgrView(QWidget *parent)
	: TableView(parent)
{
	setViewId(DetailTitleView);
	setTabName(QString::fromLocal8Bit("详细科目管理"));

	createTable();
}